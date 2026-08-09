#if 0
#include <iostream>
using namespace std;

class Point {
public:
	Point() {};
	Point(int x, int y) : x(x), y(y) {};
	friend Point operator+(const Point &, const Point &);   //声明类的友元函数
	int x, y;
};

Point operator+(const Point &a, const Point &b) {//类外重载,运算符重载函数作为类的友元函数
	Point ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return ret;
}

//int main() {
//	Point a(2, 4), b(5, 3);
//	Point c = a + b;
//	cout << "x :" << c.x << endl;
//	cout << "y :" << c.y << endl;
//}
#endif