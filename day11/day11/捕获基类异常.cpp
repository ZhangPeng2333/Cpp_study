#if 0
#include <iostream>
#include <stdexcept>
using namespace std;
int main()
{
	string str = "hello";
	try {
		// 下面两行分别启用和禁用，查看异常捕获的结果
		// cout << str.at(1000) << endl;
		throw length_error("仅用于演示");
	}
	catch (exception &e) // 不同的异常类型使用同一种处理方式
	{
		cout << e.what() << endl;
		cout << 'A' << endl;
	}
	try {
		//cout << str.at(1000) << endl;
		throw length_error("仅用于演示");
	}
	catch (...) // 捕获任何异常
	{
		// cout << e.what() << endl;
		cout << 'A' << endl;
	}
	cout << "主函数执行结束" << endl;
	return 0;
}
#endif // 0
