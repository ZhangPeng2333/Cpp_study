#if 0
#include<iostream>
#include<vector>
using namespace std;

void printVector(vector<int>& v) {
	if (v.begin()==v.end())
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
	//Î²²å
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);
	printVector(v1);
	//Î²É¾
	v1.pop_back();
	printVector(v1);

	//²åÈë
	v1.insert(v1.begin(), 100);
	printVector(v1);

	v1.insert(v1.begin(), 2, 1000);
	printVector(v1);

	//É¾³ý
	v1.erase(v1.begin());
	printVector(v1);

	//Çå¿Õ
	v1.erase(v1.begin(), v1.end());
	v1.clear();
	printVector(v1);

}

int main() {

	test01();
	return 0;
}
#endif // 0
