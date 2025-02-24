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

typedef struct
{
    ElemType data[MAXSIZE];
    int top; //用于栈顶指针
} SqStack;

Status Push(SqStack *S, ElemType e);
Status Pop(SqStack *S, ElemType *e);

Status InitStack(SqStack *S);
Status DestroyStack(SqStack *S);
Status ClearStack(SqStack *S);
Status StackEmpty(SqStack S);
Status GetTop(SqStack S, int *e);
Status StackLength(SqStack S);
Status StackTraverse(SqStack S);

//插入元素e为新的栈顶元素
Status Push(SqStack *S, ElemType e)
{
    if (S->top == MAXSIZE - 1)
    { //栈满
        return ERROR;
    }
    S->top++;            //栈顶指针加1
    S->data[S->top] = e; //将新插入元素赋值给栈顶空间
    return OK;
}

//若栈不空，则删除S的栈顶元素，用e返回其值
Status Pop(SqStack *S, ElemType *e)
{
    if (S->top == -1)
    { //空栈
        return ERROR;
    }
    *e = S->data[S->top]; //用e返回删除值
    S->top--;             //栈顶指针-1
    return OK;
}

//----------------------------
//以下是自己写的
Status InitStack(SqStack *S)
{
    S->top = -1;
    return OK;
}
Status DestroyStack(SqStack *S)
{
    free(S->data);
    return OK;
}
Status ClearStack(SqStack *S)
{
    S->top = -1;
    return OK;
}
Status StackEmpty(SqStack S)
{
    if (S.top == -1)
    {
        return OK;
    }
    return ERROR;
}
Status GetTop(SqStack S, int *e)
{
    if (S.top == -1)
    { //空栈
        return ERROR;
    }
    *e = S.data[S.top];
    return OK;
}
Status StackLength(SqStack S)
{
    return S.top + 1;
}
Status StackTraverse(SqStack S)
{
    if (S.top == -1)
    { //空栈
        return ERROR;
    }
    for (int i = 0; i <= S.top; i++)
    {
        printf("%d\t", S.data[i]);
    }
    printf("\n");
    return OK;
}
void main()
{
    SqStack S;
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
    // if (DestroyStack(&S))
    // {
    //     printf("NULL\n");
    // }
}