#if 0
/*weak_ptr对资源的持有可能失效，此时lock也会失效。因此，在执行lock函数之前，要
先检测资源是否已经失效。expired()函数
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
	weak_ptr<Test> wp1;
	{
		cout << "{" << endl;
		shared_ptr<Test> sp1 = make_shared<Test>("A");
		wp1 = sp1;
		cout << "}" << endl;
	}
	// wp1持有的资源已经失效
	if (wp1.expired()) // 如果已经失效则返回true
	{
		cout << "资源已失效！" << endl;
	}
	else
	{
		shared_ptr<Test> sp2 = wp1.lock(); //最好在执行lock前检测一下资源是否失效
		sp2.get()->show();
	}
	cout << "主函数执行结束" << endl;
	return 0;
}

#endif // 0
