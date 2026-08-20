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
		unique_ptr<Test> up1(new Test("A"));
		//显式调用拷贝函数
		//unique_ptr<Test> up2(up1);//错误 unique不让
		//unique_ptr<Test> up3 = up2;错误 同理
		unique_ptr<Test> up4;
		//赋值运算符
		//up4 = up1;//错误
		//之前的复制语义结合move函数仍然可以转移控制权
		unique_ptr<Test> up2(move(up1));
		unique_ptr<Test> up3 = move(up2);
		up4 = move(up3);
	}
	cout << "主函数执行结束" << endl;
	return 0;
}
#endif // 0
