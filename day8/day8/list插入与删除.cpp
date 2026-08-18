#if 0
#include<iostream>
#include <list>
using namespace std;

void printList(const list<int>& L) {
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
//²åÈëºÍÉ¾³ý
void test01()
{
	list<int> L;
	//Î²²å
	L.push_back(10);
	L.push_back(20);
	L.push_back(30);
	//Í·²å
	L.push_front(100);
	L.push_front(200);
	L.push_front(300);
	printList(L);
	//Î²É¾
	L.pop_back();
	printList(L);
	//Í·É¾
	L.pop_front();
	printList(L);
	//²åÈë
	list<int>::iterator it = L.begin();
	L.insert(++it, 1000);
	printList(L);
	//É¾³ý
	it = L.begin();
	L.erase(++it);
	printList(L);
	//ÒÆ³ý
	L.push_back(10000);
	L.push_back(10000);
	L.push_back(10000);
	printList(L);
	L.remove(10000);
	printList(L);
	//Çå¿Õ
	L.clear();
	printList(L);
}
int main() {
	test01();
	system("pause");
	return 0;
}
#endif // 0
