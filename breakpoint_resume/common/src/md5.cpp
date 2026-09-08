// MD5 实现 mmap加速

#include "md5.h"
#include <cstdio>
#include <cstring>
#define OPENSSL_SUPPRESS_DEPRECATED
#include <openssl/md5.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

/**
 * @brief 计算文件 MD5
 * @param path 文件路径
 * @param out  输出 16 字节摘要
 * @return 0 成功, -1 失败
 *
 * 文件大于 0 字节时优先用 mmap 映射后一次更新摘要,
 * mmap 失败则回退为 256KB 缓冲读取。
 */
int Md5::file(const char *path, unsigned char out[MD5_LEN])
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return -1;
    struct stat st;
    if (fstat(fd, &st) != 0)
    {
        close(fd);
        return -1;
    }
    MD5_CTX ctx;
    MD5_Init(&ctx);
    int ret = 0;
    if (st.st_size > 0)
    {
        void *m = mmap(NULL, (size_t)st.st_size,
                       PROT_READ, MAP_PRIVATE, fd, 0);
        if (m == MAP_FAILED)
        {
            // 回退缓冲读
            unsigned char buf[256 * 1024];
            ssize_t n;
            while ((n = read(fd, buf, sizeof(buf))) > 0)
                MD5_Update(&ctx, buf, (size_t)n);
            if (n < 0)
                ret = -1;
        }
        else
        {
            MD5_Update(&ctx, m, (size_t)st.st_size); // 映射区更新
            munmap(m, (size_t)st.st_size);
        }
    }
    close(fd);
    if (ret == 0)
        MD5_Final(out, &ctx);
    return ret;
}

/**
 * @brief 二进制摘要转十六进制串
 * @param md5 16 字节摘要
 * @param hex 输出缓冲区(至少 33 字节)
 */
void Md5::hex(const unsigned char *md5, char *hex)
{
    const char *m = "0123456789abcdef";
    for (int i = 0; i < MD5_LEN; i++)
    {
        hex[i * 2] = m[(md5[i] >> 4) & 0xf];
        hex[i * 2 + 1] = m[md5[i] & 0xf];
    }
    hex[MD5_LEN * 2] = '\0';
}
