#include<iostream>

using namespace std;

class Person1
{
public:

	Person1() {
		// 无参/默认 构造函数
		cout << "无参构造" << endl;

	}
	Person1(int age, int sex) {
		// 有参构造函数
		cout << "有参构造函数" << endl;

		m_age = age;
		m_sex = new int(sex);
	}
	Person1(const Person1& p) {
		//拷贝构造函数
		cout << "拷贝构造函数" << endl;
		this->m_age = p.m_age;
		this->m_sex = new int(*p.m_sex);
	}

	~Person1() {
		//析构函数
		//cout << "析构函数" << endl;		
		cout << m_age << "析构函数" << endl;
		if (m_sex!=NULL)
		{
			delete m_sex;
			m_sex = NULL;
		}
	}

public:
	int m_age;
	int* m_sex;
};

void test01() {
	Person1 p1(18, 1);
	Person1 p2(19,0);
	cout << "P1 age:" << p1.m_age << " sex:" << *p1.m_sex << endl;
	cout << "P2 age:" << p2.m_age << " sex:" << *p2.m_sex << endl;

}

//int main() {
//	test01();
//
//	system("pause");
//
//	return 0;
//}