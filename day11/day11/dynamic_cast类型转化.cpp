/*用于继承过程中将基类指针转化为派生类指针
将一个基类对象指针或者引用转为派生类对象指针或者引用
根据基类指针时候真正指向继承类指针【是否有派生类成员存在，虚函数】
若转化成功 获取派生类对象指针 若转化失败 获取是空指针*/
#if 0

#include<iostream>
#include<memory>
using namespace std;
//基类
class Base
{
public:
	Base()
	{
		cout << "Base()" << endl;
	}
	~Base()
	{
		cout << "~Base()" << endl;
	}
	virtual void show()
	{
		cout << "Base::show()" << endl;
	}
};
//派生类
class derived : public Base
{
public:
	derived()
	{
		cout << "derived()" << endl;
	}
	~derived()
	{
		cout << "~derived()" << endl;
	}
	void show()
	{
		cout << "derived::show()" << endl;
	}
};
int main()
{
	//定义基类指针
	Base* ptr = new Base;//基类初始化
	Base* ptr1 = new derived;//派生类初始化
	ptr->show();
	//将基类指针转化为派生类指针
	derived* der1 = (derived*)ptr;
	der1->show();
	//将基类指针转化为派生类指针
	derived* der2 = dynamic_cast<derived*>(ptr);
	if (der2 == nullptr)
	{
		cout << "nullptr" << endl;
	}
	else
	{
		der2->show();
	}
	//此时派生类指针转换成功，因为基类中有派生类的赋值和虚函数存在
	derived* der3 = dynamic_cast<derived*>(ptr1);
	if (der3 == nullptr)
	{
		cout << "nullptr" << endl;
	}
	else
	{
		der3->show();
	}
	return 0;
}
#endif // 
