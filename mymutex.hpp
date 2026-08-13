// mutex.hpp
#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include <cstdio>

class Mutex
{

public:
    Mutex() : 
    m_mutex(-1)
    {

    }
    bool init()
    {
        int ret = -1;
        ret = pthread_mutex_init(&m_mutex, nullptr);
        // if(ret)
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&m_mutex);
        printf("Mutex 销毁完成\n");
    }
    void lock()
    {
        pthread_mutex_lock(&m_mutex);
        printf("加锁成功\n");
    }

    void unlock()
    {
        pthread_mutex_unlock(&m_mutex);
        printf("解锁成功\n");
    }

private:
    Mutex(const Mutex &) = delete;            // 拷贝构造
    Mutex &operator=(const Mutex &) = delete; // 赋值函数

private:
    pthread_mutex_t m_mutex;
};

#endif