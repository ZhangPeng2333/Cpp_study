#if 0
#include<iostream>
#include<string>
#include<memory>
using namespace std;

class Test {
private:
	string name;
public:
	Test(string name) :
		name(name) {
		cout << name << "构造函数" << endl;

	}

	void show() {
		cout << name << "成员函数" << endl;

	}

	~Test() {
		cout << name << "析构函数" << endl;
	}

};

int main() {
	{
		auto_ptr<Test> ap1(new Test("A"));
		// 显式调用拷贝构造函数
		auto_ptr<Test> ap2(ap1);
		// 隐式调用拷贝构造函数
		auto_ptr<Test> ap3 = ap2;

		auto_ptr<Test> ap4;
		ap4 = ap3;//赋值运算符
		//指针转移
		cout << ap1.get() << endl;
		cout << ap2.get() << endl;
		cout << ap3.get() << endl;
		cout << ap4.get() << endl;
		/*	00000000
			00000000
			00000000
			008FF490
			*/

			//如果忘记已经转移了
			//ap1.get()->show();//报错
	}
}
#endif // 0
