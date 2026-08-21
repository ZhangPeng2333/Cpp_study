/**
 * C++新特性
 *
 * 1. 线程与锁
 *    C++ 对线程和锁级别编程的支持是 POSIX 和 Windows 所提供的线程和锁的类型安全变体
 *    • thread——系统的执行线程，支持 join() 和 detach()
 *    • mutex——系统的互斥锁，支持 lock()、unlock() 和保证 unlock() 的 RAII 方式
 *    • condition_variable——系统中线程间进行事件通信的条件变量
 *    • thread_local——线程本地存储
 *    线程和锁模型需要使用某种形式的同步来避免竞争条件。C++11 为此提供了标准的 mutex（互斥锁）
 *
 * 2. nullptr（掌握）
 *    C++中NULL实际上是0，有时候代码会产生歧义。
 *    C++11中通过nullptr关键字来代替NULL避免上面的问题。
 *
 * 3. 类型推导（熟悉）
 *    使用auto关键字可以自动推导变量类型。
 *    需要注意的是，auto不支持推导数组类型，也不能用于参数类型或表达式。表示类型的推导可以使用decltype关键字。
 *
 * 4. 右值引用
 *    左值：表达式结束之后依然存在的持久对象 a
 *    右值：表达式结束之后就不存在的临时对象 10
 *    在c++中引入右值赋值，引入了右值引用类型 &&，右值引用负责匹配右值，左值引用则负责匹配左值
 *    在右值引用操作中主要用于类中的各种构造拷贝(拷贝构造、移动构造、赋值构造，移动赋值构造)，移动的意思是转移所有权
 *    类的类型 &&类对象=右值赋值；
 *    右值引用是C++11中引入的一个特性，它允许程序员区分出那些即将被销毁的临时对象（右值）和有名字的对象（左值）。
 *    通过使用右值引用，可以实现移动语义和完美转发等高级功能，从而提高程序的性能。
 *    左值能寻址，右值不能寻址；左值能赋值，右值不能赋值；左值可变，右值不能变量（仅对基本数据类型适用，用户自定义数据类型右值引用可以通过成员函数改变）
 *
 * 5. Lambda 表达式
 *    C++11 引入了 Lambda 表达式，Lambda 表达式是一种匿名函数，可以在需要函数的地方定义并使用它，而无需显式命名函数。
 *    基本语法：[capture list](parameters) -> return_type { 函数体 }
 *    其中，capture list 指定要捕获的变量列表，parameters 是参数列表，return_type 可自动推导。
 *
 * 6. 范围 for
 *    C++11中引入范围for循环，提供简洁直观的方式遍历容器、数组、字符串等可迭代对象。
 *    语法：for (element : container) { 操作 }
 *
 * 7. final & override
 *    final用于修饰类，表示禁止该类进一步派生和虚函数的进一步重载；
 *    override用于修饰派生类中的成员函数，标明该函数重写了基类函数，若父类无此虚函数则编译报错，避免无意错误。
 *
 * 8. 别名
 *    C++11 提供了两种方式来创建类型别名：typedef 和 using。
 */

#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <utility>
#include <cstring>
#include <exception>

using namespace std;

// ---------- 1. 线程示例 ----------
void print_message(const std::string& message, int n) {
	for (int i = 0; i < n; ++i) {
		std::cout << message << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 暂停一段时间以模拟工作
	}
}

void demo_thread() {
	std::vector<std::thread> threads;
	threads.push_back(std::thread(print_message, "Hello from thread 1", 5));
	threads.push_back(std::thread(print_message, "Hello from thread 2", 5));
	threads.push_back(std::thread(print_message, "Hello from thread 3", 5));
	for (auto& thread : threads) {
		thread.join();
	}
	std::cout << "All threads have finished execution." << std::endl;
}

// ---------- 2. nullptr 演示（合并两个示例） ----------
void func(int) {
	cout << "1" << endl;
}
void func(char*) {
	cout << "2" << endl;
}

void demo_nullptr() {
	// 使用 NULL 时的歧义
	char* c = NULL;
	func(c);     // 2
	func(NULL);  // 1 （因为 NULL 是 0，匹配 int 版本）

	// 使用 nullptr 解决歧义
	char* p = nullptr;
	func(p);        // 2
	func(nullptr);  // 2
}

// ---------- 3. 类型推导（auto / decltype） ----------
void demo_type_deduction() {
	auto i1 = 123;          // 自动推导为 int
	cout << i1 << endl;
	auto i2 = 12.3;         // 自动推导为 double
	cout << i2 << endl;
	auto i3 = new int(123); // 自动推导为 int*
	cout << i3 << " " << *i3 << endl;
	delete i3;

	// decltype 示例
	auto a = 123;
	auto b = 12.3;
	decltype(a + b) d = 12.3;   // 推导为 double
	cout << d << endl;
}

// ---------- 4. 右值引用（移动语义） ----------
class MyString {
private:
	char* data;
public:
	// 构造函数
	MyString(const char* str) {
		data = new char[strlen(str) + 1];
		strcpy(data, str);
		std::cout << "Constructed: " << data << std::endl;
	}
	// 拷贝构造函数
	MyString(const MyString& other) {
		data = new char[strlen(other.data) + 1];
		strcpy(data, other.data);
		std::cout << "Copy constructed: " << data << std::endl;
	}
	// 移动构造函数
	MyString(MyString&& other) noexcept {
		data = other.data;          // 直接接管资源
		other.data = nullptr;       // 避免原对象析构时释放资源
		std::cout << "Move constructed: " << data << std::endl;
	}
	// 析构函数
	~MyString() {
		delete[] data;
		std::cout << "Destructed" << (data ? " with data" : " without data") << std::endl;
	}
	// 禁用拷贝赋值操作
	MyString& operator=(const MyString&) = delete;
	// 移动赋值操作
	MyString& operator=(MyString&& other) noexcept {
		if (this != &other) {
			delete[] data;
			data = other.data;
			other.data = nullptr;
		}
		return *this;
	}
	const char* get_data() const { return data; }
};

void demo_rvalue() {
	MyString s1("Hello");
	MyString s2 = std::move(s1); // 使用移动构造函数
	std::cout << "s1's data: " << (s1.get_data() ? s1.get_data() : "nullptr") << std::endl;
	std::cout << "s2's data: " << (s2.get_data() ? s2.get_data() : "nullptr") << std::endl;
}

// ---------- 5. Lambda 表达式 ----------
void demo_lambda() {
	int x = 42;
	// 使用 Lambda 表达式打印变量 x 的值
	auto printX = [x]() {
		std::cout << "x = " << x << std::endl;
	};
	printX(); // 调用 Lambda 函数
}

// ---------- 6. 范围 for ----------
void demo_range_for() {
	std::vector<int> numbers = { 1, 2, 3, 4, 5 };
	for (auto number : numbers) {
		std::cout << number << " ";
	}
	std::cout << std::endl;
}

// ---------- 7. final & override ----------
struct Base {
	virtual void func() {
		cout << "base" << endl;
	}
};
struct Derived : public Base {
	void func() override { // 确保func被重写
		cout << "derived" << endl;
	}
	// void fu() override { } // error，基类没有fu()，不可被重写（编译报错，注释以通过编译）
};

// ---------- 8. 别名 ----------
#include <list>
typedef int myInt;                     // 将 int 定义为 myInt 类型的别名
typedef std::vector<int> IntVector;    // 将 std::vector<int> 定义为 IntVector 类型的别名
using myInt2 = int;                    // 将 int 定义为 myInt2 类型的别名
using IntVector2 = std::vector<int>;   // 将 std::vector<int> 定义为 IntVector2 类型的别名
using StringList = std::list<std::string>;
using IntMatrix = std::vector<std::vector<int>>;

// ---------- 主函数调用所有演示 ----------
int main() {
	// 为简化输出，可单独运行或注释掉某些演示
	// demo_thread();      // 线程演示（耗时，可注释）
	// demo_nullptr();
	// demo_type_deduction();
	// demo_rvalue();
	// demo_lambda();
	// demo_range_for();
	// final/override 在结构体中已体现
	// 别名类型已定义，此处简单使用
	myInt a = 10;
	IntVector v = { 1,2,3 };
	cout << "myInt a = " << a << endl;
	cout << "IntVector size = " << v.size() << endl;

	// 调用部分演示（根据需要取消注释）
	demo_nullptr();
	demo_type_deduction();
	demo_rvalue();
	demo_lambda();
	demo_range_for();

	return 0;
}