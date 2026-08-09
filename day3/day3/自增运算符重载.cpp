#if 0
#include<iostream>

using namespace std;

class MyInteger
{
	friend ostream& operator<<(ostream& out, MyInteger myint);
public:
	MyInteger() {
		m_Num = 0;
	}
	//++MyInteger
	MyInteger& operator++() {
		//先增
		m_Num++;
		return *this;
	}

	MyInteger operator++(int) {
		//先保存 用于返回
		MyInteger temp = *this;
		//后自增
		m_Num++;
		return temp;
	}
	~MyInteger() {

	}

private:
	int m_Num;
};

ostream& operator<<(ostream& out, MyInteger myint) {
	out << myint.m_Num;
	return out;
}

void test01() {
	MyInteger myInt;
	cout << "++MyInteger:" << endl;
	cout << ++myInt << endl;
	cout << myInt << endl;
}

void test02() {
	MyInteger myInt;
	cout << endl;
	cout << "MyInteger++:" << endl;
	cout << myInt++ << endl;
	cout << myInt << endl;
}

int main() {
	test01();
	test02();

	system("pause");
	return 0;
}

#endif