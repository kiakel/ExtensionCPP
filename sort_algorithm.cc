#include "./sort_algorithm.h"
#include <iostream>
using namespace std;
// 从小到大排列
void swap(int &left, int &right)
{
	if ((left ^ right) != 0)
	{
		left = left ^ right;
		right = left ^ right;
		left = left ^ right;
	}
}

void printArr(int *pArr, int arrLen)
{
	for (int index=0;index<arrLen;++index)
	{
		cout << *(pArr + index);
		if (index ^ (arrLen-1))
		{
			cout << ",";
		}
		else
		{
			cout << endl;
		}
	}
}


/***************************************冒泡排序*********************************/
void sortBubble(int *pArr, int arrLen)
{
	cout << "source:";
	printArr(pArr, arrLen);
	// 假定最后一位已排序，剩余序列逐次遍历，每次找出一个排序数字
	for (int outterIndex = 0; outterIndex < arrLen - 1; ++outterIndex)
	{
		bool isSorted = true; // 如果相邻两个元素不再交换数据，说明序列已经是排序状态
		// 剩余未排序(n-1-已排序个数)两两比较
		for (int innerIndex = 0; innerIndex < arrLen - 1 - outterIndex; ++innerIndex)
		{
			if (*(pArr + innerIndex) > *(pArr + innerIndex + 1))
			{
				swap(*(pArr + innerIndex), *(pArr + innerIndex + 1));
				isSorted = false;
			}
		}
		
		if (isSorted)
		{
			break;
		}
		printArr(pArr, arrLen);
	}
}


/****************************************快速排序********************************/

void swapArr(int arr[], int index1, int index2)
{
	int tmp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = tmp;
}

int retMidValue(int arr[], int leftIndex, int rightIndex)
{
	int midIndex = (leftIndex + rightIndex) / 2;
	if ((arr[midIndex] >= arr[leftIndex] && arr[midIndex] <= arr[rightIndex])
		|| (arr[midIndex] <= arr[leftIndex] && arr[midIndex] >= arr[rightIndex]))
	{
		swapArr(arr, midIndex, rightIndex);
		return rightIndex;
	}

	if (arr[leftIndex] > arr[midIndex])
	{
		swapArr(arr, leftIndex, midIndex);
	}
	if (arr[midIndex] > arr[rightIndex])
	{
		swapArr(arr, midIndex, rightIndex);
	}
	if (arr[leftIndex] > arr[midIndex])
	{
		swapArr(arr, leftIndex, midIndex);
	}

	swapArr(arr, midIndex, rightIndex);
	return rightIndex;
}

int splitArr(int arr[], int firstIndex, int lastIndex)
{
	int midValue = arr[retMidValue(arr, firstIndex, lastIndex)];
	int arrLen = lastIndex - firstIndex + 1;
	int leftIndex = firstIndex;
	int rightIndx = lastIndex - 1;

	while (leftIndex < rightIndx)
	{
		while (arr[leftIndex] < midValue)
		{
			leftIndex++;
		}

		while (arr[rightIndx] > midValue)
		{
			rightIndx--;
		}

		if (leftIndex < rightIndx)
		{
			swapArr(arr, leftIndex, rightIndx);
		}
		else
		{
			break;
		}
	}

	swapArr(arr, leftIndex, lastIndex);
	return leftIndex;
}

void quick_sort(int arr[], int leftIndex, int rightIndex)
{
	if ((rightIndex - leftIndex) < 1)
	{
		return;
	}
	int index = splitArr(arr, leftIndex, rightIndex);
	quick_sort(arr, leftIndex, index - 1);
	quick_sort(arr, index + 1, rightIndex);
}
void quick_sort(int arr[], int length)
{
	quick_sort(arr, 0, length - 1);
	printArr(arr, length);
}


/******************************************选择插入排序*****************************/
void insert_sort(int arr[], int length)
{
	for (int outter = 1;outter<length;++outter)
	{
		int value = arr[outter];
		for (int inner = outter-1; inner>=0; --inner)
		{
			if (arr[inner]>value)
			{
				arr[inner + 1] = arr[inner];
				arr[inner] = value;
			}
		}
	}
	printArr(arr, length);
}

/************************************************************************/