#if 0
#include<iostream>
#include<exception>
using namespace std;

//使用关键字noexcept修饰 不抛出异常
void func()noexcept
{//throw "error func";
}
void funs()
{
	throw std::runtime_error("error funs");//抛出异常
}
//可以接受一个常量表达式作为参数
void myfunc(int x)noexcept(false) //noexcept(x > 0) err，该表达式不为常数
{
	if (x <= 0)
	{
		throw std::runtime_error("myfunc arg");
	}
}
//注意常量表达式是在编译的时候确定，所以不依赖运行时候的值
int main()
{
	//检查异常
	try
	{
		func();//不会抛出异常
		funs();//会抛出异常
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

#endif // 0
