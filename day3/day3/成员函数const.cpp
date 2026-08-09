#if 0
#include<iostream>
#include<string>
using namespace std; 
//常函数和常对象 const修饰后这样叫成员函数和对象//常对象只能调用常函数.常对象不能修改 
class person {
public:
	void showperson() const //在成员函数后加const，修饰的是this指向，
	{
		m_b = 100;
	}
	void func() {
		m_a = 100;
	}
	int m_a;
	mutable int m_b;//特殊变量，即使是在常函数中也可以修改这个值的大小
};

void test1() {
	const person p;
	//p.m_a = 100；错误
	p.m_b = 100;//正确，因为这里m_b是一个特殊的变量，可以修改，在常对象下可以修改。
	//p.func();不允许，不正确，常对象不可以调用普通函数，因为普通函数可以修改属性，而常对象要求不能修改属性
}

//int main() {
//	test1();
//	system("pause");
//	return 0;
//}
#endif