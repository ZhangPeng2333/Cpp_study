// 收块位图封装 断点续传
/// @file bitmap.h
/// @brief 断点续传位图: 记录已下载块并实现配置持久化

#ifndef CPP_COMMON_BITMAP_H
#define CPP_COMMON_BITMAP_H

#include <cstddef>
#include <cstdint>
#include <sys/types.h>
#include <pthread.h>
#include "protocol.h"

/// 配置文件头长度: 文件名+大小+MD5+块数
#define CFG_HDR_SIZE (FILENAME_SIZE + 8 + MD5_LEN + 4)
/// 计算 n 块所需位图字节数
#define cfg_bitmap_size(n) (((n) + 7) / 8)

/**
 * @brief 断点续传位图
 *
 * 用位图记录每个块是否已接收, 配置落盘以支持断点续传,
 * 批量累积满 256 块才刷盘以减少 IO。
 */
class Bitmap {
public:
    int            block_nums; ///< 块总数
    int            count;      ///< 已接收块数
    unsigned char *bits;       ///< 位图指针
    int            fd;         ///< 配置文件 fd
    int            flush_cnt;  ///< 待刷盘计数
    pthread_mutex_t mtx;       ///< 位图读写互斥锁

    Bitmap();
    ~Bitmap();

    /**
     * @brief 新建并初始化配置文件
     * @param path       配置路径
     * @param filename   文件名
     * @param size       文件大小
     * @param md5        文件 MD5
     * @param block_nums 总块数
     * @return 0 成功, -1 失败
     */
    int create(const char *path, const char *filename, off_t size,
               const unsigned char *md5, int block_nums);
    /**
     * @brief 载入已有配置文件
     * @param path   配置路径
     * @param filename 输出文件名(缓冲区)
     * @param fn_sz 文件名缓冲区长度
     * @param size  输出文件大小
     * @param md5   输出文件 MD5
     * @return 0 成功, -1 失败
     */
    int load(const char *path, char *filename, size_t fn_sz,
             off_t *size, unsigned char *md5);
    /**
     * @brief 标记某块已接收
     * @param seq 块序号
     * @return 0 成功, -1 失败
     */
    int set(int seq);
    /**
     * @brief 查询某块是否已接收
     * @param seq 块序号
     * @return 1 已收, 0 未收或越界
     */
    int has(int seq);
    /**
     * @brief 返回已接收块数
     * @return 已接收块数
     */
    int countReceived() const { return count; }
    /**
     * @brief 释放资源并刷盘残余位图
     */
    void destroy();

private:
    Bitmap(const Bitmap &);            ///< 禁止拷贝构造
    Bitmap &operator=(const Bitmap &); ///< 禁止赋值
};

#endif
