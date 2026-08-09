// mutex.hpp
#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include <cstdio>

class Mutex {
private:
    pthread_mutex_t m_mutex;

public:
    Mutex() {
        pthread_mutex_init(&m_mutex, nullptr);
        printf("Mutex 初始化完成\n");
    }

    ~Mutex() {
        pthread_mutex_destroy(&m_mutex);
        printf("Mutex 销毁完成\n");
    }
    void lock() {
        pthread_mutex_lock(&m_mutex);
        printf("加锁成功\n");
    }

    void unlock() {
        pthread_mutex_unlock(&m_mutex);
        printf("解锁成功\n");
    }

    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;
};

#endif