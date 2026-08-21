#if 0
#include<iostream>
using namespace std;

double division(double a, double b) {
	if (b == 0)
	{
		throw "不能除以0!";
		int n = 10;//不执行
	}
	return a / b;
}

double add(double a, double b) {
	try {
		double d = division(a + b, a - b);
		int j = 20;// 不会执行 因上一行代码有异常
		return d;
	}
	catch (int e)//捕获失败 向上转移控制权
	{
		cout << "捕获到异常！" << endl;
		return 0;
	}
}

int main() {
	try
	{
		cout << add(5, 5) << endl;
		int m = 30;//不执行 in上一行代码有异常 且在add函数中，捕获的异常类型不对，不能捕获此异常，此异常继续上一层传递
	}
	catch (const char* e)//捕获成功
	{
		cout << "捕获到异常B" << e << endl;
		cout << 1 << endl;
	}
	cout << "main over" << endl;
	return 0;
}
#endif // 0
