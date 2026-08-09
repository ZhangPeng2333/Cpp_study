#if 0
#include<iostream>
using namespace std;

class Person {
	friend ostream& operator<<(ostream& out, Person& p);

public:
	Person(int a){
		m_age = new int(a);
	}

	Person& operator=(Person& p) {
		if (m_age!=NULL)
		{
			delete m_age;
			m_age = NULL;
		}
		//提供深拷贝

		m_age = new int(*p.m_age);

		return *this;

	}
	Person(const Person& other) {
		//提供深拷贝 解决浅拷贝问题
		m_age = new int(*other.m_age);
	}

	~Person() {
		if (m_age != NULL) {
			delete m_age;
			m_age = NULL;
		}
	}
private:
	int * m_age;
};
ostream& operator<<(ostream& out, Person& p) {
	out << "age:" <<*p.m_age<<" addr: "<< p.m_age << endl;
	return out;
}
void test01() {
	Person p1(1);
	Person p2(2);
	Person p3(3);

	p3 = p2 = p1;

	cout << "p1 " << p1;
	cout << "p2 " << p2;
	cout << "p3 " << p3;
	return;
}

int main() {
	test01();
	int a = 1, b = 2, c = 3;
	c = b = a;
	cout << "a " << a << endl;
	cout << "b " << b << endl;
	cout << "c " << c << endl;
}
#endif