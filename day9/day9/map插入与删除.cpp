#if 0
#include<iostream>
#include<map>
using namespace std;

void printMap(const map<int, int>& m) {
	for (map<int, int>::const_iterator it = m.begin(); it != m.end(); it++)
	{
		cout << "key= " << it->first << " value= " << it->second << endl;
	}
	cout << endl;
}

void test01() {
	map<int, int>m;
	//插入 方式1
	m.insert(pair<int, int>(1, 10));
	//插入 方式2
	m.insert(make_pair(2, 20));
	//3 
	m.insert(map<int, int>::value_type(3, 30));
	//4 (慎用)
	m[4] = 40;
	printMap(m);

	//删除
	m.erase(m.begin());
	printMap(m);

	m.erase(3);//删除key为3的pair
	printMap(m);

	//清空
	//1
	m.erase(m.begin(), m.end());
	//2
	m.clear();
	printMap(m);


}

int main() {

	test01();

	//test02();

	system("pause");

	return 0;
}
#endif // 0
