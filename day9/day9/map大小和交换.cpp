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
	map<int, int>m;//默认构造
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(3, 30));
	m.insert(pair<int, int>(4, 40));
	
	if (m.empty()) {
		cout << "m为空" << endl;
	}
	else {
		cout << "m不为空" << endl;
		cout << "m的大小为：" << m.size() << endl;
	}
}

void test02() {
	map<int, int> m;
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(3, 30));

	map<int, int>m2;
	m2.insert(pair<int, int>(4, 40));
	m2.insert(pair<int, int>(5, 50));
	m2.insert(pair<int, int>(6, 60));

	cout << "Before:" << endl;
	printMap(m);
	printMap(m2);

	m.swap(m2);

	cout << "After:" << endl;
	printMap(m);
	printMap(m2);
}


int main() {

	test01();

	test02();

	system("pause");

	return 0;
}
#endif // 0
