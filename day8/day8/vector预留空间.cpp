#if 0
#include<iostream>
#include<vector>
using namespace std;

void printVector(vector<int>& v) {
	if (v.begin() == v.end())
	{
		cout << "空vector" << endl;
		return;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {

	vector<int> v;
	//v.reserve(100000);
	int num = 0;
	int * p = NULL;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);

		if (p!=&v[0])
		{
			p = &v[0];
			num++;
		}
	}
	num--;
	cout << "num: " << num << endl;
	// MSVC采用约1.5倍扩容，此处结果为29
	// 若在LINUX下GCC编译 采用2倍扩容，通过消耗更多内存减少扩容次数，
	//以换取时间效率，此处num:16
}

int main() {

	test01();
	return 0;
}
#endif // 0
