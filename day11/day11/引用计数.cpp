#if 0
/*每多一个shared_ptr持有同一资源，每个share_ptr内部的引用计数将增加1，每一个持有该资源的
shared_ptr销毁时，引用计数将减1，直到引用计数减为0，则销毁持有的资源。*/
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
	{
		cout << "{" << endl;
		shared_ptr<Test> sp1 = make_shared<Test>("A");
		cout << "引用计数：" << sp1.use_count() << endl; // 1
		shared_ptr<Test> sp2(sp1);
		shared_ptr<Test> sp3 = sp2;
		sp4 = sp3;
		cout << "引用计数：" << sp1.use_count() << endl; // 4
		cout << "引用计数：" << sp2.use_count() << endl; // 4
		cout << "引用计数：" << sp3.use_count() << endl; // 4
		cout << "引用计数：" << sp4.use_count() << endl; // 4
		cout << "}" << endl;
	}
	cout << "引用计数：" << sp4.use_count() << endl; // 1
	cout << "主函数执行结束" << endl;
	return 0;
}

#endif // 0
