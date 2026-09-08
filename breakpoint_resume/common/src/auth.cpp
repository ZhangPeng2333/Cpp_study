// 认证头实现

#include "auth.h"

/**
 * @brief 序列化登录头到缓冲区
 * @param out 输出缓冲区(USER_SIZE+PASSWORD_SIZE+2 字节)
 * @param hdr 登录头
 *
 * 布局: username | password | op_type(1) | check(1)
 */
void Auth::pack(char *out, const LoginHeader *hdr)
{
    char *p = out;
    memcpy(p, hdr->username, USER_SIZE);
    p += USER_SIZE;
    memcpy(p, hdr->password, PASSWORD_SIZE);
    p += PASSWORD_SIZE;
    *p = (char)hdr->op_type;
    p += 1;
    *p = hdr->check;
}

/**
 * @brief 从缓冲区反序列化登录头
 * @param in  输入缓冲区
 * @param hdr 输出登录头
 */
void Auth::unpack(const char *in, LoginHeader *hdr)
{
    const char *p = in;
    memcpy(hdr->username, p, USER_SIZE);
    p += USER_SIZE;
    hdr->username[USER_SIZE - 1] = '\0';
    memcpy(hdr->password, p, PASSWORD_SIZE);
    p += PASSWORD_SIZE;
    hdr->password[PASSWORD_SIZE - 1] = '\0';
    hdr->op_type = (uint8_t)*p;
    p += 1;
    hdr->check = *p;
}
