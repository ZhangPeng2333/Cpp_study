// Socket 工具封装
/// @file socket.h
/// @brief TCP 套接字的监听/连接与精确收发封装

#ifndef CPP_COMMON_SOCKET_H
#define CPP_COMMON_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * @brief 套接字工具类
 *
 * 封装监听、接受连接、发起连接、精确收发数据,
 * 并对断连(EPIPE/EBADF)与信号中断(EINTR)做静默处理。
 */
class Socket {
public:
    /**
     * @brief 创建监听套接字并绑定端口
     * @param ip   监听 IP
     * @param port 监听端口
     * @return 监听 fd, 失败返回 -1
     */
    static int listen(const char *ip, int port);
    /**
     * @brief 接受一个新的客户端连接
     * @param listen_fd 监听 fd
     * @return 客户端 fd, 失败返回 -1
     */
    static int accept(int listen_fd);
    /**
     * @brief 连接指定服务器
     * @param ip   服务器 IP
     * @param port 服务器端口
     * @return 连接 fd, 失败返回 -1
     */
    static int connect(const char *ip, int port);
    /**
     * @brief 精确发送全部数据
     * @param fd  套接字
     * @param buf 数据缓冲区
     * @param len 数据长度
     * @return 0 成功, -1 失败(含对端断开)
     */
    static int sendAll(int fd, const void *buf, size_t len);
    /**
     * @brief 精确接收指定长度数据
     * @param fd  套接字
     * @param buf 接收缓冲区
     * @param len 期望接收长度
     * @return 0 成功, -1 失败(含对端断开)
     */
    static int recvAll(int fd, void *buf, size_t len);
    /**
     * @brief 关闭 Nagle 算法
     * @param fd 套接字
     */
    static void setNodelay(int fd);
};

#endif
