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

//线性表的单链表存储结构
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *CLinkList; //定义CLinkList

Status InitList(CLinkList *L);
Status ListLength(CLinkList L);
Status ListEmpty(CLinkList L);
Status GetElem(CLinkList L, int i, ElemType *e);
Status LocateElem(CLinkList L, int e);
Status ListInsert(CLinkList *L, int i, ElemType e);
Status ListDelete(CLinkList *L, int i, ElemType *e);
Status ClearList(CLinkList *L);
Status ListTraverse(CLinkList L);

//初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
//操作结果：用e返回L中第i个数据元素的值
Status GetElem(CLinkList L, int i, ElemType *e)
{
    int j;
    CLinkList p;  //声明一指针p
    p = L->next; //让p指向链表L的第一个结点
    j = 1;       //j为计数器
    while (p && j < i)
    {                //p不为空且计数器j还没有等于i时，循环继续
        p = p->next; //让p指向下一个结点
        ++j;
    }
    if (!p || j > i)
    { //第i个结点不存在
        return ERROR;
    }
    *e = p->data; //取第i个结点的数据
    return OK;
}
//初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
//操作结果：在L中第i个结点位置之前插入新的数据元素e，L的长度加1
Status ListInsert(CLinkList *L, int i, ElemType e)
{
    int j;
    CLinkList p, s;
    p = *L; //p指向头结点
    j = 1;
    while (j < i)
    { //寻找第i-1个结点
        p = p->next;
        ++j;
    }
    if (j > i)
    { //第i个结点不存在
        return ERROR;
    }
    s = (CLinkList)malloc(sizeof(Node)); //生成新结点
    s->data = e;                        //将数据元素e赋值给s->data
    s->next = p->next;                  //将p的后继结点赋值给s的后继
    p->next = s;                        //将s赋值给p的后继
    return OK;
}
//初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
//操作结果：删除L的第i个结点，并用e返回其值，L的长度减1
Status ListDelete(CLinkList *L, int i, ElemType *e)
{
    int j;
    CLinkList p, q;
    p = *L; //p指向头结点
    j = 1;
    while (j < i)
    { //寻找第i-1个结点
        p = p->next;
        ++j;
    }
    if (j > i)
    { //第i个结点不存在
        return ERROR;
    }
    q = p->next;       //将第i个结点赋值给q，即待删除结点p->next
    p->next = q->next; //将q的后继赋值给p的后继
    *e = q->data;      //将q结点中的数据给e
    free(q);           //让系统回收此结点，释放内存
    return OK;
}
//将L重置为空表
Status ClearList(CLinkList *L)
{
    CLinkList p, q;
    p = (*L)->next; //p指向第一个结点
    while (p == *L)
    {
        q = p->next; //将p的下一个结点赋给q
        free(p);     //释放当前结点p
        p = q;       //将下一节点q赋值给p
    }
    (*L)->next = *L; //头结点指针域为空
    return OK;
}

//----------------------------

//以下是自己写的

Status InitList(CLinkList *L)
{
    *L = (CLinkList)malloc(sizeof(Node));
    (*L)->next = *L;
}
Status ListEmpty(CLinkList L)
{
    if (L->next == L)
    {
        return OK;
    }
    return ERROR;
}
Status LocateElem(CLinkList L, int e)
{
    int i = 0;
    CLinkList p;
    p = L->next;
    while (p)
    {
        i++;
        if (p->data == e)
        {
            return i;
        }
        p = p->next;
    }
    return ERROR;
}
Status ListLength(CLinkList L)
{
    int i = 0;
    CLinkList p;
    p = L->next;
    while (p != L)
    {
        i++;
        p = p->next;
    }
    return i;
}
Status ListTraverse(CLinkList L)
{
    CLinkList p;
    p = L->next;
    while (p != L)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

void main()
{
    CLinkList L;
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