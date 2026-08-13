#if 0
#include <iostream>
using namespace std;

class Base {
public:
	virtual void func() { cout << "Base::func" << endl; }  // virtual -> 可覆盖
	void func2() { cout << "Base::func2" << endl; }        // 非virtual -> 可隐藏
};

class Derived : public Base {
public:
	void func() override { cout << "Derived::func" << endl; }   // 覆盖
	void func2() { cout << "Derived::func2" << endl; }          // 隐藏（重定义）
};

int main() {
	Derived d;
	Base* p = &d;

	cout << "--- 直接调用对象 ---" << endl;
	d.func();    // 调用自己的（覆盖）
	d.func2();   // 调用自己的（隐藏）

	cout << "--- 父类指针指向子类 ---" << endl;
	p->func();   // 调子类（覆盖，多态）
	p->func2();  // 调父类（隐藏，非多态）

	return 0;
}
#endif