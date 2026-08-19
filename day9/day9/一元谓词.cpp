#if 0
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//1.Ò»ÔªÎ½´Ê
struct GreaterFive {
	bool operator()(int val) {
		return val > 5;
	}
};

void test01() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
	if (it == v.end())
	{
		cout << "unfind!" << endl;
	}
	else {
		cout << "find:" << *it << endl;
	}


}

int main() {
	test01();
	system("pause");
	return 0;
}
#endif // 0
