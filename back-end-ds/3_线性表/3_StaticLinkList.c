#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <io.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000 //存储空间初始分配量

typedef int Status;   //Status是函数的类型，其值是函数的状态代码，如OK等
typedef int ElemType; //ElemType类型根据实际情况而定，这里假设为int

typedef struct
{
    ElemType data;
    int cur; //游标（Cursor），为0时表示无指向
} Component, StaticLinkList[MAXSIZE];

Status InitList(StaticLinkList space);
int ListLength(StaticLinkList L);
int Malloc_SLL(StaticLinkList space);
Status ListInsert(StaticLinkList L, int i, ElemType e);
void Free_SLL(StaticLinkList space, int k);
Status ListDelete(StaticLinkList L, int i, int *e);

Status GetElem(StaticLinkList L, int i, ElemType *e);
Status ListTraverse(StaticLinkList L);
Status ListEmpty(StaticLinkList L);
Status ClearList(StaticLinkList L);
Status LocateElem(StaticLinkList L, int e);

//将一维数组space中各分量链成一备用链表
//space[0].cur为头指针，"0"表示为空指针
Status InitList(StaticLinkList space)
{
    int i;
    for (i = 0; i < MAXSIZE - 1; i++)
    {
        space[i].cur = i + 1;
    }
    space[MAXSIZE - 1].cur = 0; //目前静态链表为空，最后一个元素的cur为0
    return OK;
}

//返回L中数据元素个数
int ListLength(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE - 1].cur;
    while (i)
    {
        i = L[i].cur;
        j++;
    }
    return j;
}

//若备用空间链表非空，则返回分配的结点下标，否则返回0
int Malloc_SLL(StaticLinkList space)
{
    int i = space[0].cur; //当前数组第一个元素的cur存的值，
                          //就是要返回的第一个备用空间的下标

    if (space[0].cur)
    {
        space[0].cur = space[i].cur; //由于要拿出一个分量来使用了
                                     //所以我们就得把它的下一个分量来做备用
    }
    return i;
}
//在L中第i个元素之前插入新的元素e
Status ListInsert(StaticLinkList L, int i, ElemType e)
{
    int j, k, l;
    k = MAXSIZE - 1; //注意k首先是最后一个元素的下标
    if (i < 1 || i > ListLength(L) + 1)
    {
        return ERROR;
    }
    j = Malloc_SLL(L); //获得空闲分量下标
    if (j)
    {
        L[j].data = e; //将数据赋值给此分量的data
        for (l = 1; l <= i - 1; l++)
        {
            k = L[k].cur; //找到第i个元素之前的位置
        }
        L[j].cur = L[k].cur; //把第i个元素之前的cur赋值给新元素的cur
        L[k].cur = j;        //把新元素的下标赋值给第i个元素之前元素的cur
        return OK;
    }
    return ERROR;
}
//将下标为k的空闲结点回收到备用链表
void Free_SLL(StaticLinkList space, int k)
{
    space[k].cur = space[0].cur; //把第一个元素cur值赋给要删除的分量cur
    space[0].cur = k;            //把要删除的分量下标赋值给第一个元素的cur
}
//删除L中第i个数据元素
Status ListDelete(StaticLinkList L, int i, int *e)
{
    int j, k;
    if (i < 1 || i > ListLength(L))
    {
        return ERROR;
    }
    k = MAXSIZE - 1;
    for (j = 1; j <= i - 1; j++)
    {
        k = L[k].cur;
    }
    j = L[k].cur;
    L[k].cur = L[j].cur;
    *e = L[j].data;
    Free_SLL(L, j);
    return OK;
}

//----------------------------

//以下是自己写的
Status GetElem(StaticLinkList L, int i, ElemType *e)
{
    int k;
    k = L[MAXSIZE - 1].cur;
    if (i < 1 || i > ListLength(L) + 1)
    {
        return ERROR;
    }
    for (int j = 1; j < i; j++)
    {
        k = L[k].cur;
    }
    *e = L[k].data;
    return OK;
}
Status ListTraverse(StaticLinkList L)
{
    int k;
    k = L[MAXSIZE - 1].cur;
    if (L[MAXSIZE - 1].cur == 0)
    {
        return ERROR;
    }
    for (int i = 0; i < ListLength(L); i++)
    {
        printf("%d\t", L[k].data);
        k = L[k].cur;
    }
    printf("\n");
    return OK;
}
Status ListEmpty(StaticLinkList L)
{
    if (L[MAXSIZE - 1].cur)
    {
        return ERROR;
    }
    return OK;
}
Status ClearList(StaticLinkList L)
{
    int e;
    while (ListLength(L))
    {
        ListDelete(L, 1, &e);
    }
    return OK;
}
Status LocateElem(StaticLinkList L, int e)
{
    int k;
    k = L[MAXSIZE - 1].cur;
    if (L[MAXSIZE - 1].cur == 0)
    {
        return ERROR;
    }
    for (int i = 1; i <= ListLength(L); i++)
    {

        if (L[k].data == e)
        {
            return i;
        }
        k = L[k].cur;
    }
    return OK;
}

void main()
{
    StaticLinkList L;
    int e;
    InitList(L);
    for (int i = 0; i < 10; i++)
    {
        ListInsert(L, 1, i);
    }
    printf("Length:%d\n", ListLength(L));
    ListTraverse(L);
    ListDelete(L, 1, &e);
    printf("e:%d\n", e);
    ListTraverse(L);
    GetElem(L, 5, &e);
    printf("e:%d\n", e);
    printf("Locate:%d\n", LocateElem(L, 5));
    ClearList(L);
    if (ListEmpty(L))
    {
        printf("Empty\n");
    }
}
