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

//结点结构
typedef struct QNode
{
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;
//队列的链表结构
typedef struct
{
    QueuePtr front, rear; //队头队尾指针
} LinkQueue;

Status EnQueue(LinkQueue *Q, ElemType e);
Status DeQueue(LinkQueue *Q, ElemType *e);

Status InitQueue(LinkQueue *Q);
Status QueueLength(LinkQueue Q);
Status QueueEmpty(LinkQueue Q);
Status GetHead(LinkQueue Q, ElemType *e);
Status ClearQueue(LinkQueue *Q);
Status QueueTraverse(LinkQueue Q);

//插入元素e为Q新的队尾元素
Status EnQueue(LinkQueue *Q, ElemType e)
{
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    if (!s)
    { //存储分配失败
        exit(OVERFLOW);
    }
    s->data = e;
    s->next = NULL;
    Q->rear->next = s; //把拥有新元素e的新结点s赋值给原队尾结点的后继
    Q->rear = s;       //把当前的s设置为队尾结点，rear指向s
    return OK;
}
//若队列不空，则删除Q中队头元素，用e返回其值
Status DeQueue(LinkQueue *Q, ElemType *e)
{
    QueuePtr p;
    if (Q->front == Q->rear)
    { //队列已空
        return ERROR;
    }
    p = Q->front->next; //将欲删除的队头结点暂给p
    *e = p->data;
    ;                         //将欲删除的队头结点的值赋值给e
    Q->front->next = p->next; //将原队头结点后继p->next赋值给头结点后继
    if (Q->rear == p)
    { //若队头是队尾，则删除后将rear指向头结点
        Q->rear = Q->front;
    }
    return OK;
}

//----------------------------
//以下是自己写的
Status InitQueue(LinkQueue *Q)
{
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    s->next = NULL;
    Q->front = s;
    Q->rear = Q->front;
    return OK;
}
Status QueueLength(LinkQueue Q)
{
    QueuePtr p;
    int i = 0;
    p = Q.front;
    while (p != Q.rear)
    {
        p = p->next;
        i++;
    }
    return i;
}
Status QueueEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
    { //队列已空
        return OK;
    }
    return ERROR;
}
Status GetHead(LinkQueue Q, ElemType *e)
{
    if (Q.front == Q.rear)
    { //队列已空
        return ERROR;
    }
    *e = Q.front->next->data;
    return OK;
}
Status ClearQueue(LinkQueue *Q)
{
    QueuePtr p, q;
    p = Q->front->next;
    while (p)
    {
        q = p->next; //将p的下一个结点赋给q
        free(p);     //释放当前结点p
        p = q;       //将下一节点q赋值给p
    }
    Q->front->next = NULL;
    Q->rear = Q->front;
    return OK;
}
Status QueueTraverse(LinkQueue Q)
{
    QueuePtr p;
    p = Q.front;
    while (p != Q.rear)
    {
        printf("%d\t", p->next->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

void main()
{
    LinkQueue Q;
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
