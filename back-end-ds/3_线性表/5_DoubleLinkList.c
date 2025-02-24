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

//线性表的双向链表存储结构
typedef struct DulNode
{
    ElemType data;
    struct DulNode *prior; //直接前驱指针
    struct DulNode *next;  //直接后继指针
} DulNode, *DuLinkList;

Status GetElem(DuLinkList L, int i, ElemType *e);
Status ListInsert(DuLinkList *L, int i, ElemType e);
Status ListDelete(DuLinkList *L, int i, ElemType *e);
Status ClearList(DuLinkList *L);

Status InitList(DuLinkList *L);
Status ListEmpty(DuLinkList L);
Status LocateElem(DuLinkList L, int e);
Status ListLength(DuLinkList L);
Status ListTraverse(DuLinkList L);

//初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
//操作结果：用e返回L中第i个数据元素的值
Status GetElem(DuLinkList L, int i, ElemType *e)
{
    int j;
    DuLinkList p; //声明一指针p
    p = L->next;  //让p指向链表L的第一个结点
    j = 1;        //j为计数器
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
Status ListInsert(DuLinkList *L, int i, ElemType e)
{
    int j;
    DuLinkList p, s;
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
    s = (DuLinkList)malloc(sizeof(DulNode)); //生成新结点
    s->data = e;                             //将数据元素e赋值给s->data
    s->prior = p;                            //把p赋值给s的前驱
    s->next = p->next;                       //把p->next赋值给s的后继
    p->next->prior = s;                      //把s赋值给p->next的前驱
    p->next = s;                             //把s赋值给p的后继
    return OK;
}
//初始条件：顺序线性表L已存在，1<=i<=ListLength(L)
//操作结果：删除L的第i个结点，并用e返回其值，L的长度减1
Status ListDelete(DuLinkList *L, int i, ElemType *e)
{
    int j;
    DuLinkList p, q;
    p = (*L)->next; //p指向头结点
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
    p->prior->next = p->next;  //把p->next赋值给p->prior的后继
    p->next->prior = p->prior; //把p->prior赋值给p->next的前驱
    *e = p->data;              //将p结点中的数据给e
    free(p);                   //让系统回收此结点，释放内存
    return OK;
}
//将L重置为空表
Status ClearList(DuLinkList *L)
{
    DuLinkList p, q;
    p = (*L)->next; //p指向第一个结点
    while (p != *L)
    {
        q = p->next; //将p的下一个结点赋给q
        free(p);     //释放当前结点p
        p = q;       //将下一节点q赋值给p
    }
    (*L)->next = *L; //头结点指针域为空
    (*L)->prior = *L;
    return OK;
}

//----------------------------

//以下是自己写的

Status InitList(DuLinkList *L)
{
    *L = (DuLinkList)malloc(sizeof(DulNode));
    (*L)->next = *L;
    (*L)->prior = *L;
}
Status ListEmpty(DuLinkList L)
{
    if (L->next == L->prior)
    {
        return OK;
    }
    return ERROR;
}
Status LocateElem(DuLinkList L, int e)
{
    int i = 0;
    DuLinkList p;
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
Status ListLength(DuLinkList L)
{
    int i = 0;
    DuLinkList p;
    p = L->next;
    while (p != L)
    {
        i++;
        p = p->next;
    }
    return i;
}
Status ListTraverse(DuLinkList L)
{
    DuLinkList p;
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
    DuLinkList L;
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
