#include<string>
#include<iostream>
using namespace std;

//2.全局函数配合友元 类外实现 - 先做函数模板声明，下方在做函数模板定义，在做友元
template<class T1, class T2> class Person;

//如果声明了函数模板，可以将实现写到后面，否则需要将实现体写到类的前面让编译器提前看到
//template<class T1, class T2> void printPerson2(Person<T1, T2> & p);

template<class T1,class T2>
void printPerson2(Person<T1, T2>& p) {
	cout << "类外实现---- 姓名：" << p.m_name << " 年龄：" << p.m_age << endl;
}

template<class T1,class T2>
class Person
{
public:
	//1.全局函数配合友元 类内实现
	friend void printPerson(Person<T1, T2>& p) {
		cout << "name: " << p.m_name << " age: " << p.m_age << endl;
	}
	Person(T1 name, T2 age) :
		m_name(name),
		m_age(age) {

	}
	~Person() {

	}
	//类外实现 类内声明
	friend void printPerson2<>(Person<T1, T2>& p);

private:
	T1 m_name;
	T2 m_age;
};

void test01() {
	Person <string, int> p("Tom", 20);
	printPerson(p);
}

void test02() {
	Person <string, int>p("Jerry", 30);
	printPerson2(p);
}

int main() {
	test01();

	test02();

	system("pause");

	return 0;
}