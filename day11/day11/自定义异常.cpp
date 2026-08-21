#if 0
//前提 勿滥用异常
#include<iostream>
#include<stdexcept>
using namespace std;

class ZeroException :public exception {
public:
	const char* what() const throw() //异常规格说明，表示what函数不可能出现任何异常
	{
		return "不能除以0！！";
	}
};

double division(double a, double b) {
	if (b == 0)
		throw ZeroException();
	return a / b;
}

int main() {
	try {
		//一个try块只放一个异常对象
		cout << "A" << division(5, 0) << endl;
	}
	catch (ZeroException &e) {
		cout << e.what() << endl;
		cout << "C" << -1 << endl;
	}
	cout << "main over" << endl;
	return 0;
}
#endif // 0
