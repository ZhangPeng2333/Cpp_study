#if 0
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};
void test01()
{
	vector<int> v1;
	for (int i = 0; i < 10; i++) {
		v1.push_back(i + 1);
	}
	vector<int> v2;
	//不给他分配，用back_inserter
	// v2.resize(v1.size());
	//copy(v1.begin(), v1.end(), v2.begin());
	// 使用 back_inserter，它会自动调用 v2.push_back()
	copy(v1.begin(), v1.end(), back_inserter(v2));
	for_each(v2.begin(), v2.end(), myPrint());
	cout << endl;
}
int main() {
	test01();
	system("pause");
	return 0;
}
#endif // 0
