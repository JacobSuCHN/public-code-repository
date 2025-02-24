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

void MSort(int SR[], int TR1[], int s, int t);
void HeapAdjust(SqList *L, int s, int m);
void MergePass(int SR[], int TR[], int s, int n);
void Merge(int SR[], int TR[], int i, int m, int n);

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
//对顺序表L作归并排序（递归）
void MergeSort1(SqList *L)
{
    MSort(L->r, L->r, 1, L->length);
}
//将SR[s...t]归并排序为TR1[s...t]（递归）
void MSort(int SR[], int TR1[], int s, int t)
{
    int m;
    int TR2[MAXSIZE];
    if (s == t)
    {
        TR1[s] = SR[s];
    }
    else
    {
        m = (s + t) / 2;          //将SR[s...t]平分为SR[s...m]和SR[m+1...t]
        MSort(SR, TR2, s, m);     //递归将SR[s...m]归并为有序的TR2[s...m]
        MSort(SR, TR2, m + 1, t); //递归将SR[m+1...t]归并为有序的TR2[m+1...t]
        Merge(TR2, TR1, s, m, t); //将TR2[s...m]和TR2[m+1...t]归并到TR1[s...t]
    }
}
//将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n]
void Merge(int SR[], int TR[], int i, int m, int n)
{
    int j, k, l;
    for (j = m + 1, k = i; i <= m && j <= n; k++)
    { //将SR中的记录由小到大归并入TR
        if (SR[i] < SR[j])
        {
            TR[k] = SR[i++];
        }
        else
        {
            TR[k] = SR[j++];
        }
    }
    if (i <= m)
    {
        for (l = 0; l <= m - i; l++)
        {
            TR[k + l] = SR[i + l]; //将剩余的SR[i...m]复制到TR
        }
    }
    if (j <= n)
    {
        for (l = 0; l <= n - j; l++)
        {
            TR[k + l] = SR[j + l]; //将剩余的SR[j...n]复制到TR
        }
    }
}
//对顺序表L作归并排序（非递归）
void MergeSort2(SqList *L)
{
    int *TR = (int *)malloc(L->length * sizeof(int)); //申请额外空间
    int k = 1;
    while (k < L->length)
    {
        MergePass(L->r, TR, k, L->length);
        k = 2 * k; //子序列长度加倍
        MergePass(TR, L->r, k, L->length);
        k = 2 * k; //子序列长度加倍
    }
}
//将SR[]中相邻长度为s的子序列两两归并到TR[]
void MergePass(int SR[], int TR[], int s, int n)
{
    int i = 1;
    int j;
    while (i <= n - 2 * s + 1)
    {
        Merge(SR, TR, i, i + s - 1, i + 2 * s - 1); //两两归并
        i = i + 2 * s;
    }
    if (i < n - s + 1)
    { //归并最后两个序列
        Merge(SR, TR, i, i + s - 1, n);
    }
    else
    { //若最后只剩下单个子序列
        for (j = i; j <= n; j++)
        {
            TR[j] = SR[j];
        }
    }
}
void main()
{
    SqList L;
    init(&L);
    print(L);
    MergeSort1(&L);
    print(L);
    init(&L);
    MergeSort2(&L);
    print(L);
}