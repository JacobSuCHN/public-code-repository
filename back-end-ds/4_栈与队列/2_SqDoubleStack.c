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
    int top1; //栈1栈顶指针
    int top2; //栈2栈顶指针
} SqDoubleStack;

Status Push(SqDoubleStack *S, ElemType e, int stackNumber);
Status Pop(SqDoubleStack *S, ElemType *e, int stackNumber);

Status InitStack(SqDoubleStack *S);
Status DestroyStack(SqDoubleStack *S);
Status ClearStack(SqDoubleStack *S, int stackNumber);
Status StackEmpty(SqDoubleStack S, int stackNumber);
Status GetTop(SqDoubleStack S, int *e, int stackNumber);
Status StackLength(SqDoubleStack S, int stackNumber);
Status StackTraverse(SqDoubleStack S, int stackNumber);

//插入元素e为新的栈顶元素
Status Push(SqDoubleStack *S, ElemType e, int stackNumber)
{
    if (S->top1 + 1 == S->top2)
    { //栈满
        return ERROR;
    }
    if (stackNumber == 1)
    {                           //栈1有元素进栈
        S->data[++S->top1] = e; //若栈1则先top1+1后给数组元素赋值
    }
    if (stackNumber == 2)
    {                           //栈1有元素进栈
        S->data[--S->top2] = e; //若栈2则先top2-1后给数组元素赋值
    }
    return OK;
}
//若栈不空，则删除S的栈顶元素，用e返回其值
Status Pop(SqDoubleStack *S, ElemType *e, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (S->top1 == -1)
        { //栈1已空
            return ERROR;
        }
        *e = S->data[S->top1];
        S->top1--; //将栈1的栈顶元素出战
    }
    else if (stackNumber == 2)
    {
        if (S->top2 == MAXSIZE)
        { //栈2已空
            return ERROR;
        }
        *e = S->data[S->top2];
        S->top2++; //将栈1的栈顶元素出战
    }
}

//----------------------------
//以下是自己写的
Status InitStack(SqDoubleStack *S)
{
    S->top1 = -1;
    S->top2 = MAXSIZE;
    return OK;
}
Status DestroyStack(SqDoubleStack *S)
{
    free(S->data);
    return OK;
}
Status ClearStack(SqDoubleStack *S, int stackNumber)
{
    if (stackNumber == 1)
    {
        S->top1 = -1;
    }
    else if (stackNumber == 2)
    {
        S->top2 = MAXSIZE;
    }
    return OK;
}
Status StackEmpty(SqDoubleStack S, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (S.top1 == -1)
        {
            return OK;
        }
    }
    else if (stackNumber == 2)
    {
        if (S.top2 == MAXSIZE)
        {
            return OK;
        }
    }

    return ERROR;
}
Status GetTop(SqDoubleStack S, int *e, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (S.top1 == -1)
        { //栈1已空
            return ERROR;
        }
        *e = S.data[S.top1];
    }
    else if (stackNumber == 2)
    {
        if (S.top2 == MAXSIZE)
        { //栈2已空
            return ERROR;
        }
        *e = S.data[S.top2];
    }
    return OK;
}
Status StackLength(SqDoubleStack S, int stackNumber)
{
    if (stackNumber == 1)
    {
        return S.top1 + 1;
    }
    else if (stackNumber == 2)
    {
        return MAXSIZE - S.top2;
    }
}
Status StackTraverse(SqDoubleStack S, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (S.top1 == -1)
        { //栈1已空
            return ERROR;
        }
        printf("Stack1:");
        for (int i = 0; i <= S.top1; i++)
        {
            printf("%d\t", S.data[i]);
        }
        printf("\n");
    }
    else if (stackNumber == 2)
    {
        if (S.top2 == MAXSIZE)
        { //栈2已空
            return ERROR;
        }
        printf("Stack2:");

        for (int i = MAXSIZE - 1; i >= S.top2; i--)
        {
            printf("%d\t", S.data[i]);
        }
        printf("\n");
    }

    return OK;
}
void main()
{
    SqDoubleStack S;
    int e;
    InitStack(&S);
    for (int i = 0; i < 10; i++)
    {
        Push(&S, i, 1);
    }
    for (int i = 9; i > 4; i--)
    {
        Push(&S, i, 2);
    }
    printf("Length1:%d\n", StackLength(S, 1));
    StackTraverse(S, 1);
    printf("Length2:%d\n", StackLength(S, 2));
    StackTraverse(S, 2);
    Pop(&S, &e, 1);
    printf("Pop1:%d\n", e);
    StackTraverse(S, 1);
    Pop(&S, &e, 2);
    printf("Pop2:%d\n", e);
    StackTraverse(S, 2);
    GetTop(S, &e, 1);
    printf("Top1:%d\n", e);
    GetTop(S, &e, 2);
    printf("Top2:%d\n", e);
    ClearStack(&S, 1);
    if (StackEmpty(S, 1))
    {
        printf("Empty1\n");
    }
    ClearStack(&S, 2);
    if (StackEmpty(S, 2))
    {
        printf("Empty2\n");
    }
    // if (DestroyStack(&S))
    // {
    //     printf("NULL\n");
    // }
}