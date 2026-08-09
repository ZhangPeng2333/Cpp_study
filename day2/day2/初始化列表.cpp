#include<iostream>

using namespace std;

class Person
{
public:
	//初始化 列表方式初始化
	Person(int a, int b, int c) :
		m_A(a),
		m_B(b),
		m_C(c) {

	}
	~Person() {

	}

	void PrintPerson() {
		cout << "m_A:" << m_A << endl;
		cout << "m_B:" << m_B << endl;
		cout << "m_C:" << m_C << endl;
	}

private:
	int m_A, m_B, m_C;
};

class Point
{
public:
	Point(float X, float Y){
		m_X = new float(X);
		m_Y = new float(Y);
		cout << "Point 有参构造" << endl;

	}
	Point() {
		m_X = new float(0);
		m_Y = new float(0);
		cout << "Point 默认构造" << endl;

	}
	Point(const Point& p) {
		this->m_X = new float(*p.m_X);
		this->m_Y = new float(*p.m_Y);
		cout << "Point 拷贝构造" << endl;

	}
	~Point() {
		cout << "Point 析构" << endl;
		delete(m_X);
		delete(m_Y);
		m_X = NULL;
		m_Y = NULL;
	}

private:
	float* m_X;
	float* m_Y;
};

class Circle
{
public:
	Circle(float c_X, float c_Y, float r) :
		m_center(c_X, c_Y),
		m_radius(r) {
		cout << "Circle 有参构造" << endl;
	}
	Circle() :
		m_center(),
		m_radius(0) {
		cout << "Circle 无参构造" << endl;
	}
	Circle(const Circle& c) :
		m_center(c.m_center),
		m_radius(c.m_radius) {
		cout << "Circle 拷贝构造" << endl;
	}
	~Circle() {
		cout << "Circle 析构" << endl;
	}

private:
	Point m_center;
	float m_radius;
};

class NoneClass
{
};

class OnlyFunc {
	OnlyFunc() {

	}
	~OnlyFunc() {

	}
	void PrintHello() {
		cout << "Hello World" << endl;
	}
};

class Student1
{
public:
	Student1();
	~Student1();

private:
	//int age, id;
	int age;
};

class Student2
{
public:
	Student2();
	~Student2();
	static int PrintStudent2() {
		//cout << "Student2 age:" << m_age << endl << "Student2 ID:" << m_id << endl;
	}

private:
	//static int m_age;
	//static int m_id;
};

class Student3
{
public:
	Student3();
	~Student3();
	static int PrintStudent3() {
		cout << "Student3 age:" << m_age << endl << "Student3 ID:" << m_id << endl;
	}

private:
	static int m_age;
	static int m_id;
};

void sayHello() {
	cout << "Hello!" << endl;
}

class OnlyVirtualFunc {
public:
	virtual void func() {

	}

};

int main() {

	Circle* c1 = new Circle(1, 1, 1);
	Circle* c2 = new Circle();
	Circle* c3 = new Circle(*c1);

	cout << "sizeof NoneClass:" << sizeof(NoneClass) << " 空类"<<endl;
	cout << "sizeof OnlyFunc:" << sizeof(OnlyFunc) << " 只有成员函数"<<endl;
	cout << "sizeof Student1:" << sizeof(Student1) << " 只有成员变量"<<endl;
	cout << "sizeof Student2:" << sizeof(Student2) << " 只有静态函数"<<endl;
	cout << "sizeof Student3:" << sizeof(Student3) << " 静态成员与静态函数"<<endl;
	cout << "sizeof OnlyVirtualFunc:" << sizeof(OnlyVirtualFunc) << " 只有虚函数" << endl;
	system("pause");

	return 0;
}