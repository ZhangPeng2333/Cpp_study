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

int main() {
	shared_ptr<Test> sp1;
	{
		cout << '{' << endl;
		shared_ptr<Test>sp2 = make_shared<Test>("A");
		sp1 = sp2;//影响引用计数
		//创建weakptr对象
		weak_ptr<Test> wp1(sp2);//不影响计数
		weak_ptr<Test> wp2 = wp1;//同上
		weak_ptr<Test> wp3;
		wp3 = wp1;//同上

		// wp3.get();错误：无法直接获得资源
		cout << wp1.use_count() << endl;//2
		cout << wp2.use_count() << endl;//2
		cout << wp3.use_count() << endl;//2
		cout << sp1.use_count() << endl;//2
		cout << sp2.use_count() << endl;//2
		cout << '}' << endl;

	}
	cout << sp1.use_count() << endl;//1
	cout << "main over" << endl;
	return 0;
}
#endif // 0
