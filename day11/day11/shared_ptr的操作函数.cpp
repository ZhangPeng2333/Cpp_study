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
	shared_ptr<Test> sp4;
	// 不持有资源(因为未new或make_shared)，返回false
	cout << sp4.operator bool() << endl;
	cout << sp4.get() << endl; // 00000000
	{
		cout << "{" << endl;
		shared_ptr<Test> sp1 = make_shared<Test>("A");
		// 判断是否是独自持有资源
		cout << sp1.unique() << endl; // 1
		shared_ptr<Test> sp2(sp1);
		cout << sp1.unique() << endl; // 0
		sp4 = sp2;
		// 获得资源对象的引用
		Test &t = sp2.operator *();
		t.show();
		// 如果持有资源，则返回true
		cout << sp2.operator bool() << endl;
		cout << "}" << endl;
	}
	cout << "主函数执行结束" << endl;
	return 0;
}
#endif // 0
