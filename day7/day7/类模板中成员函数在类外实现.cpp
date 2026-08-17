#if 0
#include<iostream>
#include<string>
using namespace std;

template<class T1, class T2>
class Person {
public:
	//成员函数类内声明
	Person(T1 name, T2 age);
	void showPerson();
public:
	T1 m_name;
	T2 m_age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) :
	m_name(name),
	m_age(age) {

}

template<class T1, class T2>
void Person<T1, T2>::showPerson() {
	cout << "name: " << this->m_name << " age: " << this->m_age << endl;
}

void test01() {
	Person<string, int>p("Tom", 20);
	p.showPerson();
}

int main() {
	test01();
	system("pause");

	return 0;
}
#endif // 0
