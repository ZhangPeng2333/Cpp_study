// 公共协议定义
/// @file protocol.h
/// @brief 客户端与服务端共用的线格式与结构体定义

#ifndef CPP_COMMON_PROTOCOL_H
#define CPP_COMMON_PROTOCOL_H

#include <cstdint>
#include <cstring>
#include <sys/types.h>

#ifndef FILENAME_SIZE
#define FILENAME_SIZE 512 ///< 文件名最大长度
#endif
#ifndef BLOCK_BYTE_SIZE
#define BLOCK_BYTE_SIZE (256 * 1024) ///< 单块字节数(256KB)
#endif
#ifndef FILE_LIST_SIZE
#define FILE_LIST_SIZE 256 ///< 文件列表容量
#endif
#ifndef MD5_LEN
#define MD5_LEN 16 ///< MD5 摘要字节数
#endif

/// 消息类型: 列表/文件头
#define MSG_LIST    1 ///< 下发文件列表
#define MSG_HEADER  2 ///< 下发文件头
/// 客户端请求类型
#define REQ_FILE    1 ///< 请求文件头
#define REQ_QUIT    2 ///< 请求退出
#define REQ_BLOCK   3 ///< 请求数据块
/// 认证消息类型(预留, 实际用 LoginHeader.op_type)
#define MSG_REG     0x01 ///< 注册消息(预留)
#define MSG_LOGIN   0x02 ///< 登录消息(预留)

/// 单文件信息
struct FileInfo {
    char          filename[FILENAME_SIZE]; ///< 文件名
    off_t         file_size;               ///< 文件字节数
    unsigned char md5[MD5_LEN];            ///< MD5 摘要(启动算好复用)
};

/// 文件列表
struct FileList {
    uint32_t file_count;            ///< 实际文件数
    FileInfo files[FILE_LIST_SIZE]; ///< 文件数组
};

/// 文件头(下发给客户端)
struct FileHeader {
    char          filename[FILENAME_SIZE]; ///< 文件名
    off_t         file_size;               ///< 文件字节数
    int32_t       block_nums;              ///< 总块数
    unsigned char md5[MD5_LEN];            ///< MD5 摘要
};

/// 下载请求(客户端->服务端)
struct Req {
    uint8_t  type;      ///< 请求类型(REQ_*)
    uint32_t index;     ///< 文件下标
    uint32_t block_seq; ///< 块序号
};

/// 数据块(线格式参考, 服务端以 seq+size+data 三段发送)
struct Chunk {
    int           seq;  ///< 块序号
    int           size; ///< 本块字节数
    unsigned char data[BLOCK_BYTE_SIZE]; ///< 块数据
};

#endif
