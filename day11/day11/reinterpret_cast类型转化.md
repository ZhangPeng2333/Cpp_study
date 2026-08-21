reinterpret_cast是类型重新解释转化，其对象必须是一个指针、引用、函数指针、成员指针
将指定类型指针或者引用转化为解释类型的数据，用于指针类型之间、整数和指针类型之间的转化
	int a = 100;
	int* p = &a;
	//c
	int number = *p;
	char* ctr = (char*)p; //强制类型转化
	void* arg = (void*)p;
	cout << p << " " << ctr << " " << arg << endl;
	//类型重新解释
	int num = reinterpret_cast<int>(*p);
	cout << num << endl;
	char* str = reinterpret_cast<char*>(p);
	void* arg1 = reinterpret_cast<void*>(p);
	cout << p << " " << str << " " << arg1 << endl;