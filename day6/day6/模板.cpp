#include<iostream>
using namespace std;

void swapInt(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void swapDouble(double& a, double& b) {
	double temp = a;
	a = b;
	b = temp;
}

//template<class T>完全相同
template<typename T>
void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

void test01() {
	int a = 10, b = 20;
	//swapInt(a,b);
	mySwap(a, b);
	mySwap<int>(a, b);
	cout << "a = " << a ;
	cout << " b = " << b << endl;

}

//注意事项
//1.自动类型推导：必须推导出一致的数据类型T才可使用
void test02() {
	int a = 10, b = 20;
	char c = 'c';

	mySwap(a, b);//正确
	//mySwap(a, c);//不可
	cout << "a = " << a;
	cout << " b = " << b << endl;
}

//2.模板必须要确定出T的数据类型才可使用
template<class T>
void func() {
	cout << "func 调用" << endl;
}
void test03() {
	//func();模板不能独立使用，必须要确定出T的类型
	func<int>() ;

}

template<class T>
void mySort(T arr[], int len) {
	for (int i = 0; i < len; i++)
	{
		int max = i;
		for (int j = 0; j < len; j++)
		{
			if (arr[max]<arr[j])
			{
				max = j;
			}
		}
		if (max!=i)
		{
			mySwap(arr[max], arr[i]);
		}
	}
}
template<class T>
void printArray(T arr[], int len) {
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void test04() {

	//测试char数组
	char charArr[] = "bdcfgeahj";
	int num = sizeof(charArr) / sizeof(char);
	mySort(charArr, num);
	printArray(charArr, num);

}

void test05() {
	//测试int数组
	int intArr[] = { 7,5,8,1,3,9,2,4,6 };
	int num = sizeof(intArr) / sizeof(int);
	mySort(intArr, num);
	printArray(intArr, num);
}

int myadd01(int a, int b) {
	return a+b
}
template<class T>
T myadd02(T a, T b) {
	return a + b;
}

void test06() {
	int a = 10, b = 20;
	char c = 'c';
	cout << myadd01(a, c) << endl;
	//可，c隐式转化为int
	//myadd02(a,c)//否，若自动类型推导不会发生隐式转化
	cout << myadd02<int>(a, c) << endl;
	//可，指定类型发生了隐式转化

}


int main() {
	test01();
	test02();
	test03();

	system("pause");

	return 0;
}