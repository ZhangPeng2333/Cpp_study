// 进度条封装 npm风
/// @file progress.h
/// @brief 带节流与清行能力的 npm 风格进度条

#ifndef CPP_COMMON_PROGRESS_H
#define CPP_COMMON_PROGRESS_H

#include <sys/time.h>
#include <pthread.h>

/**
 * @brief 进度条封装
 *
 * 支持百分比、速率与耗时显示, 非终端环境下退化为纯文本输出,
 * 绘制按时间间隔节流以减少刷屏。
 */
class Progress {
public:
    const char *label;     ///< 标题文本
    long long   total_units; ///< 总单位数(块)
    long long   total_bytes; ///< 总字节数
    long long   done_units;  ///< 已完成单位数
    long long   done_bytes;  ///< 已完成字节数
    int         width;       ///< 进度条宽度
    int         tty;         ///< 是否终端(1是0否)
    int         drawn;       ///< 是否已绘制
    int         last_len;    ///< 上帧长度(用于清行)
    struct timeval start;    ///< 起始时间
    struct timeval last_draw;///< 末次绘制时间

    Progress();

    /**
     * @brief 初始化进度条
     * @param label       标题
     * @param total_units 总块数
     * @param total_bytes 总字节数
     * @param width       条宽
     */
    void init(const char *label,
              long long total_units, long long total_bytes, int width);
    /**
     * @brief 累加进度并可能触发绘制
     * @param units 新增完成单位数
     * @param bytes 新增完成字节数
     */
    void add(long long units, long long bytes);
    /**
     * @brief 预设已完成量(断点续传起点)
     * @param units 已完成的单位数
     * @param bytes 已完成的字节数
     */
    void seed(long long units, long long bytes);
    /**
     * @brief 收尾绘制(定格 100%)
     */
    void finish();
    /**
     * @brief 清行复位
     */
    void clear();

private:
    static pthread_mutex_t s_mtx; ///< 跨实例绘制互斥锁
    void drawLocked();            ///< 内部绘制(调用方持锁)
};

#endif
