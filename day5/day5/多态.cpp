#if 0
#include<iostream>

using namespace std;


class Animal
{
public:
	virtual void speak() {
		cout << "Animal speaking" << endl;
	}
};

class Cat : public Animal {
public:
	void speak() {
		cout << "Cat speaking" << endl;
	}
};

class Dog : public Animal {
public:
	void speak() {
		cout << "Dog speaking" << endl;
	}

};

void DoSpeak(Animal & animal) {
	animal.speak();
}


void test1() {
	Cat cat;
	DoSpeak(cat);

	Dog dog;
	DoSpeak(dog);

}

int main() {
	test1();

	system("pause");

	return 0;
}
#endif // 0
