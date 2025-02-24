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

//循环队列的顺序存储结构
typedef struct
{
    ElemType data[MAXSIZE];
    int front; //头指针
    int rear;  //尾指针，若队列不空，指向队列尾元素的下一个位置
} SqQueue;

Status InitQueue(SqQueue *Q);
Status QueueLength(SqQueue Q);
Status EnQueue(SqQueue *Q, ElemType e);
Status DeQueue(SqQueue *Q, ElemType *e);


Status QueueEmpty(SqQueue Q);
Status GetHead(SqQueue Q, ElemType *e);
Status ClearQueue(SqQueue *Q);
Status QueueTraverse(SqQueue Q);

//初始化队列
Status InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}
//返回队列元素个数
Status QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}
//若队列未满，则插入元素e为Q新的队尾元素
Status EnQueue(SqQueue *Q, ElemType e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
    { //队列已满
        return ERROR;
    }
    Q->data[Q->rear] = e;              //将元素e赋值给队尾
    Q->rear = (Q->rear + 1) % MAXSIZE; // rear指针向后移一位置，若到最后则转到数组头部
    return OK;
}
//若队列不空，则删除Q中队头元素，用e返回其值
Status DeQueue(SqQueue *Q, ElemType *e)
{
    if (Q->front == Q->rear)
    { //队列已空
        return ERROR;
    }
    *e = Q->data[Q->front];              //将队头元素赋值给e
    Q->front = (Q->front + 1) % MAXSIZE; // front指针向后移一位置，若到最后则转到数组头部
    return OK;
}

//----------------------------
//以下是自己写的
Status QueueEmpty(SqQueue Q)
{
    if (Q.front == Q.rear)
    { //队列已空
        return OK;
    }
    return ERROR;
}
Status GetHead(SqQueue Q, ElemType *e)
{
    if (Q.front == Q.rear)
    { //队列已空
        return ERROR;
    }
    *e = Q.data[Q.front];
    return OK;
}
Status ClearQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}
Status QueueTraverse(SqQueue Q)
{
    int i = Q.front;
    while (i != Q.rear)
    {
        printf("%d\t", Q.data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
    return OK;
}
void main()
{
    SqQueue Q;
    int e;
    InitQueue(&Q);
    for (int i = 0; i < 10; i++)
    {
        EnQueue(&Q, i);
    }
    printf("Length:%d\n", QueueLength(Q));
    QueueTraverse(Q);
    DeQueue(&Q, &e);
    printf("De:%d\n", e);
    QueueTraverse(Q);
    GetHead(Q, &e);
    printf("Head:%d\n", e);
    ClearQueue(&Q);
    if (QueueEmpty(Q))
    {
        printf("Empty\n");
    }
}
