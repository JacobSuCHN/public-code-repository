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

typedef int Status; // Status是函数的类型，其值是函数的状态代码，如OK等

typedef char VertexType; //顶点类型
typedef int EdgeType;    //边上权值类型
#define MAXVEX 100       //最大顶点数
#define INFINITY_G 65535 //用65535表示无穷

typedef struct Edges
{
    int begin, end;
    int weight;
} Edge;
typedef struct
{
    VertexType vexs[MAXVEX];      //顶点表
    EdgeType arc[MAXVEX][MAXVEX]; //邻接矩阵
    int numVertexes, numEdges;    //图中当前顶点数和边数
} MGraph;

//建立无向图的邻接矩阵表示
void CreateMGraph(MGraph *G, VertexType ver[], Edge edge[], int len)
{
    int i, j, k, w;
    // printf("输入顶点数和边数:\n");
    // scanf("%d,%d", &G->numVertexes, G->numEdges); //输入顶点数和边数
    G->numVertexes = strlen(ver);
    G->numEdges = len;
    for (i = 0; i < G->numVertexes; i++)
    { //读入顶点信息，建立顶点表
        // scanf(&G->vexs);
        G->vexs[i] = ver[i];
    }
    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = INFINITY_G; //邻接矩阵初始化
        }
    }
    for (k = 0; k < G->numEdges; k++)
    { //读入numEdges条边，建立邻接矩阵
        // printf("输入边(vi,vj)上的下标i，下标j和权w:\n");
        // scanf("%d,%d,%d", &i, &j, &w); //输入边(vi,vj)和边上的权
        i = edge[k].begin;
        j = edge[k].end;
        w = edge[k].weight;
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j]; //无向图，矩阵对称
    }
}
void PrintAdjMatrix(MGraph G)
{

    int i, j;
    printf("\t");
    for (i = 0; i < G.numVertexes; i++)
    {
        printf("%d%c\t", i, G.vexs[i]);
    }
    printf("\n");
    for (i = 0; i < G.numVertexes; i++)
    {
        printf("%d%c\t", i, G.vexs[i]);
        for (j = 0; j < G.numVertexes; j++)
        {

            if (G.arc[i][j] != INFINITY_G)
            {
                printf("%d\t", G.arc[i][j]);
            }
            else
            {
                printf("N\t");
            }
        }
        printf("\n");
    }
}
//边表结点
typedef struct EdgeNode
{
    int adjvex;            //邻接点域，存储该顶点对应的下标
    EdgeType weight;       //用于存储权值
    struct EdgeNode *next; //链域，指向下一个邻接点
} EdgeNode;
//顶点表结点
typedef struct VertexNode
{
    VertexType data;     //顶点域，存储顶点信息
    EdgeNode *firstedge; //边表头指针
} VertexNode, AdjList[MAXVEX];
//邻接表
typedef struct
{
    AdjList adjlist;
    int numVertexes, numEdges; //图中当前顶点数和边数
} GraphAdjList;

//建立图的邻接表结构
void CreateALGraph(GraphAdjList *G, VertexType ver[], Edge edge[], int len)
{
    int i, j, k;
    EdgeNode *e;
    // printf("输入顶点数和边数:\n");
    // scanf("%d,%d", &G->numVertexes, &G->numEdges); //输入顶点数和边数
    G->numVertexes = strlen(ver);
    G->numEdges = len;
    for (i = 0; i < G->numVertexes; i++)
    {
        // scanf(&G->adjlist[i].data);     //输入顶点信息
        G->adjlist[i].data = ver[i];
        G->adjlist[i].firstedge = NULL; //将边表置空
    }
    for (k = 0; k < G->numEdges; k++)
    { //建立边表
        // printf("输入边(vi,vj)的顶点序号:\n");
        // scanf("%d,%d", &i, &j);                   //输入边(vi,vj)的顶点序号
        i = edge[k].begin;
        j = edge[k].end;
        e = (EdgeNode *)malloc(sizeof(EdgeNode)); //生成边表结点
        e->adjvex = j;                            //邻接序号为j
        e->weight = edge[k].weight;
        e->next = G->adjlist[i].firstedge; //将e指针指向当前顶点指向的结点
        G->adjlist[i].firstedge = e;       //将当前顶点的指针指向e

        e = (EdgeNode *)malloc(sizeof(EdgeNode)); //生成边表结点
        e->adjvex = i;                            //邻接序号为i
        e->weight = edge[k].weight;
        e->next = G->adjlist[j].firstedge; //将e指针指向当前顶点指向的结点
        G->adjlist[j].firstedge = e;       //将当前顶点的指针指向e
    }
}
void PrintAdjList(GraphAdjList G)
{

    int i, j;
    EdgeNode *e;
    for (i = 0; i < G.numVertexes; i++)
    {
        printf("%2d%c:", i, G.adjlist[i].data);
        e = G.adjlist[i].firstedge;
        while (e)
        {
            printf(" %d%c|%2d ->", e->adjvex, G.adjlist[e->adjvex].data, e->weight);
            e = e->next;
        }
        printf(" NULL\n");
    }
}
typedef int Boolean;
Boolean visited_MG[MAXVEX];  //访问标志的数组
Boolean visited_ALG[MAXVEX]; //访问标志的数组
//邻接矩阵的深度优先递归算法
void DFS_MG(MGraph G, int i)
{
    int j;
    visited_MG[i] = TRUE;
    printf("%c ", G.vexs[i]); //打印顶点，可改为其他操作
    for (j = 0; j < G.numVertexes; j++)
    {
        if (G.arc[i][j] == 1 && !visited_MG[j])
        {
            DFS_MG(G, j); //对未访问的邻接顶点递归调用
        }
    }
}
//邻接矩阵的深度遍历操作
void DFSTraverse_MG(MGraph G)
{
    int i;
    for (i = 0; i < G.numVertexes; i++)
    {
        visited_MG[i] = FALSE; //初始化所有顶点状态都是未访问过状态
    }
    for (i = 0; i < G.numVertexes; i++)
    {
        if (!visited_MG[i])
        { //对未访问过的顶点调用DFS，若是连通图只会执行一次
            DFS_MG(G, i);
        }
    }
    printf("\n");
}
//邻接表的深度优先递归算法
void DFS_ALG(GraphAdjList GL, int i)
{
    EdgeNode *p;
    visited_ALG[i] = TRUE;
    printf("%c ", GL.adjlist[i].data); //打印顶点，可改为其他操作
    p = GL.adjlist[i].firstedge;
    while (p)
    {
        if (!visited_ALG[p->adjvex])
        {
            DFS_ALG(GL, p->adjvex); //对未访问的邻接顶点递归调用
        }
        p = p->next;
    }
}
//邻接表深度优先遍历操作
void DFSTraverse_ALG(GraphAdjList GL)
{
    int i;
    for (int i = 0; i < GL.numVertexes; i++)
    {
        visited_ALG[i] = FALSE; //初始化所有顶点状态都是未访问过状态
    }
    for (i = 0; i < GL.numVertexes; i++)
    {
        if (!visited_ALG[i])
        { //对未访问过的顶点调用DFS，若是连通图只会执行一次
            DFS_ALG(GL, i);
        }
    }
    printf("\n");
}

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
} Queue;

Status EnQueue(Queue *Q, ElemType e);
Status DeQueue(Queue *Q, ElemType *e);

Status InitQueue(Queue *Q);
Status QueueEmpty(Queue Q);

//插入元素e为Q新的队尾元素
Status EnQueue(Queue *Q, ElemType e)
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
Status DeQueue(Queue *Q, ElemType *e)
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

Status InitQueue(Queue *Q)
{
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    s->next = NULL;
    Q->front = s;
    Q->rear = Q->front;
    return OK;
}
Status QueueEmpty(Queue Q)
{
    if (Q.front == Q.rear)
    { //队列已空
        return OK;
    }
    return ERROR;
}
//邻接矩阵的广度优先遍历算法
void BFSTraverse_MG(MGraph G)
{
    int i, j;
    Queue Q;
    for (i = 0; i < G.numVertexes; i++)
    {
        visited_MG[i] = FALSE;
    }
    InitQueue(&Q); //初始化一辅助队列
    for (i = 0; i < G.numVertexes; i++)
    { //对每一个顶点做循环
        if (!visited_MG[i])
        {                             //若是未访问就处理
            visited_MG[i] = TRUE;     //设置当前顶点访问过
            printf("%c ", G.vexs[i]); //打印顶点，可改为其他操作
            EnQueue(&Q, i);           //将此顶点入队
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q, &i); //将队中元素出队，赋值给i
                for (j = 0; j < G.numVertexes; j++)
                {
                    //判断其他顶点若与当前顶点存在边且未被访问过
                    if (G.arc[i][j] == 1 && !visited_MG[j])
                    {
                        visited_MG[j] = TRUE;     //设置此顶点访问过
                        printf("%c ", G.vexs[j]); //打印顶点，可改为其他操作
                        EnQueue(&Q, j);           //将找到的此顶点入队
                    }
                }
            }
        }
    }
    printf("\n");
}
//邻接表的广度优先遍历算法
void BFSTraverse_ALG(GraphAdjList GL)
{
    int i;
    EdgeNode *p;
    Queue Q;
    for (i = 0; i < GL.numVertexes; i++)
    {
        visited_ALG[i] = FALSE;
    }
    InitQueue(&Q); //初始化一辅助队列
    for (i = 0; i < GL.numVertexes; i++)
    { //对每一个顶点做循环
        if (!visited_ALG[i])
        {                                      //若是未访问就处理
            visited_ALG[i] = TRUE;             //设置当前顶点访问过
            printf("%c ", GL.adjlist[i].data); //打印顶点，可改为其他操作
            EnQueue(&Q, i);                    //将此顶点入队
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q, &i);             //将队中元素出队，赋值给i
                p = GL.adjlist[i].firstedge; //找到当前顶点边表头指针
                while (p)
                {
                    //若当前顶点未被访问
                    if (!visited_ALG[p->adjvex])
                    {
                        visited_ALG[p->adjvex] = TRUE;             //设置此顶点访问过
                        printf("%c ", GL.adjlist[p->adjvex].data); //打印顶点，可改为其他操作
                        EnQueue(&Q, p->adjvex);                    //将找到的此顶点入队
                    }
                    p = p->next; //指针指向下一个邻接点
                }
            }
        }
    }
    printf("\n");
}
void main()
{
    MGraph G;
    GraphAdjList GL;
    VertexType ver[] = "ABCDEFGHI";
    Edge edge[] = {{1, 0, 1}, {2, 1, 1}, {3, 2, 1}, {4, 3, 1}, {5, 0, 1}, {5, 4, 1}, {6, 1, 1}, {6, 3, 1}, {6, 5, 1}, {7, 3, 1}, {7, 4, 1}, {7, 6, 1}, {8, 1, 1}, {8, 2, 1}, {8, 3, 1}};
    int edgelen = sizeof(edge) / sizeof(edge[0]);
    CreateMGraph(&G, ver, edge, edgelen);
    PrintAdjMatrix(G);
    DFSTraverse_MG(G);
    BFSTraverse_MG(G);
    CreateALGraph(&GL, ver, edge, edgelen);
    PrintAdjList(GL);
    DFSTraverse_ALG(GL);
    BFSTraverse_ALG(GL);
}