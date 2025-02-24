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

typedef struct Notation
{
    char elem[MAXSIZE];
} Notation;

typedef int Status;        // Status是函数的类型，其值是函数的状态代码，如OK等
typedef Notation ElemType; // ElemType类型根据实际情况而定，这里假设为int

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
Status StackLength(LinkStack S);
Status StackTraverse(LinkStack S);

Status InitStack(LinkStack *S)
{
    S->count = 0;
    return OK;
}

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
Status StackEmpty(LinkStack S)
{
    if (S.count == 0)
    {
        return OK;
    }
    return ERROR;
}
Status StackLength(LinkStack S)
{
    return S.count;
}
Status StackTraverse(LinkStack S)
{
    LinkStackPtr p;
    p = S.top;
    printf("Stack:");
    for (int i = 0; i < S.count; i++)
    {
        printf("%s\t", p->data.elem);
        p = p->next;
    }
    printf("\n");
    return OK;
}

Status CalculateRPN(Notation RPN[], int length)
{
    LinkStack S;
    InitStack(&S);
    Notation left, right, result;

    for (int i = 0; i < length; i++)
    {
        if (strcmp(RPN[i].elem, "+") == 0 || strcmp(RPN[i].elem, "-") == 0 || strcmp(RPN[i].elem, "*") == 0 || strcmp(RPN[i].elem, "/") == 0)
        {
            Pop(&S, &right);
            Pop(&S, &left);
            if (strcmp(RPN[i].elem, "+") == 0)
            {
                itoa(atoi(left.elem) + atoi(right.elem), result.elem, 10);
            }
            else if (strcmp(RPN[i].elem, "-") == 0)
            {
                itoa(atoi(left.elem) - atoi(right.elem), result.elem, 10);
            }
            else if (strcmp(RPN[i].elem, "*") == 0)
            {
                itoa(atoi(left.elem) * atoi(right.elem), result.elem, 10);
            }
            else if (strcmp(RPN[i].elem, "/") == 0)
            {
                itoa(atoi(left.elem) / atoi(right.elem), result.elem, 10);
            }
            Push(&S, result);
        }
        else
        {
            Push(&S, RPN[i]);
        }
    }
    Pop(&S, &result);
    printf("%d", atoi(result.elem));
}
Status DALtoRPN(Notation DAL[], Notation RPN[], int *length)
{
    LinkStack S;
    InitStack(&S);
    Notation output;
    int priority[MAXSIZE];
    int j = 0;
    int k = 0;

    for (int i = 0; i < *length; i++)
    {
        if (strcmp(DAL[i].elem, "+") == 0 || strcmp(DAL[i].elem, "-") == 0 || strcmp(DAL[i].elem, "*") == 0 || strcmp(DAL[i].elem, "/") == 0)
        {

            if (strcmp(DAL[i].elem, "+") == 0 || strcmp(DAL[i].elem, "-") == 0)
            {
                priority[j] = 1;
            }
            else if (strcmp(DAL[i].elem, "*") == 0 || strcmp(DAL[i].elem, "/") == 0)
            {
                priority[j] = 2;
            }
            j++;
            while (priority[j - 1] <= priority[j - 2])
            {
                priority[j - 2] = priority[j - 1];
                priority[j - 1] = -1;
                Pop(&S, &output);
                j--;
                RPN[k] = output;
                k++;
            }
            Push(&S, DAL[i]);
        }
        else if (strcmp(DAL[i].elem, "(") == 0)
        {
            Push(&S, DAL[i]);
            priority[j] = 0;
            j++;
        }
        else if (strcmp(DAL[i].elem, ")") == 0)
        {
            while (priority[j - 1] > 0)
            {
                priority[j - 1] = -1;
                Pop(&S, &output);
                j--;
                RPN[k] = output;
                k++;
            }
            Pop(&S, &output);
            j--;
        }
        else
        {
            RPN[k] = DAL[i];
            k++;
        }
    }
    while (!StackEmpty(S))
    {
        Pop(&S, &output);
        RPN[k] = output;
        k++;
    }
    *length = k;
}
void main()
{
    // Notation rpn[] = {"100", "300", "+", "10", "20", "+", "2", "/", "-", "15", "+"};
    Notation rpn[MAXSIZE];
    Notation dal[] = {"100", "+", "300", "-", "(", "10", "+", "20", ")", "/", "2", "+", "15"};
    int length = sizeof(dal) / sizeof(dal[0]);
    DALtoRPN(dal, rpn, &length);
    CalculateRPN(rpn, length);
}