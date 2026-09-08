// 认证头封装 登录注册
/// @file auth.h
/// @brief 登录/注册报文的封装、枚举与账号库路径

#ifndef CPP_COMMON_AUTH_H
#define CPP_COMMON_AUTH_H

#include <cstdint>
#include <cstring>

#define USER_SIZE 32  ///< 用户名长度
#define PASSWORD_SIZE 64 ///< 密码长度
#define DB_PATH "my.db" ///< 本地账号库路径
#define SQL_SIZE 256    ///< SQL 缓冲长度

/// 登录/注册结果枚举(数值须与 C 版一致以便互通)
enum LoginType {
    REG_FAIL = 1, ///< 注册失败
    REG_OK,       ///< 注册成功
    LOG_FAIL,     ///< 登录失败
    LOG_OK,       ///< 登录成功
    AUTH_UNK      ///< 未知
};

#define OP_REGISTER 1 ///< 操作: 注册
#define OP_LOGIN    2 ///< 操作: 登录

/// 登录/注册报文头
struct LoginHeader {
    char   username[USER_SIZE]; ///< 用户名
    char   password[PASSWORD_SIZE]; ///< 密码
    uint8_t op_type; ///< 操作类型(OP_*)
    char   check;    ///< 返回结果(LoginType)
};

/**
 * @brief 认证报文编解码工具类
 */
class Auth {
public:
    /**
     * @brief 序列化登录头到缓冲区
     * @param out 输出缓冲区(USER_SIZE+PASSWORD_SIZE+2 字节)
     * @param hdr 登录头
     */
    static void pack(char *out, const LoginHeader *hdr);
    /**
     * @brief 从缓冲区反序列化登录头
     * @param in  输入缓冲区
     * @param hdr 输出登录头
     */
    static void unpack(const char *in, LoginHeader *hdr);
};

#endif
