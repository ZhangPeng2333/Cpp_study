// 基础序列化 网络序
/// @file codec.h
/// @brief 整数与字节序的编解码工具(统一为网络字节序)

#ifndef CPP_COMMON_CODEC_H
#define CPP_COMMON_CODEC_H

#include <cstdint>
#include <cstring>
#include <arpa/inet.h>
#include <endian.h>

/**
 * @brief 字节序编解码工具类
 *
 * 提供 1/2/4/8 字节整数与网络字节序之间的互转,
 * 所有方法均为静态方法, 调用方负责保证缓冲区长度足够。
 */
class Codec {
public:
    /// 写入单字节
    static void putChar(char *buf, char v) { *buf = v; }
    /// 读出单字节
    static void getChar(const char *buf, char *v) { *v = *buf; }

    /**
     * @brief 写入 16 位整数(转网络序)
     * @param buf 目标缓冲区(至少 2 字节)
     * @param v   待写入值
     */
    static void putShort(char *buf, int16_t v) {
        uint16_t net = htons((uint16_t)v);
        memcpy(buf, &net, sizeof(net));
    }
    /**
     * @brief 读出 16 位整数(转主机序)
     * @param buf 源缓冲区(至少 2 字节)
     * @param v   输出参数, 接收解析值
     */
    static void getShort(const char *buf, int16_t *v) {
        uint16_t net;
        memcpy(&net, buf, sizeof(net));
        *v = (int16_t)ntohs(net);
    }

    /**
     * @brief 写入 32 位整数(转网络序)
     * @param buf 目标缓冲区(至少 4 字节)
     * @param v   待写入值
     */
    static void putInt(char *buf, int32_t v) {
        uint32_t net = htonl((uint32_t)v);
        memcpy(buf, &net, sizeof(net));
    }
    /**
     * @brief 读出 32 位整数(转主机序)
     * @param buf 源缓冲区(至少 4 字节)
     * @param v   输出参数, 接收解析值
     */
    static void getInt(const char *buf, int32_t *v) {
        uint32_t net;
        memcpy(&net, buf, sizeof(net));
        *v = (int32_t)ntohl(net);
    }

    /**
     * @brief 写入 64 位整数(转网络序)
     * @param buf 目标缓冲区(至少 8 字节)
     * @param v   待写入值
     */
    static void putLong(char *buf, int64_t v) {
        uint64_t net = htobe64((uint64_t)v);
        memcpy(buf, &net, sizeof(net));
    }
    /**
     * @brief 读出 64 位整数(转主机序)
     * @param buf 源缓冲区(至少 8 字节)
     * @param v   输出参数, 接收解析值
     */
    static void getLong(const char *buf, int64_t *v) {
        uint64_t net;
        memcpy(&net, buf, sizeof(net));
        *v = (int64_t)be64toh(net);
    }
};

#endif
