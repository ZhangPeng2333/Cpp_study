#if 0
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

//常用遍历算法 搬运 transform
class Transform {
public:
	int operator()(int val) {
		return val;
	}
};

class MyPrint {
public:
	void operator()(int val) {
		cout << val << ' ';
	}
};

void test01() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//目标容器
	vector<int> vTar;

	vTar.resize(v.size());
	transform(v.begin(), v.end(), vTar.begin(), Transform());

	for_each(vTar.begin(), vTar.end(), MyPrint());

}

int main() {
	test01();

	return 0;
}

#endif // 0
