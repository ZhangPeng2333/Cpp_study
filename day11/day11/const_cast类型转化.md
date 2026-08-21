用来移除变量的const修饰或者volatile限定符
（1）常量指针被转化之后成为非常量指针，并且仍然执行原来的对象地址
（2）常量引用被转化之后成为非常量引用，并且仍然执行原来的对象
（3）const_cast用于修改底层指针，比如const char *p形式
注意：强制类型转化的目标只能是指针或者引用
	const int a = 100;//只读型变量
	const int* p = &a;//const int *指向const int的地址
	cout << a << " " << *p << endl;
	//C语言中 强行修改为普通int *指针
	int* ptr = (int*)p;//int *和const int *
	cout << ptr << " " << p << endl;
	*ptr = 200;
	cout << *ptr << " " << *p << endl;
	//c++中，去除指针的const修饰
	int* qtr = const_cast<int*>(p);
	cout << qtr << " " << p << endl;
	*qtr = 200;
	cout << *qtr << " " << *p << endl;