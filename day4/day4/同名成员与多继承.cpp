#if 0
#include <iostream>
using namespace std;

// 父子同名成员
class BaseFather {
public:
	int m_A = 100;
};

class SonSame : public BaseFather {
public:
	int m_A = 200;
};

void test_SameMember() {
	SonSame s;
	cout << "子类直接访问 m_A：" << s.m_A << endl;
	cout << "访问父类 m_A：" << s.BaseFather::m_A << endl;
}

// 多继承，两个基类有同名成员
class Base1 {
public:
	Base1() { m_A = 100; }
	int m_A;
};

class Base2 {
public:
	Base2() { m_A = 200; }
	int m_A;
};

class SonMulti : public Base2, public Base1 {
public:
	int m_C;
	int m_D;
};

void test_MultiExtend() {
	SonMulti s;
	cout << "Son 占用内存大小：" << sizeof(s) << endl;
	// cout << s.m_A;      // 二义性，编译错误
	cout << "Base1::m_A = " << s.Base1::m_A << endl;
	cout << "Base2::m_A = " << s.Base2::m_A << endl;
}

int main() {
	test_SameMember();
	test_MultiExtend();
	system("pause");
	return 0;
}
#endif // 0
