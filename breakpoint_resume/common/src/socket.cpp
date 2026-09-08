// Socket 实现

#include "socket.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <pthread.h>

#ifndef PATH_SIZE
#define PATH_SIZE 1024 // 路径长度
#endif

/**
 * @brief 创建监听套接字并绑定端口
 * @param ip   监听 IP
 * @param port 监听端口
 * @return 监听 fd, 失败返回 -1
 */
int Socket::listen(const char *ip, int port)
{
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return -1;
    }
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // 端口复用

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(fd);
        return -1;
    }
#if 0
    addr.sin_addr.s_addr = inet_addr(argv[1]); // IP
#else
    //自动绑定所有本机网卡的地址
    addr.sin_addr.s_addr = INADDR_ANY;
#endif
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) // 绑定地址
    {
        perror("bind");
        close(fd);
        return -1;
    }
    if (::listen(fd, 5) < 0) // 开始监听
    {
        perror("listen");
        close(fd);
        return -1;
    }
    printf("服务器启动 %s:%d\n", ip, port);
    return fd;
}

/**
 * @brief 接受一个新的客户端连接
 * @param listen_fd 监听 fd
 * @return 客户端 fd, 失败返回 -1
 */
int Socket::accept(int listen_fd)
{
    struct sockaddr_in cliaddr;
    socklen_t addrlen = sizeof(cliaddr);
    int clifd = ::accept(listen_fd, (struct sockaddr *)&cliaddr, &addrlen);
    if (clifd < 0)
    {
        if (errno == EINTR || errno == EBADF)
            return -1; // 被中断
        perror("accept");
        return -1;
    }
    printf("新连接 %s:%d\n",
           inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port)); // 打印对端
    setNodelay(clifd);
    return clifd;
}

/**
 * @brief 连接指定服务器
 * @param ip   服务器 IP
 * @param port 服务器端口
 * @return 连接 fd, 失败返回 -1
 */
int Socket::connect(const char *ip, int port)
{
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(fd);
        return -1;
    }
    if (::connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("connect");
        close(fd);
        return -1;
    }
    setNodelay(fd);
    printf("已连服务器 %s:%d\n", ip, port);
    return fd;
}

/**
 * @brief 关闭 Nagle 算法
 * @param fd 套接字
 */
void Socket::setNodelay(int fd)
{
    int on = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));
}

/**
 * @brief 精确发送全部数据
 * @param fd  套接字
 * @param buf 数据缓冲区
 * @param len 数据长度
 * @return 0 成功, -1 失败(含对端断开)
 */
int Socket::sendAll(int fd, const void *buf, size_t len)
{
    const char *p = (const char *)buf;
    size_t total = 0;
    while (total < len)
    {
        ssize_t n = send(fd, p + total, len - total, 0);
        if (n < 0)
        {
            if (errno == EINTR)
                continue; // 信号中断重试
            if (errno == EBADF || errno == EPIPE)
                return -1; // 对端断开静默
            perror("send");
            return -1;
        }
        if (n == 0)
            break;
        total += (size_t)n;
    }
    return (total == len) ? 0 : -1;
}

/**
 * @brief 精确接收指定长度数据
 * @param fd  套接字
 * @param buf 接收缓冲区
 * @param len 期望接收长度
 * @return 0 成功, -1 失败(含对端断开)
 */
int Socket::recvAll(int fd, void *buf, size_t len)
{
    char *p = (char *)buf;
    size_t total = 0;
    while (total < len)
    {
        ssize_t n = recv(fd, p + total, len - total, 0);
        if (n < 0)
        {
            if (errno == EINTR)
                continue; // 信号中断重试
            if (errno == EBADF)
                return -1; // 已关闭静默
            perror("recv");
            return -1;
        }
        if (n == 0)
        {
            fprintf(stderr, "连接关闭\n"); // 对端关闭
            return -1;
        }
        total += (size_t)n;
    }
    return 0;
}
