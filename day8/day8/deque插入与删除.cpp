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

// Á½¶Ë²Ù×÷
void test01() {
	deque<int> d;
	// Î²²å
	d.push_back(10);
	d.push_back(20);
	// Í·²å
	d.push_front(100);
	d.push_front(200);

	printDeque(d);

	//Î²É¾
	d.pop_back();
	//Í·É¾
	d.pop_front();
	printDeque(d);
}

//²åÈë
void test02()
{
	deque<int> d;
	d.push_back(10);
	d.push_back(20);
	d.push_front(100);
	d.push_front(200);
	printDeque(d);
	d.insert(d.begin(), 1000);
	printDeque(d);
	d.insert(d.begin(), 2, 10000);
	printDeque(d);
	deque<int>d2;
	d2.push_back(1);
	d2.push_back(2);
	d2.push_back(3);
	d.insert(d.begin(), d2.begin(), d2.end());
	printDeque(d);
}


//É¾³ý
void test03()
{
	deque<int> d;
	d.push_back(10);
	d.push_back(20);
	d.push_front(100);
	d.push_front(200);
	printDeque(d);
	d.erase(d.begin());
	printDeque(d);
	d.erase(d.begin(), d.end());
	d.clear();
	printDeque(d);
}


int main() {
	test01();
	test02();
	test03();
	system("pause");
	return 0;
}
#endif // 0
