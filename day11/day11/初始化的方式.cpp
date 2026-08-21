#if 0
#include <iostream>
#include <memory>
#include <string>
using namespace std;
class Test
{
private:
	string name;
public:
	Test(string name) :name(name)
	{
		cout << name << "构造函数" << endl;
	}
	void show()
	{
		cout << name << "成员函数" << endl;
	}
	~Test()
	{
		cout << name << "析构函数" << endl;
	}
};
int main()
{
	{
		// 使用new来初始化
		shared_ptr<Test> sp1(new Test("A"));
		// 使用make_shared函数来初始化
		shared_ptr<Test> sp2 = make_shared<Test>("B");
		sp1.get()->show();
		sp2.get()->show();
	}
	cout << "主函数执行结束" << endl;
	return 0;
}
#endif // 0
