// 下载客户端实现

#include "client.h"
#include "codec.h"
#include "socket.h"
#include "md5.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

// 全局状态
volatile sig_atomic_t Client::s_exit = 0;
int Client::s_sock = -1;
char Client::s_user[USER_SIZE];
char Client::s_pass[PASSWORD_SIZE];
int Client::s_socks[MAX_SOCKETS];
int Client::s_nsocks = 0;

/**
 * @brief 信号处理: 置退出标志并关闭所有活动连接
 * @param sig 信号编号
 */
void Client::sigHandler(int sig)
{
    (void)sig;
    s_exit = 1;
    for (int i = 0; i < s_nsocks; i++) // 关闭全部连接
    {
        if (s_socks[i] >= 0)
        {
            close(s_socks[i]);
            s_socks[i] = -1;
        }
    }
}

/**
 * @brief 打印人类可读的文件大小
 * @param size 字节数
 */
void Client::printSz(off_t size)
{
    const char *u[] = {"B", "KB", "MB", "GB", "TB"};
    double v = (double)size;
    int i = 0;
    while (v >= 1024.0 && i < 4)
    {
        v /= 1024.0;
        i++;
    }
    if (i == 0)
        printf("%lld %s", (long long)size, u[i]);
    else
        printf("%.2f %s", v, u[i]);
}

/**
 * @brief 解析用户输入的文件编号
 * @param line 输入行
 * @param max  最大合法下标(文件数)
 * @return 合法下标或 -1
 */
int Client::parseIdx(const char *line, int max)
{
    while (*line == ' ' || *line == '\t')
        line++;
    char *end;
    long val = strtol(line, &end, 10);
    if (end == line)
        return -1;
    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')
        end++;
    if (*end != '\0')
        return -1;
    if (val < 0 || val >= max)
        return -1;
    return (int)val;
}

/**
 * @brief 生成配置文件路径(文件名.config)
 * @param filename 文件名
 * @param out      输出路径
 * @param n        out 长度
 */
void Client::configPath(const char *filename, char *out, size_t n)
{
    snprintf(out, n, "%s.config", filename);
}

/**
 * @brief 注册流程
 * @param fd 已连接套接字
 * @return 0 成功, -1 失败
 */
int Client::regClient(int fd)
{
    LoginHeader hdr;
    int ret = -1;
    char buf[USER_SIZE + PASSWORD_SIZE + 2];

    memset(&hdr, 0, sizeof(hdr));
    printf("=======Reg=======\n");
    printf("Reg username:");
    if (fgets(hdr.username, USER_SIZE, stdin) == NULL)
    {
        printf("用户名EOF\n");
        return -1;
    }
    hdr.username[strcspn(hdr.username, "\n")] = '\0';
    printf("Reg password:");
    if (fgets(hdr.password, PASSWORD_SIZE, stdin) == NULL)
    {
        printf("密码EOF\n");
        return -1;
    }
    hdr.password[strcspn(hdr.password, "\n")] = '\0';
    hdr.op_type = OP_REGISTER;
    hdr.check = AUTH_UNK;
    // 缓存凭证供下载连接复用
    strncpy(s_user, hdr.username, USER_SIZE - 1);
    s_user[USER_SIZE - 1] = '\0';
    strncpy(s_pass, hdr.password, PASSWORD_SIZE - 1);
    s_pass[PASSWORD_SIZE - 1] = '\0';
    Auth::pack(buf, &hdr);

    ret = Socket::sendAll(fd, buf, sizeof(buf));
    if (ret == -1)
    {
        perror("reg send");
        return -1;
    }
    ret = Socket::recvAll(fd, buf, sizeof(buf));
    if (ret == -1)
    {
        perror("reg recv");
        return -1;
    }
    Auth::unpack(buf, &hdr);
    if (hdr.check == REG_OK)
    {
        printf("注册成功!\n");
        return 0;
    }
    printf("注册失败\n");
    return -1;
}

/**
 * @brief 登录流程并缓存凭证
 * @param fd 已连接套接字
 * @return 0 成功, -1 失败
 */
int Client::loginClient(int fd)
{
    LoginHeader hdr;
    memset(&hdr, 0, sizeof(hdr));
    int ret = -1;
    char buf[USER_SIZE + PASSWORD_SIZE + 2];

    printf("=======Login=======\n");
    printf("Login username:");
    if (fgets(hdr.username, USER_SIZE, stdin) == NULL)
    {
        printf("用户名EOF\n");
        return -1;
    }
    hdr.username[strcspn(hdr.username, "\n")] = '\0';
    printf("Login password:");
    if (fgets(hdr.password, PASSWORD_SIZE, stdin) == NULL)
    {
        printf("密码EOF\n");
        return -1;
    }
    hdr.password[strcspn(hdr.password, "\n")] = '\0';
    hdr.op_type = OP_LOGIN;
    hdr.check = AUTH_UNK;

    // 缓存凭证供下载连接复用
    strncpy(s_user, hdr.username, USER_SIZE - 1);
    s_user[USER_SIZE - 1] = '\0';
    strncpy(s_pass, hdr.password, PASSWORD_SIZE - 1);
    s_pass[PASSWORD_SIZE - 1] = '\0';

    Auth::pack(buf, &hdr);
    ret = Socket::sendAll(fd, buf, sizeof(buf));
    if (ret == -1)
    {
        perror("login send");
        return -1;
    }
    ret = Socket::recvAll(fd, buf, sizeof(buf));
    if (ret == -1)
    {
        perror("login recv");
        return -1;
    }
    Auth::unpack(buf, &hdr);
    if (hdr.check == LOG_OK)
    {
        printf("登录成功!\n");
        return 0;
    }
    printf("登录失败\n");
    return -1;
}

/**
 * @brief 用已缓存凭证在指定连接上登录
 * @param fd 已连接套接字
 * @return 0 成功, -1 失败
 */
int Client::loginOnSock(int fd)
{
    LoginHeader hdr;
    memset(&hdr, 0, sizeof(hdr));
    strncpy(hdr.username, s_user, USER_SIZE - 1);
    strncpy(hdr.password, s_pass, PASSWORD_SIZE - 1);
    hdr.op_type = OP_LOGIN;
    hdr.check = AUTH_UNK;
    char buf[USER_SIZE + PASSWORD_SIZE + 2];
    Auth::pack(buf, &hdr);
    if (Socket::sendAll(fd, buf, sizeof(buf)) == -1)
        return -1;
    if (Socket::recvAll(fd, buf, sizeof(buf)) == -1)
        return -1;
    Auth::unpack(buf, &hdr);
    if (hdr.check != LOG_OK)
        return -1;
    // 吞掉服务器登录后主动下发的文件列表
    FileList dummy;
    memset(&dummy, 0, sizeof(dummy));
    if (recvList(fd, &dummy) == -1)
        return -1;
    return 0;
}

/**
 * @brief 接收文件列表
 * @param fd   已连接套接字
 * @param list 输出文件列表
 * @return 0 成功, -1 失败
 */
int Client::recvList(int fd, FileList *list)
{
    char type;
    if (Socket::recvAll(fd, &type, 1) != 0)
        return -1;
    if (type != MSG_LIST)
    {
        fprintf(stderr, "类型错\n");
        return -1;
    }
    char cnt_buf[4];
    if (Socket::recvAll(fd, cnt_buf, 4) != 0)
        return -1;
    int32_t count;
    Codec::getInt(cnt_buf, &count);
    if (count > FILE_LIST_SIZE)
        count = FILE_LIST_SIZE;
    if (count < 0)
        count = 0;
    list->file_count = (uint32_t)count;

    for (int32_t i = 0; i < count; i++)
    {
        char name[FILENAME_SIZE];
        if (Socket::recvAll(fd, name, FILENAME_SIZE) != 0)
            return -1;
        name[FILENAME_SIZE - 1] = '\0';
        memcpy(list->files[i].filename, name, FILENAME_SIZE);

        char sz_buf[8];
        if (Socket::recvAll(fd, sz_buf, 8) != 0)
            return -1;
        int64_t sz;
        Codec::getLong(sz_buf, &sz);
        list->files[i].file_size = (off_t)sz;
    }
    return 0;
}

/**
 * @brief 发送下载请求
 * @param fd    已连接套接字
 * @param type  请求类型(REQ_*)
 * @param index 文件下标
 * @param seq   块序号
 * @return 0 成功, -1 失败
 */
int Client::sendReq(int fd, uint8_t type, uint32_t index, uint32_t seq)
{
    char buf[1 + 4 + 4];
    Codec::putChar(buf, (char)type);
    Codec::putInt(buf + 1, (int32_t)index);
    Codec::putInt(buf + 5, (int32_t)seq);
    return Socket::sendAll(fd, buf, sizeof(buf));
}

/**
 * @brief 接收文件头
 * @param fd  已连接套接字
 * @param hdr 输出文件头
 * @return 0 成功, -1 失败
 */
int Client::recvHeader(int fd, FileHeader *hdr)
{
    char type;
    if (Socket::recvAll(fd, &type, 1) != 0)
        return -1;
    if (type != MSG_HEADER)
    {
        fprintf(stderr, "类型错\n");
        return -1;
    }
    char buf[FILENAME_SIZE + 8 + 4 + MD5_LEN];
    if (Socket::recvAll(fd, buf, sizeof(buf)) != 0)
        return -1;

    const char *p = buf;
    memcpy(hdr->filename, p, FILENAME_SIZE);
    hdr->filename[FILENAME_SIZE - 1] = '\0';
    p += FILENAME_SIZE;
    int64_t sz;
    Codec::getLong(p, &sz);
    hdr->file_size = (off_t)sz;
    p += 8;
    Codec::getInt(p, &hdr->block_nums);
    p += 4;
    memcpy(hdr->md5, p, MD5_LEN);
    return 0;
}

/**
 * @brief 接收数据块并落盘
 * @param fd      已连接套接字
 * @param dest_fd 本地目标 fd
 * @param seq     期望块序号
 * @param bm      断点续传位图
 * @param prog    进度条
 * @return 0 成功, -1 失败
 */
int Client::recvBlock(int fd, int dest_fd, int seq, Bitmap *bm, Progress *prog)
{
    char seq_buf[4], sz_buf[4];
    if (Socket::recvAll(fd, seq_buf, 4) != 0)
        return -1;
    if (Socket::recvAll(fd, sz_buf, 4) != 0)
        return -1;

    int32_t rseq, size;
    Codec::getInt(seq_buf, &rseq);
    Codec::getInt(sz_buf, &size);
    if (rseq != seq || size < 0 || size > BLOCK_BYTE_SIZE)
    {
        fprintf(stderr, "非法块头\n");
        return -1;
    }

    unsigned char data[BLOCK_BYTE_SIZE];
    if (size > 0 && Socket::recvAll(fd, data, (size_t)size) != 0)
        return -1;

    off_t off = (off_t)seq * BLOCK_BYTE_SIZE;
    size_t w = 0;
    while (w < (size_t)size)
    {
        ssize_t n = pwrite(dest_fd, data + w, size - (int)w, off + (off_t)w);
        if (n <= 0)
        {
            fprintf(stderr, "写盘失败\n");
            return -1;
        }
        w += (size_t)n;
    }

    if (bm && bm->set(seq) != 0)
    {
        fprintf(stderr, "写配置失败\n");
        return -1;
    }
    if (prog)
        prog->add(1, size); // 刷新进度条
    return 0;
}

/// 线程参数: 本线程独立连接 + 共享上下文
struct ThreadArg {
    int        sock; ///< 本线程独立连接
    DlContext *ctx;  ///< 共享下载上下文
};

/**
 * @brief 下载循环: 领块并发送/接收(独立连接)
 * @param sock 本线程独立连接
 * @param c    下载上下文
 */
void Client::workerLoop(int sock, DlContext *c)
{
    while (!s_exit && !c->abort)
    {
        int seq;
        pthread_mutex_lock(&c->seq_mtx);
        if (c->next_seq >= c->block_nums)
        {
            pthread_mutex_unlock(&c->seq_mtx);
            return;
        }
        seq = c->next_seq++;
        pthread_mutex_unlock(&c->seq_mtx);

        if (c->bm->has(seq))
            continue; // 续传已收跳过

        if (sendReq(sock, REQ_BLOCK, c->idx, (uint32_t)seq) == -1)
        {
            if (!s_exit) c->abort = 1;
            return;
        }
        if (recvBlock(sock, c->dest_fd, seq, c->bm, c->prog) == -1)
        {
            if (!s_exit) c->abort = 1;
            return;
        }
    }
}

/**
 * @brief 下载线程入口
 * @param arg ThreadArg 指针(含本线程 socket 与上下文)
 * @return NULL
 */
void *Client::workerThread(void *arg)
{
    ThreadArg *a = (ThreadArg *)arg;
    workerLoop(a->sock, a->ctx); // 使用本线程独立连接
    return NULL;
}

/**
 * @brief 程序入口: 解析参数并启动交互
 * @param argc 参数个数
 * @param argv 参数列表(ip port)
 * @return 0 正常退出, -1 参数错误
 */
int Client::run(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("usage: %s <ip> <port>\n", argv[0]);
        return -1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    if (port <= 0 || port > 65535)
    {
        printf("端口错误\n");
        return -1;
    }

    if (signal(SIGINT, sigHandler) == SIG_ERR)
    {
        perror("signal");
        return -1;
    }
    signal(SIGPIPE, SIG_IGN); // 忽略断连

    // 连接服务器
    s_sock = Socket::connect(ip, port);
    if (s_sock == -1)
        return -1;

    // 登录注册
    printf("请选择操作：\n");
    printf("  1. 注册\n");
    printf("  2. 登录\n");
    printf("输入编号: ");
    fflush(stdout);
    char choice[16];
    if (fgets(choice, sizeof(choice), stdin) == NULL)
    {
        if (s_exit)
        {
            printf("用户中断\n");
            close(s_sock);
            return 0;
        }
        fprintf(stderr, "读取失败\n");
        close(s_sock);
        return -1;
    }
    if (s_exit)
    {
        printf("用户中断\n");
        close(s_sock);
        return 0;
    }
    int opt = atoi(choice);
    int auth = -1;
    switch (opt)
    {
    case 1:
        auth = regClient(s_sock);
        break;
    case 2:
        auth = loginClient(s_sock);
        break;
    default:
        printf("无效选择\n");
        close(s_sock);
        return -1;
    }
    if (auth == -1)
    {
        fprintf(stderr, "认证失败\n");
        close(s_sock);
        return -1;
    }
    if (s_exit)
    {
        close(s_sock);
        printf("用户中断\n");
        return 0;
    }

    // 接收列表
    FileList list;
    memset(&list, 0, sizeof(list));
    if (recvList(s_sock, &list) == -1)
    {
        if (s_exit)
        {
            printf("用户退出\n");
            close(s_sock);
            return 0;
        }
        perror("recv list");
        close(s_sock);
        return -1;
    }
    if (list.file_count == 0)
    {
        printf("无可用文件\n");
        sendReq(s_sock, REQ_QUIT, 0, 0);
        close(s_sock);
        return 0;
    }

    // 展示列表
    printf("\n文件列表 共 %u 个:\n", list.file_count);
    for (uint32_t i = 0; i < list.file_count; i++)
    {
        printf("  [%2u] %-40s  ", i, list.files[i].filename);
        printSz(list.files[i].file_size);
        printf("\n");
    }

    // 交互下载
    char line[256];
    while (!s_exit)
    {
        printf("\n输入编号下载 (q退出): ");
        fflush(stdout);
        if (s_exit)
            break;
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            if (s_exit)
                break;
            break;
        }
        if (s_exit)
            break;
        line[strcspn(line, "\r\n")] = '\0';
        if (strcmp(line, "q") == 0 || strcmp(line, "quit") == 0)
            break;

        int idx = parseIdx(line, (int)list.file_count);
        if (idx < 0)
        {
            if (!s_exit)
                printf("编号无效 0~%u\n", list.file_count - 1);
            continue;
        }

        // 载入位图续传
        char cfg_path[1024];
        configPath(list.files[idx].filename, cfg_path, sizeof(cfg_path));
        Bitmap bm;
        int have_cfg = 0;
        char cfg_name[FILENAME_SIZE];
        off_t cfg_size = 0;
        unsigned char cfg_md5[MD5_LEN];
        if (bm.load(cfg_path, cfg_name, sizeof(cfg_name),
                    &cfg_size, cfg_md5) == 0)
        {
            if (strcmp(cfg_name, list.files[idx].filename) == 0 &&
                cfg_size == list.files[idx].file_size)
                have_cfg = 1;
            else
            {
                remove(cfg_path); // 失效config
                bm.destroy();
                have_cfg = 0;
            }
        }

        // 取文件头(主连接)
        if (sendReq(s_sock, REQ_FILE, (uint32_t)idx, 0) == -1)
        {
            perror("send req");
            break;
        }
        FileHeader hdr;
        if (recvHeader(s_sock, &hdr) == -1)
        {
            if (s_exit)
            {
                printf("用户退出\n");
                close(s_sock);
                return 0;
            }
            perror("recv hdr");
            break;
        }

        // 不符则重建
        if (!have_cfg)
        {
            if (bm.create(cfg_path, hdr.filename, hdr.file_size,
                          hdr.md5, hdr.block_nums) == -1)
                break;
        }
        else if (bm.block_nums != hdr.block_nums)
        {
            remove(cfg_path);
            bm.destroy();
            if (bm.create(cfg_path, hdr.filename, hdr.file_size,
                          hdr.md5, hdr.block_nums) == -1)
                break;
            have_cfg = 0;
        }

        // 打开本地文件(续传不截断)
        int dest_fd = -1;
        if (have_cfg)
        {
            dest_fd = open(hdr.filename, O_RDWR, 0644);
            if (dest_fd < 0)
            {
                // 续传文件丢失, 退回全新下载
                remove(cfg_path);
                bm.destroy();
                have_cfg = 0;
                if (bm.create(cfg_path, hdr.filename, hdr.file_size,
                              hdr.md5, hdr.block_nums) == -1)
                    break;
            }
        }
        if (dest_fd < 0)
            dest_fd = open(hdr.filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (dest_fd < 0)
        {
            perror("open local");
            break;
        }

        // 统计已收块数/字节(用于续传起点)
        int done = 0;
        long long done_bytes = 0;
        for (int s = 0; s < hdr.block_nums; s++)
        {
            int bs = (s == hdr.block_nums - 1)
                         ? (int)(hdr.file_size - (off_t)s * BLOCK_BYTE_SIZE)
                         : BLOCK_BYTE_SIZE;
            if (bs < 0) bs = 0;
            if (bm.has(s)) { done++; done_bytes += bs; }
        }
        if (have_cfg && done > 0)
            printf("断点续传: 已下载 %d/%d 块, 续传剩余 %d 块\n",
                   done, hdr.block_nums, hdr.block_nums - done);

        printf("开始下载 %s (%lld字节)\n",
               hdr.filename, (long long)hdr.file_size);

        Progress prog;
        prog.init("下载", hdr.block_nums, hdr.file_size, 30);
        prog.seed(done, done_bytes); // 续传起点百分比

        // 建立多连接(每线程一socket)
        int n = DOWNLOAD_THREADS;
        if (n < 1) n = 1;
        if (n > MAX_SOCKETS) n = MAX_SOCKETS;
        int *socks = (int *)calloc((size_t)n, sizeof(int));
        if (!socks)
        {
            perror("calloc");
            close(dest_fd);
            prog.clear();
            break;
        }
        socks[0] = s_sock; // 主连接作为下载连接之一
        int live = 1;
        for (int i = 1; i < n; i++)
        {
            int fd = Socket::connect(ip, port);
            if (fd == -1) break;
            if (loginOnSock(fd) == -1) { close(fd); break; }
            socks[i] = fd;
            live++;
        }
        if (live < 1) live = 1;

        DlContext ctx;
        ctx.idx = (uint32_t)idx;
        ctx.dest_fd = dest_fd;
        ctx.bm = &bm;
        ctx.prog = &prog;
        ctx.block_nums = hdr.block_nums;
        ctx.next_seq = 0;
        ctx.abort = 0;
        pthread_mutex_init(&ctx.seq_mtx, NULL);

        // 登记连接供信号中断统一关闭
        s_nsocks = 0;
        for (int i = 0; i < live; i++) s_socks[i] = socks[i];
        s_nsocks = live;

        ThreadArg *args = (ThreadArg *)calloc((size_t)(live - 1), sizeof(ThreadArg));
        pthread_t *tids = (pthread_t *)calloc((size_t)(live - 1), sizeof(pthread_t));
        if (!args || !tids)
        {
            perror("calloc");
            free(args); free(tids); free(socks);
            pthread_mutex_destroy(&ctx.seq_mtx);
            close(dest_fd);
            prog.clear();
            s_nsocks = 0;
            break;
        }
        for (int i = 0; i < live - 1; i++)
        {
            args[i].sock = socks[i + 1];
            args[i].ctx = &ctx;
            pthread_create(&tids[i], NULL, &Client::workerThread, &args[i]);
        }
        // 主线程用主连接参与下载
        workerLoop(socks[0], &ctx);
        for (int i = 0; i < live - 1; i++)
            pthread_join(tids[i], NULL);
        free(args);
        free(tids);
        pthread_mutex_destroy(&ctx.seq_mtx);
        s_nsocks = 0; // 下载结束, 解除中断登记

        // 关闭各下载连接(主连接留待末尾发退出)
        for (int i = 1; i < live; i++)
        {
            sendReq(socks[i], REQ_QUIT, 0, 0); // 通知服务器断开
            close(socks[i]);
        }

        if (s_exit)
        {
            printf("用户退出\n");
            prog.clear();
            close(dest_fd);
            bm.destroy();
            free(socks);
            close(s_sock);
            return 0;
        }

        int ok = !ctx.abort;
        if (ok)
        {
            prog.finish(); // 定格100%
            if (done > 0)
                printf("\n断点续传完成 %s\n", hdr.filename);
        }
        else
            prog.clear();

        close(dest_fd);
        bm.destroy();
        free(socks);

        if (!ok)
        {
            fprintf(stderr, "下载中断 %s\n", hdr.filename);
            break;
        }
        printf("完成 %s\n", hdr.filename);

        // 校验MD5
        unsigned char local[MD5_LEN];
        if (Md5::file(hdr.filename, local) == 0 &&
            memcmp(local, hdr.md5, MD5_LEN) == 0)
        {
            char h[MD5_LEN * 2 + 1];
            Md5::hex(local, h);
            printf("MD5校验通过 %s\n", h);
            remove(cfg_path); // 合格删配置
        }
        else
        {
            char h1[MD5_LEN * 2 + 1], h2[MD5_LEN * 2 + 1];
            Md5::hex(local, h1);
            Md5::hex(hdr.md5, h2);
            printf("MD5校验失败\n  本地 %s\n  记录 %s\n", h1, h2);
            remove(cfg_path);
            remove(hdr.filename); // 损坏删文件
        }
    }

    // 结束会话
    if (s_exit)
        printf("\n用户中断，正在退出...\n");
    else
        sendReq(s_sock, REQ_QUIT, 0, 0);
    close(s_sock);
    printf("已断开\n");
    return 0;
}
