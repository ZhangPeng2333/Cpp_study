#if 0
#include<iostream>
#include<string>
using namespace std; //空指针可以调用成员函数，但由于有this指针，容易有坑 
class person {
public:
	void classname() {
		cout << "this is person class" << endl;
	}
	void personage() {
		if (this == NULL) {
			return;
		}
		cout << "age=" << m_age << endl;//存在类属性，其实在属性的前面默认都会加上一个this->，空指针调用这个函数，导致this没有指向一个确切的值
	}
	int m_age;
};

void test1() {
	person* p = NULL;
	p->classname();//只有这一个函数时，程序不崩
	p->personage();//这个函数出错，程序崩溃了，报错原因是传入指针为空
	//如何解决呢？
	//给this指针增加判断！

}

//int main() {
//	test1();
//	system("pause");
//	return 0;
//}
#endif