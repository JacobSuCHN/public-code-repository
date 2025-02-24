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
    int in;              //顶点入度
    VertexType data;     //顶点域，存储顶点信息
    EdgeNode *firstedge; //边表头指针
} VertexNode, AdjList[MAXVEX];
//邻接表
typedef struct
{
    AdjList adjlist;
    int numVertexes, numEdges; //图中当前顶点数和边数
} graphAdjList, *GraphAdjList;

//建立图的邻接表结构
void CreateALGraph(GraphAdjList G, VertexType ver[], Edge edge[], int len)
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
        G->adjlist[i].in = 0;
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
        G->adjlist[j].in++;
    }
}

void PrintAdjList(GraphAdjList G)
{

    int i, j;
    EdgeNode *e;
    for (i = 0; i < G->numVertexes; i++)
    {
        printf("%2d%c|in=%2d:", i, G->adjlist[i].data, G->adjlist[i].in);
        e = G->adjlist[i].firstedge;
        while (e)
        {
            printf(" %d%c|%2d ->", e->adjvex, G->adjlist[e->adjvex].data, e->weight);
            e = e->next;
        }
        printf(" NULL\n");
    }
}

int *etv, *ltv; //事件最早发生时间和最迟发生时间数组
int *stack2;    //用于存储拓扑序列的栈
int top2;       //用于stack2的指针
//拓扑排序，若GL无回路，则输出拓扑排序序列
Status TopologicalSort(GraphAdjList GL)
{
    EdgeNode *e;
    int i, k, gettop;
    int top1 = 0;  //用于栈指针下标
    int count = 0; //用于统计输出的顶点个数
    int *stack1;   //建栈存储入度为0的顶点
    stack1 = (int *)malloc(GL->numVertexes * sizeof(int));
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (GL->adjlist[i].in == 0)
        {
            stack1[++top1] = i; //将入度为0的顶点入栈
        }
    }
    top2 = 0;                                           //初始化为0
    etv = (int *)malloc(GL->numVertexes * sizeof(int)); //事件最早发生时间
    for (i = 0; i < GL->numVertexes; i++)
    {
        etv[i] = 0; //初始化为0
    }
    stack2 = (int *)malloc(GL->numVertexes * sizeof(int)); //初始化

    while (top1 != 0)
    {
        gettop = stack1[top1--]; //出栈
        count++;                 //统计输出顶点数
        stack2[++top2] = gettop; //将弹出的顶点序号压入拓扑序列的栈
        for (e = GL->adjlist[gettop].firstedge; e; e = e->next)
        { //对此顶点弧表遍历
            k = e->adjvex;
            if (!(--GL->adjlist[k].in))
            {                       //将k号顶点邻接点的入度减1
                stack1[++top1] = k; //若为0则入栈，以便于下次循环输出
            }

            if ((etv[gettop] + e->weight) > etv[k])
            { //求各顶点事件最早发生时间值
                etv[k] = etv[gettop] + e->weight;
            }
        }
    }
    if (count < GL->numVertexes)
    { //如果count小于顶点数，说明存在回路
        return ERROR;
    }
    else
    {
        return OK;
    }
}
//求关键路径，GL为有向网，输出GL的各项关键活动
void CriticalPath(GraphAdjList GL)
{
    EdgeNode *e;
    int i, gettop, k, j;
    int ete, lte;                                       //声明活动最早发生时间和最迟发生时间变量
    TopologicalSort(GL);                                //求拓扑序列，计算数组etv和stack2的值
    ltv = (int *)malloc(GL->numVertexes * sizeof(int)); //事件最晚发生时间
    for (i = 0; i < GL->numVertexes; i++)
    {
        ltv[i] = etv[GL->numVertexes - 1]; //初始化ltv
    }
    while (top2 != 0)
    {                            //计算ltv
        gettop = stack2[top2--]; //将拓扑序列出栈，后进先出
        for (e = GL->adjlist[gettop].firstedge; e; e = e->next)
        { //求各顶点事件的最迟发生时间ltv值
            k = e->adjvex;
            if (ltv[k] - e->weight < ltv[gettop])
            { //求个顶点时间最晚发生时间
                ltv[gettop] = ltv[k] - e->weight;
            }
        }
    }
    for (j = 0; j < GL->numVertexes; j++)
    { //求ete，lte和关键活动
        for (e = GL->adjlist[j].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            ete = etv[j];             //活动最早发生时间
            lte = ltv[k] - e->weight; //活动最迟发生时间
            if (ete == lte)
            { //两者相等即在关键路径上
                printf("<v%d%c,v%d%c> length: %d\n",
                       j, GL->adjlist[j].data, k, GL->adjlist[k].data, e->weight);
            }
        }
    }
}

void main()
{
    GraphAdjList G;
    VertexType ver[] = "ABCDEFGHIJ";
    Edge edge[] = {{0, 1, 3}, {0, 2, 4}, {1, 3, 5}, {1, 4, 6}, {2, 3, 8}, {2, 5, 7}, {3, 4, 3}, {4, 6, 9}, {4, 7, 4}, {5, 7, 6}, {6, 9, 2}, {7, 8, 5}, {8, 9, 3}};
    int edgelen = sizeof(edge) / sizeof(edge[0]);
    CreateALGraph(G, ver, edge, edgelen);
    PrintAdjList(G);
    CriticalPath(G);
}