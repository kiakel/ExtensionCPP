#include "./useExtern.h"
#include "./useConst.h"
#include "./useStatic.h"

#include <iostream>
using namespace std;

// extern const int cc_const_int; 
// extern int cc_int;// 如果useConst.h 没有extern int cc_int的声明，该方法也可以链接到cc_int。

void externPrint()
{
	printf("%p\n", &h_const_int);
	cout << "cc_const_int:" << cc_const_int << endl; // 如果useConst.h 没有extern const int cc_const_int的声明，此处报错。
	cout << "cc_int:" << cc_int << endl;
}