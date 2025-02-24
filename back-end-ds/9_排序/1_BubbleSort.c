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

//对顺序表L作交换排序（冒泡排序初级版）
void BubbleSort0(SqList *L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
    {
        for (j = i + 1; j <= L->length; j++)
        {
            if (L->r[i] > L->r[j])
            {
                swap(L, i, j); //交换L->r[i]与L->r[j]的值
            }
        }
    }
}
//对顺序表L作冒泡排序
void BubbleSort1(SqList *L)
{
    int i, j;
    for (i = 1; i < L->length; i++)
    {
        for (j = L->length - 1; j >= i; j--)
        { //注意j是从后往前排序
            if (L->r[j] > L->r[j + 1])
            {                      //若前者大于后者
                swap(L, j, j + 1); //交换L->r[j]与L->r[j+1]的值
            }
        }
    }
}
//对顺序表L作改进冒泡排序
void BubbleSort2(SqList *L)
{
    int i, j;
    Status flag = TRUE; // flag用来作为标记
    for (i = 1; i < L->length && flag; i++)
    {
        flag = FALSE; //初始为false
        for (j = L->length - 1; j >= i; j--)
        { //注意j是从后往前排序
            if (L->r[j] > L->r[j + 1])
            {                      //若前者大于后者
                swap(L, j, j + 1); //交换L->r[j]与L->r[j+1]的值
                flag = TRUE;       //如果有数据交换，则flag为true
                                   //没有数据交换说明已经排好了
            }
        }
    }
}
void main()
{
    SqList L;
    init(&L);
    print(L);
    BubbleSort0(&L);
    printf("BubbleSort0:");
    print(L);
    init(&L);
    BubbleSort1(&L);
    printf("BubbleSort1:");
    print(L);
    init(&L);
    BubbleSort2(&L);
    printf("BubbleSort2:");
    print(L);
}