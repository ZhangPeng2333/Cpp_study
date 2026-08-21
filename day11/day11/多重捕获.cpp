#if 0
#include <iostream>
#include <stdexcept>
using namespace std;
int main()
{
	string str = "hello";
	try {
		throw range_error("range_error");
		throw invalid_argument("invalid_argument");
		throw length_error("length_error");
		cout << str.at(1000) << endl;
	}
	catch (out_of_range &e)
	{
		cout << "A" << endl;
	}
	catch (length_error& e)
	{
		cout << "B" << endl;
	}
	catch (logic_error& e)
	{
		cout << "C" << endl;
	}
	catch (exception &e)
	{
		cout << "D" << endl;
	}
	cout << "主函数执行结束" << endl;
	return 0;
}
#endif // 0
