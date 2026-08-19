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
	m.insert(pair<int, int>(1, 10));
	m.emplace(2, 20);
	m.insert(map<int, int>::value_type(3, 30));
	m.insert({ 4,40 });
	map<int, int>::iterator pos = m.find(4);

	if (pos != m.end()) {
		cout << "找到了元素 key = " << (*pos).first << " value=" << (*pos).second << endl;
	}
	else {
		cout << "unfind element" << endl;
	}
	//统计
	int num = m.count(3);
	cout << "num= " << num << endl;
}

int main() {

	test01();

	//test02();

	system("pause");

	return 0;
}
#endif // 0
