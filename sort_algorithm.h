#ifndef _SORT_ALGORITHM_H
#define _SORT_ALGORITHM_H
/**
 * 内层循环对 未排序 序列 两两相邻 比较每次找出最大值或者最小值
 * 外层循环控制只遍历 未排序 序列
 */
void sortBubble(int *pArr, int arrLen);


/**
 * a、计算序列中的中间元素midValue,midValue放置于序列最后
 * b、从序列开始位置startIndex 向右 查找比midValue大的元素索引BigIndex
 * c、从序列倒数第二个开始smallEndIndex 向左 查找比midValue小的元素索引LettleIndex
 * d、如果 BigIndex<LettleIndex,两个元素交换
 * e、如果startIndex<smallEndIndex,循环b、c、d三步
 * f、将midValue值和startIndex的值交换，至此序列被分为midValue左边都是比midValue小，midValue右边都比midValue大。
 */
void quick_sort(int arr[], int length);

/**
 * 外层循环控制遍历未排序 序列
 * 内层循环对已排序 向前 遍历，选择外层元素插入位置,插入位置后的元素后移
 */
void insert_sort(int arr[],int length);


#endif