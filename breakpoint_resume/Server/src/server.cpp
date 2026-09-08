// 下载服务器实现

#include "server.h"
#include "codec.h"
#include "socket.h"
#include "md5.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sqlite3.h>

#ifndef PATH_SIZE
#define PATH_SIZE 1024 // 路径长度
#endif

// 全局状态初始化
volatile sig_atomic_t Server::s_exit = 0;
int Server::s_listen = -1;
Server::Worker Server::s_workers[MAX_THREADS];
FileList Server::s_list;
pthread_mutex_t Server::s_lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief 信号处理: 置退出标志并关闭监听
 * @param sig 信号编号
 */
void Server::sigHandler(int sig)
{
    (void)sig;
    s_exit = 1;
    if (s_listen != -1)
    {
        close(s_listen);
        s_listen = -1;
    }
}

/**
 * @brief 扫描资源目录并缓存文件信息与 MD5
 * @param dir  资源目录
 * @param list 输出文件列表
 * @return 0 成功, -1 失败
 */
int Server::scanDir(const char *dir, FileList *list)
{
    list->file_count = 0;
    DIR *d = opendir(dir);
        if (d == NULL)
    {
        spdlog::error("opendir: {}", strerror(errno));
        return -1;
    }
    struct dirent *e;
    while ((e = readdir(d)) != NULL)
    {
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0)
            continue;
        char full[PATH_SIZE];
        snprintf(full, sizeof(full), "%s/%s", dir, e->d_name);

        struct stat st;
        if (stat(full, &st) != 0)
            continue;
        if (!S_ISREG(st.st_mode))
            continue;
        if (list->file_count >= FILE_LIST_SIZE)
        {
            spdlog::error("文件过多");
            break;
        }
        FileInfo *fi = &list->files[list->file_count];
        snprintf(fi->filename, sizeof(fi->filename), "%s", e->d_name);
        fi->file_size = st.st_size;
        if (Md5::file(full, fi->md5) == -1)
            spdlog::error("md5失败 {}", e->d_name);
        list->file_count++;
    }
    closedir(d);
    return 0;
}

/**
 * @brief 计算文件总块数
 * @param size 文件大小
 * @param num  输出块数(至少 1)
 * @return 0 成功, -1 失败
 */
int Server::blockCount(off_t size, int *num)
{
    if (BLOCK_BYTE_SIZE <= 0)
    {
        spdlog::error("BLOCK err: {}", strerror(errno));
        return -1;
    }
    *num = (int)((size + BLOCK_BYTE_SIZE - 1) / BLOCK_BYTE_SIZE);
    if (*num == 0)
        *num = 1;
    return 0;
}

/**
 * @brief 注册处理
 * @param hdr 登录头(含请求)
 * @param fd  客户端 fd
 * @return 0 成功, -1 失败
 */
int Server::regServer(LoginHeader *hdr, int fd)
{
    static sqlite3 *db;
    char buf[USER_SIZE + PASSWORD_SIZE + 2] = {0};
    int ret = -1;

    if (hdr->op_type != OP_REGISTER)
    {
        spdlog::error("reg 类型错");
        return -1;
    }
    ret = sqlite3_open(DB_PATH, &db);
    if (ret != SQLITE_OK)
    {
        spdlog::error("db open: {}", strerror(errno));
        return -1;
    }
    // 建表(首次运行)
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS user(username TEXT, password TEXT);", NULL, NULL, NULL);
    char *errmsg = NULL;
    char sql[SQL_SIZE] = {0};
    snprintf(sql, sizeof(sql), "insert into user values('%s','%s');",
             hdr->username, hdr->password);

    ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if (ret == SQLITE_OK)
        hdr->check = REG_OK;
    else
        hdr->check = REG_FAIL;

    Auth::pack(buf, hdr);
    ret = Socket::sendAll(fd, buf, sizeof(buf));
    if (ret == -1)
    {
        spdlog::error("reg send: {}", strerror(errno));
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return -1;
    }
    if (hdr->check == REG_FAIL)
        spdlog::warn("用户{}已存在", hdr->username);
    else
        spdlog::info("注册{}成功", hdr->username);

    sqlite3_free(errmsg);
    sqlite3_close(db);
    return (hdr->check == REG_OK) ? 0 : -1;
}

/**
 * @brief 登录处理
 * @param hdr 登录头(含请求)
 * @param fd  客户端 fd
 * @return 0 成功, -1 失败
 */
int Server::loginServer(LoginHeader *hdr, int fd)
{
    char buf[USER_SIZE + PASSWORD_SIZE + 2] = {0};
    static sqlite3 *db = NULL;
    char *errmsg = NULL;
    char sql[SQL_SIZE] = {0};
    char **resultp = NULL;
    int n_row = 0, n_col = 0;
    int ret = -1;

    if (hdr->op_type != OP_LOGIN)
    {
        spdlog::error("login 类型错");
        return -1;
    }
    ret = sqlite3_open(DB_PATH, &db);
    if (ret != SQLITE_OK)
    {
        spdlog::error("db open: {}", strerror(errno));
        return -1;
    }
    // 建表(首次运行)
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS user(username TEXT, password TEXT);", NULL, NULL, NULL);
    snprintf(sql, sizeof(sql),
             "select * from user where username = '%s' and password = '%s';",
             hdr->username, hdr->password);

    ret = sqlite3_get_table(db, sql, &resultp, &n_row, &n_col, &errmsg);
    if (ret != SQLITE_OK)
    {
        spdlog::error("SQL err: {}", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return -1;
    }
    if (n_row == 1)
    {
        char **data = resultp + n_col;
        if (strcmp(data[0], hdr->username) == 0 &&
            strcmp(data[1], hdr->password) == 0)
            hdr->check = LOG_OK;
        else
            hdr->check = LOG_FAIL;
    }
    else
    {
        hdr->check = LOG_FAIL;
    }

    Auth::pack(buf, hdr);
    ret = Socket::sendAll(fd, buf, sizeof(buf));
    if (ret == -1)
    {
        spdlog::error("login send: {}", strerror(errno));
        sqlite3_free_table(resultp);
        sqlite3_close(db);
        return -1;
    }
    if (hdr->check == LOG_OK)
        spdlog::info("登录成功: {}", hdr->username);
    else
        spdlog::warn("登录失败: {}", hdr->username);

    sqlite3_free_table(resultp);
    sqlite3_close(db);
    return (hdr->check == LOG_OK) ? 0 : -1;
}

/**
 * @brief 下发文件列表
 * @param fd   客户端 fd
 * @param list 文件列表
 * @return 0 成功, -1 失败
 */
int Server::sendList(int fd, const FileList *list)
{
    char type = MSG_LIST;
    if (Socket::sendAll(fd, &type, 1) != 0)
        return -1;

    int32_t count = (int32_t)(list->file_count < FILE_LIST_SIZE
                                  ? list->file_count : FILE_LIST_SIZE);
    char cnt_buf[4];
    Codec::putInt(cnt_buf, count);
    if (Socket::sendAll(fd, cnt_buf, 4) != 0)
        return -1;

    for (int32_t i = 0; i < count; i++)
    {
        if (Socket::sendAll(fd, list->files[i].filename, FILENAME_SIZE) != 0)
            return -1;
        char sz_buf[8];
        Codec::putLong(sz_buf, (int64_t)list->files[i].file_size);
        if (Socket::sendAll(fd, sz_buf, 8) != 0)
            return -1;
    }
    return 0;
}

/**
 * @brief 下发文件头
 * @param fd      客户端 fd
 * @param resPath 资源目录
 * @param fi      文件信息
 * @return 0 成功, -1 失败
 */
int Server::sendHeader(int fd, const char *resPath, const FileInfo *fi)
{
    int block_nums;
    if (blockCount(fi->file_size, &block_nums) == -1)
        return -1;

    // 优先复用md5
    unsigned char md5[MD5_LEN];
    int have = 0;
    for (int i = 0; i < MD5_LEN; i++)
        if (fi->md5[i]) { have = 1; break; }
    if (have)
        memcpy(md5, fi->md5, MD5_LEN);
    else
    {
        char full[PATH_SIZE];
        snprintf(full, sizeof(full), "%s/%s", resPath, fi->filename);
        if (Md5::file(full, md5) == -1)
        {
            spdlog::error("md5: {}", strerror(errno));
            return -1;
        }
    }

    char type = MSG_HEADER;
    if (Socket::sendAll(fd, &type, 1) != 0)
        return -1;
    char buf[FILENAME_SIZE + 8 + 4 + MD5_LEN];
    char *p = buf;
    memcpy(p, fi->filename, FILENAME_SIZE);
    p += FILENAME_SIZE;
    Codec::putLong(p, (int64_t)fi->file_size);
    p += 8;
    Codec::putInt(p, block_nums);
    p += 4;
    memcpy(p, md5, MD5_LEN);
    return Socket::sendAll(fd, buf, sizeof(buf));
}

/**
 * @brief 下发数据块
 * @param fd        客户端 fd
 * @param resPath   资源目录
 * @param fi        文件信息
 * @param seq       块序号
 * @param cache_fd   连接级 fd 缓存
 * @param cache_path 连接级路径缓存
 * @return 0 成功, -1 失败
 */
int Server::sendBlock(int fd, const char *resPath, const FileInfo *fi,
                      int seq, int *cache_fd, char *cache_path)
{
    int block_nums;
    if (blockCount(fi->file_size, &block_nums) == -1)
        return -1;
    if (seq < 0 || seq >= block_nums)
    {
        spdlog::error("块越界 {}/{}", seq, block_nums);
        return -1;
    }

    int size = (seq == block_nums - 1)
                   ? (int)(fi->file_size - (off_t)seq * BLOCK_BYTE_SIZE)
                   : BLOCK_BYTE_SIZE;
    if (size < 0)
        size = 0;

    char full[PATH_SIZE];
    snprintf(full, sizeof(full), "%s/%s", resPath, fi->filename);

    // 复用缓存fd
    if (*cache_fd < 0 || strcmp(cache_path, full) != 0)
    {
        if (*cache_fd >= 0)
            close(*cache_fd);
        *cache_fd = open(full, O_RDONLY);
        if (*cache_fd < 0)
        {
            spdlog::error("open src: {}", strerror(errno));
            return -1;
        }
        snprintf(cache_path, PATH_SIZE, "%s", full);
    }
    int f = *cache_fd;

    unsigned char data[BLOCK_BYTE_SIZE];
    if (size > 0)
    {
        off_t off = (off_t)seq * BLOCK_BYTE_SIZE;
        if (lseek(f, off, SEEK_SET) == (off_t)-1)
        {
            spdlog::error("lseek src: {}", strerror(errno));
            return -1;
        }
        int remain = size, got = 0;
        while (remain > 0)
        {
            int r = read(f, data + got, remain);
            if (r <= 0)
                return -1;
            got += r;
            remain -= r;
        }
    }

    char seq_buf[4], sz_buf[4];
    Codec::putInt(seq_buf, seq);
    Codec::putInt(sz_buf, size);
    if (Socket::sendAll(fd, seq_buf, 4) != 0)
        return -1;
    if (Socket::sendAll(fd, sz_buf, 4) != 0)
        return -1;
    if (size > 0 && Socket::sendAll(fd, data, size) != 0)
        return -1;

    return 0; // 服务端静默
}

/**
 * @brief 会话线程入口
 * @param arg 客户端 fd(intptr_t)
 * @return NULL
 */
void *Server::handleClient(void *arg)
{
    int fd = (int)(intptr_t)arg;

    // 接收认证
    char login_buf[USER_SIZE + PASSWORD_SIZE + 2] = {0};
    if (Socket::recvAll(fd, login_buf, sizeof(login_buf)) == -1)
    {
        spdlog::error("认证接收失败");
        close(fd);
        return NULL;
    }
    LoginHeader hdr;
    Auth::unpack(login_buf, &hdr);

    int auth = -1;
    switch (hdr.op_type)
    {
    case OP_REGISTER:
        auth = regServer(&hdr, fd);
        break;
    case OP_LOGIN:
        auth = loginServer(&hdr, fd);
        break;
    default:
        spdlog::error("未知操作 {:d}", (int)hdr.op_type);
        close(fd);
        return NULL;
    }
    if (auth == -1)
    {
        close(fd);
        return NULL;
    }

    // 用启动已扫描列表
    FileList *list = &s_list;

    // 下发列表
    if (sendList(fd, list) == -1)
    {
        close(fd);
        return NULL;
    }

    // 处理请求循环
    Req req;
    char peer[64] = "client";
    int cache_fd = -1;
    char cache_path[PATH_SIZE];
    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);
    if (getpeername(fd, (struct sockaddr *)&peeraddr, &peerlen) == 0)
        snprintf(peer, sizeof(peer), "%s:%d",
                 inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

    char rbuf[1 + 4 + 4];
    while (!s_exit)
    {
        if (Socket::recvAll(fd, rbuf, sizeof(rbuf)) == -1)
        {
            spdlog::error("收请求失败");
            break;
        }
        char t;
        int32_t idx, rc;
        Codec::getChar(rbuf, &t);
        Codec::getInt(rbuf + 1, &idx);
        Codec::getInt(rbuf + 5, &rc);
        req.type = (uint8_t)t;
        req.index = (uint32_t)idx;
        req.block_seq = (uint32_t)rc;

        if (req.type == REQ_QUIT) // 请求退出
        {
            spdlog::info("客户端结束");
            break;
        }
        if (req.type == REQ_FILE) // 请求文件
        {
            if (req.index >= list->file_count)
            {
                spdlog::error("下标越界 {}", req.index);
                continue;
            }
            FileInfo *fi = &list->files[req.index];
            spdlog::info("请求下载 {} (已收{}) <{}>",
                         fi->filename, req.block_seq, peer);
            if (sendHeader(fd, RESOURSE_PATH, fi) == -1)
            {
                spdlog::error("发送头失败 {}", fi->filename);
                break;
            }
            continue;
        }
        if (req.type == REQ_BLOCK) // 请求数据块
        {
            if (req.index >= list->file_count)
            {
                spdlog::error("下标越界 {}", req.index);
                continue;
            }
            FileInfo *fi = &list->files[req.index];
            if (sendBlock(fd, RESOURSE_PATH, fi, (int)req.block_seq,
                         &cache_fd, cache_path) == -1)
            {
                spdlog::error("发送块失败 {}", fi->filename);
                break;
            }
            continue;
        }
        spdlog::error("未知请求 {:d}", (int)req.type);
    }

    if (cache_fd >= 0)
        close(cache_fd);
    spdlog::info("关闭连接");
    close(fd);

    pthread_mutex_lock(&s_lock);
    for (int i = 0; i < MAX_THREADS; i++)
    {
        if (s_workers[i].active &&
            pthread_equal(s_workers[i].tid, pthread_self()))
        {
            s_workers[i].active = 0;
            s_workers[i].client_fd = -1;
            break;
        }
    }
    pthread_mutex_unlock(&s_lock);
    return NULL;
}

/**
 * @brief 程序入口: 解析参数并启动服务
 * @param argc 参数个数
 * @param argv 参数列表(ip port)
 * @return 0 正常退出, -1 参数错误
 */
int Server::run(int argc, char *argv[])
{
    // 配置 spdlog 日志格式(时间/级别/线程)
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%t] %v");
    spdlog::set_level(spdlog::level::info);

    if (argc < 3)
    {
        spdlog::error("usage: {} <ip> <port>", argv[0]);
        return -1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    if (port <= 0 || port > 65535)
    {
        spdlog::error("端口错误");
        return -1;
    }

    // 启动监听
    s_listen = Socket::listen(ip, port);
    if (s_listen == -1)
        return -1;

    // 启动扫描资源
    memset(&s_list, 0, sizeof(s_list));
    if (scanDir(RESOURSE_PATH, &s_list) == -1)
    {
        spdlog::error("扫描资源目录失败");
        close(s_listen);
        return -1;
    }
    spdlog::info("资源目录 {} 共 {} 文件", RESOURSE_PATH, s_list.file_count);

    signal(SIGINT, sigHandler);
    signal(SIGPIPE, SIG_IGN); // 忽略断连
    for (int i = 0; i < MAX_THREADS; i++)
        s_workers[i].active = 0;

    // 并发接收
    while (!s_exit)
    {
        int cli_fd = Socket::accept(s_listen);
        if (cli_fd == -1)
        {
            if (s_exit)
                break;
            continue;
        }
        pthread_t tid;
        if (pthread_create(&tid, NULL, &Server::handleClient,
                           (void *)(intptr_t)cli_fd) != 0)
        {
            spdlog::error("pthread_create: {}", strerror(errno));
            close(cli_fd);
            continue;
        }
        pthread_mutex_lock(&s_lock);
        for (int i = 0; i < MAX_THREADS; i++)
        {
            if (!s_workers[i].active)
            {
                s_workers[i].tid = tid;
                s_workers[i].client_fd = cli_fd;
                s_workers[i].active = 1;
                break;
            }
        }
        pthread_mutex_unlock(&s_lock);
    }

    // 清理
    int active = 0;
    pthread_mutex_lock(&s_lock);
    for (int i = 0; i < MAX_THREADS; i++)
        if (s_workers[i].active)
            active++;
    pthread_mutex_unlock(&s_lock);

    if (active > 0)
        spdlog::info("收到 Ctrl+C，正在断开 {} 个已连接客户端...", active);

    // 断开所有客户端
    pthread_mutex_lock(&s_lock);
    for (int i = 0; i < MAX_THREADS; i++)
    {
        if (s_workers[i].active && s_workers[i].client_fd != -1)
        {
            close(s_workers[i].client_fd);
            s_workers[i].client_fd = -1;
        }
    }
    pthread_mutex_unlock(&s_lock);

    // 等待线程结束
    for (int i = 0; i < MAX_THREADS; i++)
    {
        if (s_workers[i].active)
        {
            pthread_join(s_workers[i].tid, NULL);
            s_workers[i].active = 0;
        }
    }
    if (s_listen != -1)
        close(s_listen);
    spdlog::info("服务器已退出");
    return 0;
}
