/**
 * static 成员变量、成员函数
 * static 头文件变量
 */
#ifndef _USE_STATIC_H
#define _USE_STATIC_H
#include <iostream>

using namespace std;

static const int h_static_const_int11 = 11; // 在包含该头文件的源文件中，该变量在源文件中重新开辟空间。并不能作为全局变量
static int h_static_int12 = 12; // 在包含该头文件的源文件中，该变量在源文件中重新开辟空间。并不能作为全局变量
// int h_int_13; // 导致重定义
// int * h_int_pointer; // 导致重定义

struct TESTS
{
	int a;
}; // 只能声明不能定义变量(VS中不可以定义变量，GCC中可以定义变量并且在源文件是可以共享的)

class useStatic
{
public:
	static const int m_static_const=14; // 声明式，定义式在源文件
	static int m_static_int; // 源文件定义
	// inline static int m_inline_static_int = 15; // C++17标准
	static void func()
	{
		cout << "useStatic::func()" << endl;
	}
};

#endif