#if 0
#include <iostream>
using namespace std;

// 普通菱形继承（数据冗余 + 二义性）
class Animal {
public:
	int m_Age;
};

class Sheep : public Animal {};
class Tuo : public Animal {};

class SheepTuo : public Sheep, public Tuo {};

void test_Diamond() {
	SheepTuo st;
	// st.m_Age;          // 歧义，编译错误
	st.Sheep::m_Age = 100;
	st.Tuo::m_Age = 200;
	cout << "普通菱形继承：\n";
	cout << "st.Sheep::m_Age = " << st.Sheep::m_Age << endl;
	cout << "st.Tuo::m_Age   = " << st.Tuo::m_Age << endl;
}

// 虚继承解决菱形继承（共享同一份基类数据）
class AnimalVir {
public:
	int m_Age;
};

class SheepVir : virtual public AnimalVir {};
class TuoVir : virtual public AnimalVir {};

class SheepTuoVir : public SheepVir, public TuoVir {};

void test_VirDiamond() {
	SheepTuoVir st;
	st.m_Age = 999;          // 直接访问，无歧义，共享一份
	cout << "虚继承后 m_Age = " << st.m_Age << endl;
}

int main() {
	test_Diamond();
	test_VirDiamond();
	system("pause");
	return 0;
}
#endif // 0
