#if 0
#include<iostream>
using namespace std;

double division(double a, double b) {
	if (b == 0) {
		throw "cannot divide by zero!";  // 抛出 const char* 异常
	}
	return a / b;
}

int main() {
	try {
		cout << division(2, 0) << endl;
	}
	catch (const char* msg) {          // 捕获字符串异常 有抛要有接 不接有报错
		cerr << "异常捕获: " << msg << endl;
	}

	cout << "主函数结束" << endl;
	return 0;
}
#endif // 0
