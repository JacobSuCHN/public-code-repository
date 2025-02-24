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

void HeapAdjust(SqList *L, int s, int m);

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
//对顺序表L进行堆排序
void HeapSort(SqList *L)
{
    int i;
    for (i = L->length / 2; i > 0; i--)
    { //把L中的r构成一个大顶堆
        HeapAdjust(L, i, L->length);
    }
    for (i = L->length; i > 1; i--)
    {
        swap(L, 1, i);           //将堆顶记录和当前未经排序子序列的最后一个记录交换
        HeapAdjust(L, 1, i - 1); //将L->r[1...i-1]重新调整为大顶堆
    }
}
//已知L->r[s...m]中记录的关键字除L->r[s]之外均满足对的定义
//调整L->r[s]的关键字，使L->r[s...m]构成一个大顶堆
void HeapAdjust(SqList *L, int s, int m)
{
    int temp, j;
    temp = L->r[s];
    for (j = 2 * s; j <= m; j *= 2)
    { //沿关键字较大的孩子结点向下筛选
        if (j < m && L->r[j] < L->r[j + 1])
        {
            ++j; // j为关键字中较大记录的下标
        }
        if (temp >= L->r[j])
        {
            break; // 最大值已经在堆顶，不进行位置更换
        }
        L->r[s] = L->r[j];
        s = j;
    }
    L->r[s] = temp; //插入
}
void main()
{
    SqList L;
    init(&L);
    print(L);
    HeapSort(&L);
    print(L);
}