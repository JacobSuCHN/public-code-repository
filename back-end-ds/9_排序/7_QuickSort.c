#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <io.h>

#define MAXSIZE 9 //用于要排序数组个数的最大值
#define TRUE 1
#define FALSE 0

typedef int Status; // Status是函数的类型，其值是函数的状态代码，如OK等

typedef struct
{
    int r[MAXSIZE + 1]; //用于存储要排序数组，r[0]用作哨兵或临时变量
    int length;         //用于记录顺序表的长度
} SqList;

void QSort0(SqList *L, int low, int high);
int Partition0(SqList *L, int low, int high);
void QSort1(SqList *L, int low, int high);
int Partition1(SqList *L, int low, int high);

Status init(SqList *L)
{
    int i;
    int d[MAXSIZE] = {50, 10, 90, 30, 70, 40, 80, 60, 20};
    L->r[0] = 0;
    L->length = 0;
    for (i = 0; i < MAXSIZE; i++)
    {
        L->r[i + 1] = d[i];
        L->length++;
    }
    return TRUE;
}
void print(SqList L)
{
    int i;
    for (i = 1; i < L.length; i++)
    {
        printf("%d,", L.r[i]);
    }
    printf("%d", L.r[i]);
    printf("\n");
}
//交换L中数组r的下标为i和j的值
void swap(SqList *L, int i, int j)
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}
//对顺序表L作直接插入排序
void InsertSort(SqList *L)
{
    int i, j;
    for (i = 2; i <= L->length; i++)
    {
        if (L->r[i] < L->r[i - 1])
        {                      //需将L->r[i]插入有序子表
            L->r[0] = L->r[i]; //设置哨兵
            for (j = i - 1; L->r[j] > L->r[0]; j--)
            {
                L->r[j + 1] = L->r[j]; //记录后移
            }
            L->r[j + 1] = L->r[0]; //插入到正确位置
        }
    }
}
//对顺序表L作快速排序
void QuickSort0(SqList *L)
{
    QSort0(L, 1, L->length);
}
//对顺序表L中的子序列L->r[low..high]作快速排序
void QSort0(SqList *L, int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = Partition0(L, low, high); //将L->r[low..high]一分为二算出枢轴值pivot
        QSort0(L, low, pivot - 1);        //对低子表递归排序
        QSort0(L, pivot + 1, high);       //对高子表递归排序
    }
}
//交换顺序表L中子表的记录，使枢轴记录到位，并返回其所在位置
//此时在它之前比它小，在它之后比它大
int Partition0(SqList *L, int low, int high)
{
    int privotkey;
    privotkey = L->r[low]; //用子表的第一个记录作枢轴记录
    while (low < high)
    {
        while (low < high && L->r[high] >= privotkey)
        {
            high--;
        }
        swap(L, low, high); //将比枢轴记录小的交换到低端
        while (low < high && L->r[low] <= privotkey)
        {
            low++;
        }
        swap(L, low, high); //将比枢轴记录大的交换到高端
    }
    return low; //返回枢轴所在位置
}
//对顺序表L作快速排序
void QuickSort1(SqList *L)
{
    QSort1(L, 1, L->length);
}
#define MAX_LENGTH_INSERT_SORT 7 //数组长度阈值
//对顺序表L中的子序列L->r[low..high]作快速排序
void QSort1(SqList *L, int low, int high)
{
    int pivot;
    if ((high - low) > MAX_LENGTH_INSERT_SORT)
    { //当high-low大于阈值时用快速排序
        while (low < high)
        {
            pivot = Partition1(L, low, high); //将L->r[low..high]一分为二算出枢轴值pivot
            QSort1(L, low, pivot - 1);       //对低子表递归排序
            low = pivot + 1;                 //尾递归
        }
    }
    else
    { //当high-low小于等于阈值时用插入排序
        InsertSort(L);
    }
}
//交换顺序表L中子表的记录，使枢轴记录到位，并返回其所在位置
//此时在它之前比它小，在它之后比它大
int Partition1(SqList *L, int low, int high)
{
    int privotkey;
    int m = low + (high - low) / 2; //计算中间元素的下标
    if (L->r[low] > L->r[high])
    {
        swap(L, low, high); //交换左端与右段的数据，保证左端较小
    }
    if (L->r[m] > L->r[high])
    {
        swap(L, high, m); //交换中间与右段的数据，保证中间较小
    }
    if (L->r[m] > L->r[low])
    {
        swap(L, m, low); //交换中间与左段的数据，保证中间较小
    }
    //此时L.r[low]为左中右端的中间值

    privotkey = L->r[low]; //用子表的第一个记录作枢轴记录
    L->r[0] = privotkey;   //将枢轴关键字备份到L->r[0]
    while (low < high)
    {
        while (low < high && L->r[high] >= privotkey)
        {
            high--;
        }
        L->r[low] = L->r[high]; //采用替换而不是交换的方式进行操作
        while (low < high && L->r[low] <= privotkey)
        {
            low++;
        }
        L->r[high] = L->r[low]; //采用替换而不是交换的方式进行操作
    }
    L->r[low] = L->r[0]; //将枢轴值替换回L.r[low]
    return low;          //返回枢轴所在位置
}
void main()
{
    SqList L;
    init(&L);
    print(L);
    QuickSort0(&L);
    print(L);
    init(&L);
    QuickSort1(&L);
    print(L);
}