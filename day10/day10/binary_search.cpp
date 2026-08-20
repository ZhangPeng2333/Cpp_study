#if 0
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
//
// 一定要有序！！！
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//二分查找
	bool ret = binary_search(v.begin(), v.end(), 2);
	if (ret)
	{
		cout << "找到了" << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
}

int main() {
	test01();
	system("pause");
	return 0;
}

#endif // 0
