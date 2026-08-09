#include<iostream>
#include<string.h>
using namespace std;

class Mystring
{
private:
    char* m_data;
    unsigned int m_len;
public:
    Mystring(const char* src="")
    {
        m_len = strlen(src);
        m_data = new char[m_len+1];
        strcpy(m_data,src);
        std::cout<<"mystring 构造"<<std::endl;

    }

    ~Mystring()
    {
        delete[] m_data;
        m_data = NULL;
        std::cout<<"mystring 析构"<<std::endl;
    }

    //深拷贝
    Mystring(const Mystring& other){
        m_len = other.m_len;
        m_data = new char[m_len+1];
        strcpy(m_data,other.m_data);
        std::cout<<"Mystring 拷贝构造"<<std::endl;

    }

    //赋值运算符重载
    Mystring& operator=(const Mystring& other){
        std::cout<<"Mystring 赋值运算符"<<std::endl;

        if (this == &other)
        {
            return *this;
        }

        delete[] m_data;
        m_len = other.m_len;
        m_data = new char[m_len+1];
        strcpy(m_data,other.m_data);

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Mystring& str);
};

std::ostream& operator<<(std::ostream& out, const Mystring& str){
    out << str.m_data <<std::endl;
    return out;
}

void test1(void){
    Mystring* str_a = new Mystring("Hello World!");
    Mystring* str_b = new Mystring(*str_a);
    Mystring* str_c = new Mystring("Hello Cpp!");

    std::cout<<*str_a;
    std::cout<<*str_b;
    std::cout<<*str_c;

    delete str_a;
    delete str_b;
    delete str_c;
}

int main(void)
{
    test1();
    return 0;
}
