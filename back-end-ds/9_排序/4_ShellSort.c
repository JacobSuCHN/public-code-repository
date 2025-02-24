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

Status init(SqList *L)
{
    int i;
    int d[MAXSIZE] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
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
//对顺序表L作希尔排序
void ShellSort(SqList *L)
{
    int i, j;
    int increment = L->length;
    do
    {
        increment = increment / 3 + 1; //增量序列
        for (i = increment + 1; i <= L->length; i++)
        {
            if (L->r[i] < L->r[i - increment])
            {                      //需将L->r[i]插入有序增量子表
                L->r[0] = L->r[i]; //暂存在L->r[0]
                for (j = i - increment; j > 0 && L->r[0] < L->r[j]; j -= increment)
                {
                    L->r[j + increment] = L->r[j]; //记录后移，查找插入位置
                }
                L->r[j + increment] = L->r[0]; //插入
            }
        }
        printf("\t");
        print(*L);
    } while (increment > 1);
}
void main()
{
    SqList L;
    init(&L);
    print(L);
    ShellSort(&L);
    print(L);
}