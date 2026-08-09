#if 0
#include<iostream>
using namespace std;

class Person {
	friend ostream& operator<<(ostream& out, Person& p);

public:
	Person(int a, int b) {
		this->m_A = a;
		this->m_B = b;
	}

private:
	int m_A, m_B;
};

//全局函数实现左移运算符重载
//ostream 对象只能有一个
//cout 是 ostream 类的对象。ostream 类和 cout 都是在头文件 中声明的。ostream 类将 << 重载为成员函数

ostream& operator<<(ostream& out, Person& p) {
	out << "a:" << p.m_A << " b:" << p.m_B<<endl;
	return out;
}

void test() {
	Person p1(10, 20);

	cout << p1 << "hello world" << endl;
}

int main() {
	test();
	system("pause");
	return 0;
}
#endif