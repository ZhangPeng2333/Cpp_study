
#if 0
#include <iostream>
#include <memory>
using namespace std;
class B; // 前置声明类B
class A {
public:
	A() {
		std::cout << "A()\n";
	}
	~A() {
		std::cout << "~A()\n";
	}
	std::shared_ptr<B> _ptrb; // 指向B对象的shared_ptr智能指针
};
class B {
public:
	B() {
		std::cout << "B()\n";
	}
	~B() {
		std::cout << "~B()\n";
	}
	std::shared_ptr<A> _ptra; // 指向A对象的shared_ptr智能指针
};
int main() {
	std::shared_ptr<A> ptra = std::make_shared<A>(); // ptra指向A对象，A的引用计数为1
	//（但因为是shared_ptr内部实现，这里不直接显示）
	std::shared_ptr<B> ptrb = std::make_shared<B>(); // ptrb指向B对象，B的引用计数为1
	//（同理）
	// A对象的成员变量_ptrb也指向B对象，因为是shared_ptr导致引用计数改变
	ptra->_ptrb = ptrb;
	// B对象的成员变量_ptra也指向A对象，因为是shared_ptr导致引用计数改变
	ptrb->_ptra = ptra;
	cout << ptra->_ptrb.use_count() << endl;
	cout << ptrb->_ptra.use_count() << endl;
	return 0;
}

#endif // 0

#if 0
//只需要将ptrb和ptra 改为weak_ptr即可，因为weak_ptr不会导致引用计数改变。
#include <iostream>
#include <memory>
using namespace std;

class B; // 前置声明类B
class A {
public:
	A() { std::cout << "A()\n"; }
	~A() { std::cout << "~A()\n"; }
	std::weak_ptr<B> _ptrb; // 指向B对象的弱智能指针
};
class B {
public:
	B() { std::cout << "B()\n"; }
	~B() { std::cout << "~B()\n"; }
	std::weak_ptr<A> _ptra; // 指向A对象的弱智能指针
};
int main() {
	std::shared_ptr<A> ptra = std::make_shared<A>(); // ptra指向A对象，A的引用计数为1
	//（但因为是shared_ptr内部实现，这里不直接显示）
	std::shared_ptr<B> ptrb = std::make_shared<B>(); // ptrb指向B对象，B的引用计数为1
	//（同理）
	// A对象的成员变量_ptrb也指向B对象，但因为是弱智能指针，B的引用计数没有改变 如果是
	//shared_ptr就会导致引用计数改变
	ptra->_ptrb = ptrb;
	// B对象的成员变量_ptra也指向A对象，但因为是弱智能指针，A的引用计数没有改变 如果是
	//shared_ptr就会导致引用计数改变 会导致相互引用，互相引用计数都是2，因此main函数结束时，两个对象
		//引用计数都减1，引用计数并非为0不会调用析构函数释放资源，导致内存泄漏
	ptrb->_ptra = ptra;
	// 打印ptra和ptrb的引用计数（注意：这里不能直接打印，因为shared_ptr没有提供直接的
	//use_count()成员函数输出接口，但可以通过其他方式验证）
	// 实际上，由于使用了weak_ptr，这里的引用计数仍然为1（各自独立的计数），不会因相互引用而增
	//加
	// 出main函数作用域，ptra和ptrb两个局部对象析构
	// 分别给A对象和B对象的引用计数从1减到0（但因为是weak_ptr引用，不影响实际计数）
	// 达到释放A和B的条件，因此new出来的A和B对象被析构掉
	// 解决了“强智能指针的交叉引用（循环引用）问题”
	cout << ptra->_ptrb.use_count() << endl;
	cout << ptrb->_ptra.use_count() << endl;
	return 0;
}
#endif // 
