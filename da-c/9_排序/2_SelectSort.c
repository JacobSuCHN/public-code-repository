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

//对顺序表L作简单选择排序
void SelectSort(SqList *L)
{
    int i, j, min;
    for (i = 1; i < L->length; i++)
    {
        min = i; //将当前下标定义为最小值下标
        for (j = i + 1; j <= L->length; j++)
        { //循环之后的数据
            if (L->r[min] > L->r[j])
            {            //如果有小于最小值的关键字
                min = j; //将此关键字的下标赋值给min
            }
        }
        if (i != min)
        { //若min不等于i，说明找到最小值，交换
            swap(L, i, min);
        }
    }
}
void main()
{
    SqList L;
    init(&L);
    print(L);
    SelectSort(&L);
    print(L);
}