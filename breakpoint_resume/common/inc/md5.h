// MD5 工具封装 OpenSSL
/// @file md5.h
/// @brief 基于 OpenSSL 的文件 MD5 计算与十六进制转换

#ifndef CPP_COMMON_MD5_H
#define CPP_COMMON_MD5_H

#include <cstddef>
#include <cstdint>

#ifndef MD5_LEN
#define MD5_LEN 16 ///< 摘要字节数
#endif

/**
 * @brief MD5 工具类
 *
 * 大文件优先用 mmap 计算摘要, 失败时回退为缓冲读取,
 * 同时提供二进制的十六进制字符串转换。
 */
class Md5 {
public:
    /**
     * @brief 计算文件 MD5
     * @param path 文件路径
     * @param out  输出 16 字节摘要
     * @return 0 成功, -1 失败
     */
    static int file(const char *path, unsigned char out[MD5_LEN]);
    /**
     * @brief 二进制摘要转十六进制串
     * @param md5 16 字节摘要
     * @param hex 输出缓冲区(至少 33 字节)
     */
    static void hex(const unsigned char *md5, char *hex);
};

#endif
