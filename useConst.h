#ifndef _USE_CONST_H
#define _USE_CONST_H

#include <iostream>
using std::cout;
using std::endl;

const int h_const_int = 11; // 在包含该头文件的源文件中，该变量在源文件中重新开辟空间。
extern int cc_int; // 供包含该头文件的源文件使用cc_int的值。
extern const int cc_const_int; // 供包含该头文件的源文件使用cc_const_int的值。

void constPrint();

class useConst
{
	
public:
	useConst(int var);
	// 非const 对象调用
	const int getValue()
	{
		return this->m_const_int;
	}

	// const 和 非const 对象均可调用
	void useConstFunc() const
	{
		cout << __FUNCDNAME__ << endl;
	}
	const int m_const_int;
};
#endif