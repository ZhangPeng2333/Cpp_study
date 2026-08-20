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
		Test* t = new Test("A");
		auto_ptr<Test> apt1(t);//智能指针
		//从智能指针对象中取出被管理的资源对象
		Test* t2 = apt1.get();
		t2->show();
		//delete t2;// 错误 既然放手了，就别插手
		//解除ap1对资源的管理，ap1仅仅放弃管理权，不会销毁资源
		apt1.release();
		delete t;

		//ap2持有资源B
		auto_ptr<Test> ap2(new Test("B"));
		//解除ap2对资源的管理 并 销毁资源对象
		ap2.reset();

		auto_ptr<Test> ap3(new Test("C"));
		//ap3持有的资源从C变更为D，C销毁
		ap3.reset(new Test("D"));
		ap3.get()->show();


	}
}

#endif // 0
