#if 0
#include<iostream>
#include<string>
#include<map>
#include<utility>//into use std::pair

using namespace std;

int main() {
	multimap<int, string>myMultimap;
	//insert
	myMultimap.insert(pair<int, string>(1, "Apple"));
	myMultimap.insert(pair<int, string>(1, "Apricot"));
	myMultimap.insert(pair<int, string>(2, "Banana"));
	myMultimap.insert(pair<int, string>(3, "Cherry"));
	myMultimap.insert(pair<int, string>(1, "Avocado"));

	//print
	multimap<int, string>::iterator it;
	for (it = myMultimap.begin(); it != myMultimap.end(); it++)
	{
		cout << "key= " << it->first << ", value=" << it->second << endl;
	}

	//查找某键的所有值
	int keytofind = 1;
	pair<multimap<int, string>::iterator, multimap<int, string>::iterator> range;
	range = myMultimap.equal_range(keytofind);
	cout << "values for key" << keytofind << ":" << endl;
	for (it = range.first; it != range.second; it++)
	{
		cout << it->second << endl;
	}

	//删除某键的一个实例
	it = myMultimap.find(1);//find返回指向第一个匹配键的迭代器
	if (it != myMultimap.end())
	{
		myMultimap.erase(it);
	}

	// 再次打印所有元素
	std::cout << "\nAfter erasing one value with key 1:\n";
	for (it = myMultimap.begin(); it != myMultimap.end(); ++it) {
		std::cout << "Key: " << it->first << ", Value: " << it->second << '\n';
	}
	return 0;







}
#endif // 0
