#if 0
#include<iostream>
#include<string>

using namespace std;
//成员函数和成员变量分开储存
// 只有非静态的成员变量才属于类的对象 
class person
{
public:
	int m_a;
	//非静态，属于类的对象上    
	static int m_b;
	void func()
	{//非静态成员函数，不属于类的对象     
	}
	static void test() {
		//静态成员函数，只有一份，不属于类的对象上     
	}
};
int person::m_b = 0;
void test1()
//测试案例
{
	person p;
	cout << sizeof(p) << endl;
	//空对象所占内存为1    
	//因为c++编译器，会给每个空对象分配一个空间，为了区分空对象内存的位置    
	//每个空对象都应该有一个独一无二的内存地址    
	//有一个int成员，则对象所占空间为4    
	//空对象为1，非空对象为类里属性成员所占用的空间    
	//添加一个静态成员后发现所占内存空间仍是4，没改变    
	//再添加一个非静态成员函数，内存还没变，仍为4，不属于类的对象    
	//再加一个静态成员函数，内存仍为4，静态成员变量不属于类的对象上。
}
//int main(){ 
//	test1();    
//	system("pause");    
//	return 0; 
//}
#endif