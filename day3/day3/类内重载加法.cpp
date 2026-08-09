#if 0
#include <iostream>
using namespace std;

class Point {
public:
	Point() {};
	Point(int x, int y) : x(x), y(y) {};
	Point operator+(const Point &b) { //类内重载，运算符重载函数作为类的成员函数
		Point ret;
		ret.x = this->x + b.x;
		ret.y = this->y + b.y;
		return ret;
	}
	int x, y;
};

//int main() {
//	Point a(2, 4), b(5, 3);
//	Point c = a + b;      //这里c++编译器会，自动去找 + 运算符的重载函数
//	cout << "x :" << c.x << endl;
//	cout << "y :" << c.y << endl;
//}
#endif