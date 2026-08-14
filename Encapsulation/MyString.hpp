#ifndef MYSTRING_HPP_
#define MYSTRING_HPP_

#include <iostream>
#include <string.h>

class MyString
{
private:
    char *m_data;
    unsigned int m_len;

public:
    MyString(const char *str = NULL);
    MyString(const MyString &other);
    MyString &operator=(const MyString &other);

    ~MyString();
};

MyString::MyString(const char *str = NULL)
{
    if (str == NULL) {
        m_len = 0;
        m_data = new char[1];
        m_data[0] = '\0';
    } else {
        m_len = strlen(str);
        m_data = new char[m_len + 1];
        strcpy(m_data, str);
    }
    std::cout << "mystring 构造" << std::endl;
}

MyString::MyString(const MyString &other)
{
    m_len = other.m_len;
    m_data = new char[m_len + 1];
    strcpy(m_data, other.m_data);
    std::cout << "Mystring 拷贝构造" << std::endl;
}

MyString &MyString::operator=(const MyString &other)
{
    std::cout << "Mystring 赋值运算符" << std::endl;

    if (this == &other)
    {
        return *this;
    }

    delete[] m_data;
    m_len = other.m_len;
    m_data = new char[m_len + 1];
    strcpy(m_data, other.m_data);

    return *this;
}

MyString::~MyString()
{
    delete[] m_data;
    m_data = NULL;
    std::cout<<"mystring 析构"<<std::endl;
}

#endif // MYSTRING_HPP_