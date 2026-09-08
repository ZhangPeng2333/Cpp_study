// 下载服务器封装
/// @file server.h
/// @brief 断点续传下载服务器的类封装与全局状态声明

#ifndef CPP_SERVER_SERVER_H
#define CPP_SERVER_SERVER_H

#include <cstdint>
#include <csignal>
#include <pthread.h>
#include "protocol.h"
#include "auth.h"
#include "progress.h"
#include <spdlog/spdlog.h>

#ifndef RESOURSE_PATH
#define RESOURSE_PATH "resourse" // 资源目录
#endif

#define MAX_THREADS 64 // 最大线程

/**
 * @brief 下载服务器
 *
 * 启动扫描资源目录并缓存文件列表与 MD5, 监听端口后
 * 每客户端分配一个会话线程; 支持断点续传、单连接
 * 多线程下载请求的无序响应。
 */
class Server {
public:
    /**
     * @brief 程序入口: 解析参数并启动服务
     * @param argc 参数个数
     * @param argv 参数列表(ip port)
     * @return 0 正常退出, -1 参数错误
     */
    int run(int argc, char *argv[]);

private:
    /// 会话线程记录(用于优雅退出时清理)
    struct Worker {
        pthread_t tid;     ///< 线程 id
        int client_fd;     ///< 客户端 fd
        int active;        ///< 是否活跃
    };

    /// 全局退出标志(SIGINT 置位)
    static volatile sig_atomic_t s_exit;
    /// 监听套接字
    static int s_listen;
    /// 工作线程表
    static Worker s_workers[MAX_THREADS];
    /// 启动扫描的全局文件列表(只读)
    static FileList s_list;
    /// 全局互斥锁
    static pthread_mutex_t s_lock;

    /**
     * @brief 信号处理: 置退出标志并关闭监听
     * @param sig 信号编号
     */
    static void sigHandler(int sig);
    /**
     * @brief 会话线程入口
     * @param arg 客户端 fd(intptr_t)
     * @return NULL
     */
    static void *handleClient(void *arg);
    /**
     * @brief 注册处理
     * @param hdr 登录头(含请求)
     * @param fd  客户端 fd
     * @return 0 成功, -1 失败
     */
    static int regServer(LoginHeader *hdr, int fd);
    /**
     * @brief 登录处理
     * @param hdr 登录头(含请求)
     * @param fd  客户端 fd
     * @return 0 成功, -1 失败
     */
    static int loginServer(LoginHeader *hdr, int fd);
    /**
     * @brief 下发文件列表
     * @param fd   客户端 fd
     * @param list 文件列表
     * @return 0 成功, -1 失败
     */
    static int sendList(int fd, const FileList *list);
    /**
     * @brief 下发文件头
     * @param fd     客户端 fd
     * @param resPath 资源目录
     * @param fi     文件信息
     * @return 0 成功, -1 失败
     */
    static int sendHeader(int fd, const char *resPath, const FileInfo *fi);
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
    static int sendBlock(int fd, const char *resPath, const FileInfo *fi,
                         int seq, int *cache_fd, char *cache_path);
    /**
     * @brief 扫描资源目录
     * @param dir  资源目录
     * @param list 输出文件列表
     * @return 0 成功, -1 失败
     */
    static int scanDir(const char *dir, FileList *list);
    /**
     * @brief 计算总块数
     * @param size 文件大小
     * @param num  输出块数
     * @return 0 成功, -1 失败
     */
    static int blockCount(off_t size, int *num);
};

#endif
