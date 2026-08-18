#if 0
#include<iostream>
#include<set>
using namespace std;

void test01() {
	set<int> s1;
	s1.insert(10);
	s1.insert(20);
	s1.insert(30);
	s1.insert(40);
	s1.insert(50);

	//查找
	set<int>::iterator pos = s1.find(100);
	if (pos != s1.end())
	{
		cout << "找到了元素 ： " << *pos << endl;
	}
	else
	{
		cout << "未找到元素" << endl;
	}
	//统计
	int num = s1.count(100);
	cout << "num = " << num << endl;
}


int main() {
	test01();
	system("pause");
	return 0;
}
#endif // 0
