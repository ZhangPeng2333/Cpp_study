#if 0
#include <iostream>
using namespace std;

class Base {
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

// 公共继承
class Son1 : public Base {
public:
	void func() {
		m_A; // public → public
		m_B; // protected → protected
		// m_C; // private 不可访问
	}
};

// 保护继承
class Son2 : protected Base {
public:
	void func() {
		m_A; // public → protected
		m_B; // protected → protected
	}
};

// 私有继承
class Son3 : private Base {
public:
	void func() {
		m_A; // public → private
		m_B; // protected → private
	}
};

void test_ExtendType() {
	Son1 s1;
	s1.m_A;          // 外部可访问 public
	// s1.m_B;       // 外部不可访问 protected
	// s1.m_C;

	Son2 s2;
	// s2.m_A;       // 外部不可访问 (protected)

	Son3 s3;
	// s3.m_A;       // 外部不可访问 (private)
}

int main() {
	test_ExtendType();
	
	system("pause");
	return 0;
}
#endif // 1
