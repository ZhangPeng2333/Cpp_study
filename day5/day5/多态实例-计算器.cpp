#if 0
#include<iostream>
using namespace std;

class AbstraactCalculator
{
public:
	virtual int getResult() {
		return 0;
	}

	int num1;
	int num2;
};

class AddCalculator :public AbstraactCalculator {
public:
	int getResult() {
		return num1 + num2;
	}
};

class SubCalculator :public AbstraactCalculator {
public:
	int getResult() {
		return num1 - num2;
	}
};

class MulCalculator :public AbstraactCalculator {
public:
	int getResult() {
		return num1 * num2;
	}
};


void test02() {

	AbstraactCalculator *abc = new AddCalculator;
	abc->num1 = 10;
	abc->num2 = 20;
	cout << abc->num1 << " + " << abc->num2 << " = " << abc->getResult() << endl;
	delete abc;
	abc = new SubCalculator;
	abc->num1 = 10;
	abc->num2 = 20;
	cout << abc->num1 << " - " << abc->num2 << " = " << abc->getResult() << endl;
	delete abc;
	abc = new MulCalculator;
	abc->num1 = 10;
	abc->num2 = 20;
	cout << abc->num1 << " * " << abc->num2 << " = " << abc->getResult() << endl;
	delete abc;
	abc = NULL;

}

int main() {
	test02();
	system("pause");

	return 0;
}
#endif // 0
