#include "spdlog/spdlog.h"
#include <string.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(65001);
#endif

	// 普通打印
	spdlog::info("Welcome to info spdlog!");
	spdlog::info("中国!");

	// 格式化打印
	// 打印字符串
	spdlog::info("Hello World {}", "spdlog!");
	// 打印数字
	spdlog::error("spdlog errCode : {}", -10020);
	// 指定打印数字的占位符
	spdlog::warn("spdlog format char {:08d}", 12);
	// 格式化打印不同进制的数据
	spdlog::critical("Support for int:{0:d} hex:{0:x} oct:{0:o} bin:{0:b}", 42);
	// 打印浮点型数据
	spdlog::info("float args are {:03.2f}", 1.23456);
	// 打印多个参数
	spdlog::info("string args are {0} {1}..", "too", "supported");
	spdlog::info("number args are {0} {1} {2}..", 10020, 10040, -100);

	spdlog::trace("HEllo");
	system("pause");
}
