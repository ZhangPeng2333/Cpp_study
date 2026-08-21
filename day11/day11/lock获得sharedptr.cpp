#if 0
/*
可以从weak_ptr中通过lock()获得shared_ptr对象，从而持有资源。如果对象已经被销毁，lock() 将返回
一个空的 shared_ptr。
*/
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
	shared_ptr<Test> sp1 = make_shared<Test>("A");
	weak_ptr<Test> wp1(sp1);
	{
		cout << "{" << endl;
		cout << wp1.use_count() << endl; // 1
		// 通过wp1来获得shared_ptr对象
		shared_ptr<Test> sp2 = wp1.lock();
		sp2.get()->show();
		cout << wp1.use_count() << endl; // 2
		cout << "}" << endl;
	}
	cout << sp1.use_count() << endl; // 1
	cout << "主函数执行结束" << endl;
	return 0;
}
#endif // 0
