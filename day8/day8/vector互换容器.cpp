#if 0
#include<iostream>
#include<vector>
using namespace std;

void printVector(vector<int>& v) {
	if (v.begin() == v.end())
	{
		cout << "¿Õvector" << endl;
		return;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {

	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	printVector(v1);

	vector<int>v2;
	for (int i = 10; i > 0; i--)
	{
		v2.push_back(i);
	}

	printVector(v2);
	//»¥»»ÈÝÆ÷
	cout << "»¥»»ºó" << endl;
	v1.swap(v2);
	printVector(v1);
	printVector(v2);
	
}

void test02() {
	vector<int> v;
	cout << "v's capacity: " << v.capacity() << endl;
	cout << "v's size: " << v.size() << endl;

	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);
	}

	cout << "v's capacity: " << v.capacity() << endl;
	cout << "v's size: " << v.size() << endl;

	v.resize(3);

	cout << "v's capacity: " << v.capacity() << endl;
	cout << "v's size: " << v.size() << endl;
	//ÊÕËõÄÚ´æ
	vector<int>(v).swap(v);
	cout << "v's capacity: " << v.capacity() << endl;
	cout << "v's size: " << v.size() << endl;

}

int main() {

	test01();
	test02();
	return 0;
}
#endif // 0
