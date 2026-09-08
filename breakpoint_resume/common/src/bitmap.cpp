// 位图实现

#include "bitmap.h"
#include "codec.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief 位图构造函数, 初始化字段与互斥锁
 */
Bitmap::Bitmap()
{
    block_nums = 0;
    count = 0;
    bits = NULL;
    fd = -1;
    flush_cnt = 0;
    pthread_mutex_init(&mtx, NULL);
}

/**
 * @brief 位图析构函数, 释放资源并销毁互斥锁
 */
Bitmap::~Bitmap()
{
    destroy();
    pthread_mutex_destroy(&mtx);
}

/**
 * @brief 新建并初始化配置文件
 * @param path       配置路径
 * @param filename   文件名
 * @param size       文件大小
 * @param md5        文件 MD5
 * @param block_nums 总块数
 * @return 0 成功, -1 失败
 */
int Bitmap::create(const char *path, const char *filename, off_t size,
                   const unsigned char *md5, int block_nums)
{
    int f = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (f < 0)
    {
        perror("config");
        return -1;
    }
    char hdr[CFG_HDR_SIZE];
    memset(hdr, 0, sizeof(hdr));
    memcpy(hdr, filename, FILENAME_SIZE);
    Codec::putLong(hdr + FILENAME_SIZE, (int64_t)size);
    memcpy(hdr + FILENAME_SIZE + 8, md5, MD5_LEN);
    Codec::putInt(hdr + FILENAME_SIZE + 8 + MD5_LEN, block_nums);
    if (write(f, hdr, sizeof(hdr)) != (ssize_t)sizeof(hdr)) // 写配置头
    {
        perror("cfg hdr");
        close(f);
        return -1;
    }
    int bmsize = cfg_bitmap_size(block_nums);
    if (ftruncate(f, (off_t)CFG_HDR_SIZE + bmsize) != 0) // 扩展文件
    {
        perror("cfg trunc");
        close(f);
        return -1;
    }
    this->block_nums = block_nums;
    count = 0;
    flush_cnt = 0;
    bits = (unsigned char *)calloc((size_t)bmsize, 1);
    if (!bits)
    {
        close(f);
        return -1;
    }
    fd = f;
    return 0;
}

/**
 * @brief 载入已有配置文件
 * @param path   配置路径
 * @param filename 输出文件名(缓冲区)
 * @param fn_sz 文件名缓冲区长度
 * @param size  输出文件大小
 * @param md5   输出文件 MD5
 * @return 0 成功, -1 失败
 */
int Bitmap::load(const char *path, char *filename, size_t fn_sz,
                 off_t *size, unsigned char *md5)
{
    int f = open(path, O_RDWR);
    if (f < 0)
        return -1;
    char hdr[CFG_HDR_SIZE];
    if (read(f, hdr, sizeof(hdr)) != (ssize_t)sizeof(hdr)) // 读配置头
    {
        close(f);
        return -1;
    }
    memcpy(filename, hdr, FILENAME_SIZE);
    filename[FILENAME_SIZE - 1] = '\0';
    if (fn_sz > 0 && fn_sz <= FILENAME_SIZE)
        filename[fn_sz - 1] = '\0';
    int64_t sz;
    Codec::getLong(hdr + FILENAME_SIZE, &sz);
    *size = (off_t)sz;
    memcpy(md5, hdr + FILENAME_SIZE + 8, MD5_LEN);
    int bn;
    Codec::getInt(hdr + FILENAME_SIZE + 8 + MD5_LEN, &bn);
    if (bn <= 0)
    {
        close(f);
        return -1;
    }
    int bmsize = cfg_bitmap_size(bn);
    unsigned char *b = (unsigned char *)malloc((size_t)bmsize);
    if (!b)
    {
        close(f);
        return -1;
    }
    if (pread(f, b, bmsize, (off_t)CFG_HDR_SIZE) != (ssize_t)bmsize) // 读位图
    {
        free(b);
        close(f);
        return -1;
    }
    int cnt = 0;
    for (int i = 0; i < bn; i++) // 统计已收
        if (b[i >> 3] & (1 << (i & 7)))
            cnt++;
    block_nums = bn;
    count = cnt;
    flush_cnt = 0;
    bits = b;
    fd = f;
    return 0;
}

/**
 * @brief 标记某块已接收
 * @param seq 块序号
 * @return 0 成功, -1 失败
 */
int Bitmap::set(int seq)
{
    if (!bits || seq < 0 || seq >= block_nums)
        return -1;
    pthread_mutex_lock(&mtx);
    int byte = seq >> 3;
    int bit = 1 << (seq & 7);
    if (bits[byte] & bit)
    {
        pthread_mutex_unlock(&mtx);
        return 0;
    }
    bits[byte] |= bit;
    count++;
    if (++flush_cnt >= 256) // 累计满批刷盘
    {
        flush_cnt = 0;
        size_t sz = (size_t)cfg_bitmap_size(block_nums);
        if (pwrite(fd, bits, sz, (off_t)CFG_HDR_SIZE) != (ssize_t)sz)
            perror("cfg sync");
    }
    pthread_mutex_unlock(&mtx);
    return 0;
}

/**
 * @brief 查询某块是否已接收
 * @param seq 块序号
 * @return 1 已收, 0 未收或越界
 */
int Bitmap::has(int seq)
{
    if (!bits || seq < 0 || seq >= block_nums)
        return 0;
    pthread_mutex_lock(&mtx);
    int h = (bits[seq >> 3] & (1 << (seq & 7))) ? 1 : 0;
    pthread_mutex_unlock(&mtx);
    return h;
}

/**
 * @brief 释放资源并刷盘残余位图
 */
void Bitmap::destroy()
{
    if (fd >= 0)
    {
        if (bits && flush_cnt > 0)
        {
            size_t sz = (size_t)cfg_bitmap_size(block_nums);
            if (pwrite(fd, bits, sz, (off_t)CFG_HDR_SIZE) != (ssize_t)sz)
                perror("cfg sync");
        }
        close(fd);
        fd = -1;
    }
    if (bits)
    {
        free(bits);
        bits = NULL;
    }
}
