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

typedef int Status;   // Status是函数的类型，其值是函数的状态代码，如OK等
typedef int ElemType; // ElemType类型根据实际情况而定，这里假设为int

typedef struct StackNode
{
    ElemType data;
    struct StackNode *next;
} StackNode, *LinkStackPtr;
typedef struct LinkStack
{
    LinkStackPtr top;
    int count;
} LinkStack;

Status Push(LinkStack *S, ElemType e);
Status Pop(LinkStack *S, ElemType *e);

Status InitStack(LinkStack *S);
Status ClearStack(LinkStack *S);
Status StackEmpty(LinkStack S);
Status GetTop(LinkStack S, int *e);
Status StackLength(LinkStack S);
Status StackTraverse(LinkStack S);
//插入元素e为新的栈顶元素
Status Push(LinkStack *S, ElemType e)
{
    LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
    s->data = e;
    s->next = S->top; //把当前的栈顶元素赋值给新结点的直接后继
    S->top = s;       //将新结点s赋值给栈顶元素
    S->count++;
    return OK;
}

//若栈不空，则删除S的栈顶元素，用e返回其值
Status Pop(LinkStack *S, ElemType *e)
{
    LinkStackPtr p;
    if (StackEmpty(*S))
    {
        return ERROR;
    }
    *e = S->top->data;
    p = S->top;            //将栈顶结点赋值给p
    S->top = S->top->next; //使得栈顶指针下移一位，指向后一结点
    free(p);               //释放节点p
    S->count--;
    return OK;
}

//----------------------------
//以下是自己写的

Status InitStack(LinkStack *S)
{
    LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
    S->top = s;
    S->count = 0;
    return OK;
}

Status ClearStack(LinkStack *S)
{
    LinkStackPtr p, q;
    p = S->top;
    for (int i = 0; i < S->count; i++)
    {
        q = p->next; //将p的下一个结点赋给q
        free(p);     //释放当前结点p
        p = q;       //将下一节点q赋值给p
    }
    S->count = 0;
    return OK;
}
Status StackEmpty(LinkStack S)
{
    if (S.count == 0)
    {
        return OK;
    }
    return ERROR;
}
Status GetTop(LinkStack S, int *e)
{
    *e = S.top->data;
}
Status StackLength(LinkStack S)
{
    return S.count;
}
Status StackTraverse(LinkStack S)
{
    LinkStackPtr p;
    p = S.top;
    for (int i = 0; i < S.count; i++)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}
void main()
{
    LinkStack S;
    int e;
    InitStack(&S);
    for (int i = 0; i < 10; i++)
    {
        Push(&S, i);
    }
    printf("Length:%d\n", StackLength(S));
    StackTraverse(S);
    Pop(&S, &e);
    printf("Pop:%d\n", e);
    StackTraverse(S);
    GetTop(S, &e);
    printf("Top:%d\n", e);
    ClearStack(&S);
    if (StackEmpty(S))
    {
        printf("Empty\n");
    }
}