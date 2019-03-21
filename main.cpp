#include "./ExterndUtil.h"
#include "./useStatic.h"
#include "./useConst.h"
#include "./useExtern.h"
#include "./sort_algorithm.h"
#include "./search_algorithm.h"
#include "./struct_tree.h"
#include "./order_list.h"
#include <iostream>
#include <cstdio>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <chrono>
#include <list>

using namespace std;
using namespace ExternUtility;

// 精确到毫秒
string getNowDateTime()
{
	
}


/**
 * 指针
 */
namespace testPointer
{
	double func()
	{
		return double();
	}

	int funcINt(int)
	{
		return int();
	}
	typedef int(*ff)(int);
	ff funcs(int, int)
	{

		return funcINt;
	}
	void testPointerFunc()
	{
		int arrInt[12]{ 1,2,3,4,5 };
		int *parr = arrInt;
		int(*parra)[12] = &arrInt;
		*(parr + 1) = 12;
		int *aa = *parra + 1; // aa==12

		float floatArr[10]{}; // float 数组
		float(*p_float)[10] = &floatArr; // float数组指针
		float(**def)[10] = &p_float; // 二级指针

		double* dArr[10]{}; // double指针数组
		double* (*gh)[10] = &dArr; // 


		double(*f[10])() = { func }; // 函数指针数组

		int* pb[10] = {}; // int指针数组
		int* ((*b)[10]) = &pb;

		long(*fun)(int); // 函数指针
		int(*(*fss)(int, int))(int) = funcs; // 函数指针，返回值也是函数指针
	}
}

namespace testFileCode
{
#include <fstream>
	void fileCode()
	{
		ifstream in("F:\\thread\\filecode.txt",std::ios_base::binary);
		if (in.is_open())
		{
			unsigned char first{};
			unsigned char second{};
			cout << sizeof(first) << endl;
			in.read((char*)&first,sizeof(first));
			int p = first << 8;
			in.read((char*)&second,sizeof(second));
			int pp = p + second;
			in.seekg(0);
			printf("%#x,%#x,%#x,%#x\n", p,pp,first, second);
			string code;
			switch (pp)
			{
			case 0xfffe:  //65534
				code = "Unicode";
				break;
			case 0xfeff://65279
				code = "Unicode big endian";
				break;
			case 0xefbb://61371
				code = "UTF-8";
				break;
			default:
				code = "ANSI";
				break;
			}
			cout << code << endl;
		}
	}


}
using namespace testFileCode;


int main()
{

    /*XMLParser externUtil;
    string xmlPath = "/SUMMIT/COMMON";
    XERCES_CPP_NAMESPACE::DOMDocument* doc = externUtil.parseXMLFile("G:\\GMP2IMA_Bonddef_XS1845207700_20180712.xml");
    cout << externUtil.getNodeTree(doc, xmlPath) << endl;*/

    /*string str = "123mds lSD324DFSGd fgf,ds.,[]sd[(dsfg)dslf?dsf 23.tr,{fd}kls!DS13";
    string regexStr = "[A-Z]{1,}";
    vector<string> result=StringRegex::regexFindAllString(str,regexStr);
    for (auto val:result)
    {
        cout << val << ",";
    }
    cout << endl;*/
	
	
	system("pause");
    return 0;
}
