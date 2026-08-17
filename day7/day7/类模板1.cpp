#if 0
#include<iostream>
#include<string>

using namespace std;

//可以给个默认参数
template<class NameType, class AgeType = int>
class Person
{
public:
	Person(NameType name, AgeType age) :
		mName(name),
		mAge(age) {

	}

	void showPerson() {
		cout << "name: " << this->mName << " age: " << this->mAge << endl;
	}

private:
	NameType mName;
	AgeType mAge;
};

void test01() {
	//指定NameType为string agetype->int
	//Person p("孙悟空",999)//err 类模板不可以使用自动类型推导
	Person<string, int>p1("孙悟空", 999);
	p1.showPerson();
}

void test02() {
	Person <string> p("猪八戒", 999);
	//可以使用默认参数
	p.showPerson();
}

//类模板中成员函数编译时机
/*
类模板中成员函数和普通类中成员函数创建时机是有区别的：
	普通类中的成员函数一开始就可以编译
	类模板中的成员函数在调用时才编译
*/
class Person1 {
public:
	void showPerson1() {
		cout << "Person1 show" << endl;
	}
};

class Person2 {
public:
	void showPerson2() {
		cout << "Person2 show" << endl;
	}
};

template<class T>
class MyClass
{
public:
	T obj;
	//类模板中的成员函数，并不是一开始就创建的，而是在模板调用时再生成
	void func1() {
		obj.showPerson1();
	}
	void func2() {
		obj.showPerson2();//思考 若func2为virtual ?
	}
	//没加virtual时没调用的时候可以编译。加了virtual时没调用也不能编译
	/*
	 加了 virtual 之后
一旦类中含有虚函数，编译器必须在实例化类时立即生成虚函数表（vtable），以便支持多态（即使没有直接调用虚函数）。

虚函数表需要包含所有虚函数的入口地址，因此编译器必须编译所有虚函数的定义，用模板实参去实例化它们。

当 MyClass<Person1> 实例化时，func2 是虚函数，所以编译器会强制实例化 func2 的定义，其中调用了 obj.showPerson2()。但 Person1 并没有 showPerson2 成员，导致编译错误。
	*/
};

void test03() {
	MyClass<Person1> m;
	// 这里并不会对func1, func2编译，只有明确调用了某个函数时，此函数代码才而参与编译
	m.func1();
	//m.func2();//编译出错
}

//类模板对象做函数参数
//1.指定传入的类型
void printPerson1(Person<string, int>&p) {
	p.showPerson();
}
void test04() {
	Person<string, int>p("孙悟空", 100);
	printPerson1(p);
}

//2.参数模板化
template<typename T1, typename T2>
void printPerson2(Person<T1, T2>&p) {
	p.showPerson();
	cout << "T1的类型：" << typeid(T1).name() << endl;
	cout << "T2的类型：" << typeid(T2).name() << endl;
}
void test05() {
	Person<string, int>p("猪八戒", 90);
	printPerson2(p);
}

//3.整个类模板化
template<class T>
void printPerson3(T &p) {
	cout << "T的类型为： " << typeid(T).name() << endl;
	p.showPerson();
}
void test06() {
	Person<string, int>p("唐僧", 30);
	printPerson3(p);
}

int main() {
	test01();
	test02();
	cout << endl;
	test03();
	test04();
	test05();
	test06();
	system("pause");
	return 0;
}
#endif // 0
