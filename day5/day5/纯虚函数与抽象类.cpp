#if 0
#include<iostream>
using namespace std;

class Base
{
public:
	virtual void func() = 0;//纯虚函数
};
// 只要有纯虚函数的类就是抽象类
// 其子类必须重写父类所有纯虚函数 否则也是抽象类
// 抽象类无法实例化对象

class Son : public Base {
public:
	virtual void func() {
		cout << "func\n";

	}

};

void test01() {
	Base * base = NULL;
	// base = new Base;
	base = new Son;
	base->func();
	delete base;
}

int main() {

	test01();

	system("pause");

	return 0;
}

#endif // 0
