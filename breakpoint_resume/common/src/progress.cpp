// 进度条实现

#include "progress.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>

pthread_mutex_t Progress::s_mtx = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief 计算自 t0 起的已过秒数
 * @param t0 起始时间
 * @return 经过的秒数(含小数)
 */
static double elapsed_sec(const struct timeval *t0)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)(t.tv_sec - t0->tv_sec)
         + (double)(t.tv_usec - t0->tv_usec) / 1e6;
}

/**
 * @brief 把字节数格式化为带单位的可读串
 * @param buf 输出缓冲区
 * @param n   buf 长度
 * @param bytes 待格式化字节数
 */
static void fmt_size(char *buf, size_t n, long long bytes)
{
    static const char *u[] = {"B", "KB", "MB", "GB", "TB"};
    double v = (double)bytes;
    int i = 0;
    while (v >= 1024.0 && i < 4)
    {
        v /= 1024.0;
        i++;
    }
    if (i == 0)
        snprintf(buf, n, "%lld %s", bytes, u[i]);
    else
        snprintf(buf, n, "%.2f %s", v, u[i]);
}

/**
 * @brief 进度条构造函数, 清零所有字段
 */
Progress::Progress()
{
    label = "";
    total_units = 0;
    total_bytes = 0;
    done_units = 0;
    done_bytes = 0;
    width = 30;
    tty = 0;
    drawn = 0;
    last_len = 0;
    memset(&start, 0, sizeof(start));
    memset(&last_draw, 0, sizeof(last_draw));
}

/**
 * @brief 初始化进度条
 * @param lbl        标题
 * @param total_units_ 总块数
 * @param total_bytes_ 总字节数
 * @param w          条宽
 */
void Progress::init(const char *lbl,
                    long long total_units_, long long total_bytes_, int w)
{
    label = lbl ? lbl : "";
    total_units = total_units_;
    total_bytes = total_bytes_;
    done_units = 0;
    done_bytes = 0;
    width = (w > 0) ? w : 30;
    tty = (isatty(fileno(stdout)) ? 1 : 0);
    last_len = 0;
    gettimeofday(&start, NULL);
    last_draw = start;
}

/**
 * @brief 绘制一帧(调用方须持 s_mtx)
 */
void Progress::drawLocked()
{
    double pct = (total_units > 0)
                     ? (double)done_units / (double)total_units
                     : 1.0;
    if (pct > 1.0) pct = 1.0;
    if (pct < 0.0) pct = 0.0;

    int filled = (int)(pct * width);
    if (filled > width) filled = width;

    double el = elapsed_sec(&start);
    if (el < 1e-6) el = 1e-6;
    double speed = (double)done_bytes / el;
    double eta = (pct > 0.0 && pct < 1.0) ? (el / pct) - el : 0.0;

    char sb[32], tb[32], sp[32], et[32];
    fmt_size(sb, sizeof(sb), done_bytes);
    fmt_size(tb, sizeof(tb), total_bytes);
    fmt_size(sp, sizeof(sp), (long long)speed);
    if (eta >= 1.0)
        snprintf(et, sizeof(et), "%.0fs", eta);
    else
        et[0] = '\0';

    char bar[128];
    int k = 0;
    for (int i = 0; i < width; i++) // 生成条
        bar[k++] = (i < filled) ? '#' : '-';
    bar[k] = '\0';

    char line[1024];
    snprintf(line, sizeof(line), "%s [%s] %3d%% %s/%s %s/s %s",
             label, bar, (int)(pct * 100), sb, tb, sp, et);

    // 按上帧长度清行
    fputc('\r', stdout);
    for (int i = 0; i < last_len + 1; i++)
        fputc(' ', stdout);
    fputc('\r', stdout);
    fputs(line, stdout);
    fflush(stdout);
    last_len = (int)strlen(line);
}

/**
 * @brief 累加进度并可能触发绘制
 * @param units 新增完成单位数
 * @param bytes 新增完成字节数
 */
void Progress::add(long long units, long long bytes)
{
    if (total_units <= 0)
        return;
    // 计数与绘制均持同一把锁, 多线程并发自增不丢计数
    pthread_mutex_lock(&s_mtx);
    done_units += units;
    done_bytes += bytes;
    if (done_units > total_units) done_units = total_units;
    if (done_bytes > total_bytes) done_bytes = total_bytes;
    if (!tty)
    {
        pthread_mutex_unlock(&s_mtx);
        return;
    }

    // 时间节流(持锁内判定)
    struct timeval now;
    gettimeofday(&now, NULL);
    double dt = (double)(now.tv_sec - last_draw.tv_sec)
              + (double)(now.tv_usec - last_draw.tv_usec) / 1e6;
    if (done_units < total_units && dt < 0.12)
    {
        pthread_mutex_unlock(&s_mtx);
        return;
    }
    last_draw = now;
    drawLocked();
    pthread_mutex_unlock(&s_mtx);
}

/**
 * @brief 预设已完成量(断点续传起点)
 * @param units 已完成的单位数
 * @param bytes 已完成的字节数
 */
void Progress::seed(long long units, long long bytes)
{
    if (units < 0) units = 0;
    if (bytes < 0) bytes = 0;
    done_units = units;
    done_bytes = bytes;
}

/**
 * @brief 收尾绘制(定格 100%)
 */
void Progress::finish()
{
    if (total_units <= 0)
        return;
    if (!tty)
    {
        printf("%s 完成 %lld/%lld 块 (%lld 字节)\n",
               label, done_units, total_units, done_bytes);
        fflush(stdout);
        return;
    }
    pthread_mutex_lock(&s_mtx);
    drawLocked();
    printf("\n");
    fflush(stdout);
    pthread_mutex_unlock(&s_mtx);
}

/**
 * @brief 清行复位
 */
void Progress::clear()
{
    if (last_len == 0)
        return;
    pthread_mutex_lock(&s_mtx);
    fputc('\r', stdout);
    for (int i = 0; i < last_len + 1; i++)
        fputc(' ', stdout);
    fputc('\r', stdout);
    fflush(stdout);
    last_len = 0;
    pthread_mutex_unlock(&s_mtx);
}
