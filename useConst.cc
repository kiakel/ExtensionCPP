#include "./useConst.h"
#include <iostream>
using namespace std;

const int cc_const_int = 32;
int cc_int = 55;

void constPrint()
{
	printf("const %p\n", &h_const_int);
}
useConst::useConst(int var)
	: m_const_int(var)
{

}

