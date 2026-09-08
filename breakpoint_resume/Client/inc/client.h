// 下载客户端封装
/// @file client.h
/// @brief 断点续传下载客户端的类封装与下载上下文声明

#ifndef CPP_CLIENT_CLIENT_H
#define CPP_CLIENT_CLIENT_H

#include <cstdint>
#include <csignal>
#include <pthread.h>
#include "protocol.h"
#include "auth.h"
#include "bitmap.h"
#include "progress.h"

#define DOWNLOAD_THREADS 8 // 并行连接数(每线程一socket)
#define MAX_SOCKETS 16     // 连接数上限

/**
 * @brief 下载上下文: 多线程共享状态
 */
struct DlContext {
    uint32_t    idx;      ///< 文件下标
    int         dest_fd;  ///< 本地目标文件 fd
    Bitmap     *bm;       ///< 断点续传位图
    Progress   *prog;     ///< 进度条
    int         block_nums; ///< 总块数
    int         next_seq; ///< 下一个待领块序号
    int         abort;    ///< 出错即停其它线程
    pthread_mutex_t seq_mtx; ///< 领取序号互斥锁
};

/**
 * @brief 下载客户端
 *
 * 多连接并发: 每个下载线程持独立套接字并各自登录,
 * 通过序号计数器分摊块任务; 支持断点续传与 MD5 校验。
 */
class Client {
public:
    /**
     * @brief 程序入口: 解析参数并启动交互
     * @param argc 参数个数
     * @param argv 参数列表(ip port)
     * @return 0 正常退出, -1 参数错误
     */
    int run(int argc, char *argv[]);

private:
    /// 全局退出标志(SIGINT 置位)
    static volatile sig_atomic_t s_exit;
    /// 主交互连接
    static int s_sock;
    /// 已登录用户名(供下载连接复用)
    static char s_user[USER_SIZE];
    /// 已登录密码(供下载连接复用)
    static char s_pass[PASSWORD_SIZE];
    /// 活动连接表(供信号处理器中断)
    static int s_socks[MAX_SOCKETS];
    /// 活动连接数
    static int s_nsocks;

    /**
     * @brief 信号处理: 置退出标志并关闭所有连接
     * @param sig 信号编号
     */
    static void sigHandler(int sig);
    /**
     * @brief 注册流程
     * @param fd 已连接套接字
     * @return 0 成功, -1 失败
     */
    static int regClient(int fd);
    /**
     * @brief 登录流程并缓存凭证
     * @param fd 已连接套接字
     * @return 0 成功, -1 失败
     */
    static int loginClient(int fd);
    /**
     * @brief 用已缓存凭证在指定连接上登录
     * @param fd 已连接套接字
     * @return 0 成功, -1 失败
     */
    static int loginOnSock(int fd);
    /**
     * @brief 接收文件列表
     * @param fd   已连接套接字
     * @param list 输出文件列表
     * @return 0 成功, -1 失败
     */
    static int recvList(int fd, FileList *list);
    /**
     * @brief 发送下载请求
     * @param fd    已连接套接字
     * @param type  请求类型(REQ_*)
     * @param index 文件下标
     * @param seq   块序号
     * @return 0 成功, -1 失败
     */
    static int sendReq(int fd, uint8_t type, uint32_t index, uint32_t seq);
    /**
     * @brief 接收文件头
     * @param fd  已连接套接字
     * @param hdr 输出文件头
     * @return 0 成功, -1 失败
     */
    static int recvHeader(int fd, FileHeader *hdr);
    /**
     * @brief 接收数据块并落盘
     * @param fd      已连接套接字
     * @param dest_fd 本地目标 fd
     * @param seq     期望块序号
     * @param bm      断点续传位图
     * @param prog    进度条
     * @return 0 成功, -1 失败
     */
    static int recvBlock(int fd, int dest_fd, int seq,
                         Bitmap *bm, Progress *prog);
    /**
     * @brief 下载线程入口
     * @param arg ThreadArg 指针(含本线程 socket 与上下文)
     * @return NULL
     */
    static void *workerThread(void *arg);
    /**
     * @brief 下载循环: 领块并发送/接收(独立连接)
     * @param sock 本线程独立连接
     * @param c    下载上下文
     */
    static void workerLoop(int sock, DlContext *c);
    /**
     * @brief 打印人类可读的文件大小
     * @param size 字节数
     */
    static void printSz(off_t size);
    /**
     * @brief 解析用户输入的文件编号
     * @param line 输入行
     * @param max  最大合法下标(文件数)
     * @return 合法下标或 -1
     */
    static int parseIdx(const char *line, int max);
    /**
     * @brief 生成配置文件路径(文件名.config)
     * @param filename 文件名
     * @param out      输出路径
     * @param n        out 长度
     */
    static void configPath(const char *filename, char *out, size_t n);
};

#endif
