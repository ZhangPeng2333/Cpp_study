#if 0
#include<iostream>
#include<deque>
using namespace std;

void printDeque(const deque<int>& d) {
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

}

void test01() {
	deque<int> d1;
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque(d1);
	// d1.erase(d1.begin(), d1.end());
	if (d1.empty())
	{
		cout << "d1Îª¿Õ!" << endl;
	}
	else {
		cout << "d1²»Îª¿Õ" << endl;
		cout << "d1's size: " << d1.size() << endl;
	}

	d1.resize(15, 1);
	printDeque(d1);
	d1.resize(5);
	printDeque(d1);

}

int main() {
	test01();
	system("pause");
	return 0;
}
#endif // 0
