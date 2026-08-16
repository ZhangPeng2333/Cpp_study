#if 0
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//write file
void test01() {
	ofstream ofs;
	ofs.open("test.txt", ios::out);
	ofs << "name:zhangsan" << endl;
	ofs << "sex:man" << endl;
	ofs << "age:18" << endl;

	ofs.close();
}

//read file
void test02() {
	ifstream ifs;
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "file open err" << endl;
		return;
	}

	//1.
	//char buf[1024] = { 0 };
	//while (ifs>>buf)
	//{
		//cout << buf << endl;
	//}

	////2.
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf,sizeof(buf))
	//{
	//	cout << buf << endl;
	//}

	// 3.
	/*string buf;
	while (getline(ifs,buf))
	{
		cout << buf << endl;
	}*/

	char c;
	while ((c = ifs.get()) != EOF)
	{
		cout << c;
	}

	ifs.close();
}

class Person {
public:
	char m_Name[64];
	int m_Age;

};

//二进制文件 写文件
void test03() {
	//1.包含头文件

	//2.创建输出流对象
	ofstream ofs("person.txt", ios::out | ios::binary);

	//3.打开文件
	//ofs.open("person.txt", ios::out | ios::binary);

	Person p = { "张三",18 };

	//4.写文件
	ofs.write((const char*)&p, sizeof(p));

	//5.关闭文件
	ofs.close();
}

//二进制文件 读文件
void test04() {
	ifstream ifs("person.txt", ios::in | ios::binary);
	if (!ifs.is_open())
	{
		cout << "file open err" << endl;
		return;
	}

	Person p;
	ifs.read((char*)&p, sizeof(p));

	cout << "Name: " << p.m_Name << " Age: " << p.m_Age << endl;
}

int main() {
	test04();

	system("pause");

	return 0;
}
#endif // 0
