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

#define MAXSIZE 100 //存储空间初始分配量

typedef int Status;   //Status是函数的类型，其值是函数的状态代码，如OK等
typedef int ElemType; //ElemType类型根据实际情况而定，这里假设为int

//线性表的顺序存储结构
typedef struct
{
    ElemType data[MAXSIZE]; //数组存储数据元素，最大值为MAXSIZE
    int length;             //线性表当前长度
} SqList;

Status GetElem(SqList L, int i, ElemType *e);
Status ListInsert(SqList *L, int i, ElemType e);
Status ListDelete(SqList *L, int i, ElemType *e);

Status InitList(SqList *L);
Status ListEmpty(SqList L);
Status ClearList(SqList *L);
Status LocateElem(SqList L, int e);
Status ListLength(SqList L);
Status ListTraverse(SqList L);

//初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
//操作结果：用e返回L中第i个数据元素的值
Status GetElem(SqList L, int i, ElemType *e)
{
    if (L.length == 0 || i < 1 || i > L.length)
    {
        return ERROR; //线性表不存在或不合法
    }
    *e = L.data[i - 1]; //找到第i个元素，其下标为i-1
    return OK;
}

//初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
//操作结果：在L中第i个元素之前插入新元素e，表长加1
Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;
    if (L->length == MAXSIZE)
    { //线性表已满
        return ERROR;
    }
    if (i < 1 || i > L->length + 1)
    { //i不在范围内
        return ERROR;
    }
    if (i < L->length)
    { //插入元素不在表尾
        for (k = L->length - 1; k >= i - 1; k--)
        {
            L->data[k + 1] = L->data[k]; //将要插入位置后的数据元素向后移动一位
        }
    }
    L->data[i - 1] = e; //将新元素插入
    L->length++;        //表长加1
    return OK;
}

//初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
//操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;
    if (L->length == 0)
    { //线性表为空
        return ERROR;
    }
    if (i < 1 || i > L->length)
    { //删除位置不正确
        return ERROR;
    }
    *e = L->data[i - 1]; //将要删除的值给e
    if (i < L->length)
    { //删除不是最后位置
        for (k = i; k < L->length; k++)
        {
            L->data[k - 1] = L->data[k]; //将删除位置后继元素前移
        }
    }
    L->length--; //表长减1
    return OK;
}

//----------------------------
//以下是自己写的
Status InitList(SqList *L)
{
    L->length = 0;
    return OK;
}
Status ListEmpty(SqList L)
{
    if (L.length != 0)
    {
        return FALSE;
    }
    return TRUE;
}
Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}
Status LocateElem(SqList L, int e)
{
    if (L.length == 0)
    {
        return ERROR;
    }
    for (int i = 0; i < L.length; i++)
    {
        if (L.data[i] == e)
        {
            return i + 1;
        }
    }
    return ERROR;
}
Status ListLength(SqList L)
{
    return L.length;
}
Status ListTraverse(SqList L)
{
    if (L.length == 0)
    {
        return ERROR;
    }
    for (int i = 0; i < ListLength(L); i++)
    {
        printf("%d\t", L.data[i]);
    }
    printf("\n");
    return OK;
}

void main()
{
    SqList L;
    int e;
    InitList(&L);
    for (int i = 0; i < 10; i++)
    {
        ListInsert(&L, 1, i);
    }
    printf("Length:%d\n", ListLength(L));
    ListTraverse(L);
    ListDelete(&L, 1, &e);
    printf("e:%d\n", e);
    ListTraverse(L);
    GetElem(L, 3, &e);
    printf("e:%d\n", e);
    printf("Locate:%d\n", LocateElem(L, 5));
    ClearList(&L);
    if (ListEmpty(L))
    {
        printf("Empty\n");
    }
}