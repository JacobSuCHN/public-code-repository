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

//对边集数组Edge结构的定义
typedef struct
{
    int begin;
    int end;
    int weight;
} Edge;
typedef struct
{
    VertexType vexs[MAXVEX];      //顶点表
    EdgeType arc[MAXVEX][MAXVEX]; //邻接矩阵
    int numVertexes, numEdges;    //图中当前顶点数和边数
} MGraph;

void CreateMGraph(MGraph *G, VertexType ver[], Edge edge[], int len);
void PrintAdjMatrix(MGraph G);
void MiniSpanTree_Prim(MGraph G);
void MiniSpanTree_Kruscal(MGraph G);
int Find(int *parent, int f);
void Swapn(Edge *edges, int i, int j);
void Sort(Edge edges[], MGraph *G);

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

// Prim算法生成最小生成树
void MiniSpanTree_Prim(MGraph G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];  //保存相关顶点下标
    int lowcost[MAXVEX]; //保存相关顶点边的权值，=0表示此顶点已加入生成树
    lowcost[0] = 0;      //初始化第一个权值为0，即v0加入生成树
    adjvex[0] = 0;       //初始化第一个顶点下标为0
    for (i = 1; i < G.numVertexes; i++)
    {
        lowcost[i] = G.arc[0][i]; //将v0顶点与之有边的权值存入数组
        adjvex[i] = 0;            //初始化都为v0的下标
    }
    for (i = 1; i < G.numVertexes; i++)
    {
        min = INFINITY_G; //初始化最小权值为无穷，通常设置为不可能的数字
        j = 1;
        k = 0;
        while (j < G.numVertexes)
        { //循环全部顶点
            if (lowcost[j] != 0 && lowcost[j] < min)
            {                     //如果权值部位0且权值小于min
                min = lowcost[j]; //则让当前权值成为最小值
                k = j;            //将当前最小值小标存入k
            }
            j++;
        }
        printf("(%d,%d)", adjvex[k], k); //打印当前顶点边中权值最小边
        lowcost[k] = 0;                  //将当前顶点的权值设置为0，表示此顶点已经完成任务
        for (j = 1; j < G.numVertexes; j++)
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {                             //若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
                lowcost[j] = G.arc[k][j]; //将较小权值存入lowcost
                adjvex[j] = k;            //将下标为k的顶点存入adjvex
            }
        }
    }
    printf("\n");
}

// Kruscal算法生成最小生成树
void MiniSpanTree_Kruscal(MGraph G)
{
    int i, j, k, n, m;
    Edge edges[MAXVEX]; //定义边集数组
    int parent[MAXVEX]; //定义一数组用来判断边是否形成回路
    k=0;
    //构建边集数组
    for (i = 0; i < G.numVertexes - 1; i++)
    {
        for (j = i + 1; j < G.numVertexes; j++)
        {
            if (G.arc[i][j] < INFINITY_G)
            {
                edges[k].begin = i;
                edges[k].end = j;
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }
    Sort(edges, &G); //边集数组排序
    for (i = 0; i < G.numVertexes; i++)
    {
        parent[i] = 0; //初始化数组值为0
    }
    for (i = 0; i < G.numEdges; i++)
    { //循环每一条边
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        if (n != m)
        {                  //假如n与m不等，说明此边没有与现有生成树形成回路
            parent[n] = m; //将此边的结尾顶点放入下标为起点的parent中
                           //表示此顶点已经在生成树集合中
            printf("(%d,%d) %d ", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
    printf("\n");
}
//查找连线顶点的尾部下标
int Find(int *parent, int f)
{
    while (parent[f] > 0)
    {
        f = parent[f];
    }
    return f;
}
//交换边集数组的项
void Swapn(Edge *edges, int i, int j)
{
    int temp;
    temp = edges[i].begin;
    edges[i].begin = edges[j].begin;
    edges[j].begin = temp;
    temp = edges[i].end;
    edges[i].end = edges[j].end;
    edges[j].end = temp;
    temp = edges[i].weight;
    edges[i].weight = edges[j].weight;
    edges[j].weight = temp;
}
//对权值进行排序
void Sort(Edge edges[], MGraph *G)
{
    int i, j;
    for (i = 0; i < G->numEdges; i++)
    {
        for (j = i + 1; j < G->numEdges; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                Swapn(edges, i, j);
            }
        }
    }
}
void main()
{
    MGraph G;
    VertexType ver[] = "ABCDEFGHI";
    Edge edge[] = {{1, 0, 10}, {2, 1, 18}, {3, 2, 22}, {4, 3, 20}, {5, 0, 11}, {5, 4, 26}, {6, 1, 16}, {6, 3, 24}, {6, 5, 17}, {7, 3, 16}, {7, 4, 7}, {7, 6, 19}, {8, 1, 12}, {8, 2, 8}, {8, 3, 21}};
    int edgelen = sizeof(edge) / sizeof(edge[0]);
    CreateMGraph(&G, ver, edge, edgelen);
    PrintAdjMatrix(G);
    MiniSpanTree_Prim(G);
    MiniSpanTree_Kruscal(G);
}