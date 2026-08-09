#if 0
#include<iostream>
#include<string>
using namespace std; 
//成员变量和成员函数是分开存储的
//this指针指向被调用的成员函数所属对象
//隐含在每一个非静态成员函数的一种指针，不须定义
//用途：当形参和成员变量同名时，可用this指针区分
//返回对象本身，用*this
class person {
public:
	person(int age) {//构造函数初始化对象
		this->age = age;
	}
	person& personaddage(person& p) {
		this->age += p.age;//所调用这个函数的对象的年龄加上所输入的年龄=所调用这个函数的对象的年龄
		return *this;
	}//返回本体，用引用的方式返回
	int age;
};

void test1() //测试案例
{
	person p1(10);
	person p2(10);
	p2.personaddage(p1);//p2调用函数personaddage,结果为20
	//执行完函数如果返回调用函数的对象，则可以实现无限增加年龄
	p2.personaddage(p1).personaddage(p1).personaddage(p1);
	cout << p2.age << endl;//结果为40
}

//int main() {
//	test1();
//	system("pause");
//	return 0;
//}
#endif