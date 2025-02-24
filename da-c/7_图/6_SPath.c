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

typedef int Patharc[MAXVEX];          //用于存储最短路径下标的数组
typedef int ShortPathTable_D[MAXVEX]; //用于存储到个顶点最短路径的权值和
// Dijkstra算法，求最短路径P[v]及带权长度D[v]
// P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径长度和
void ShortestPath_Dijkstra(MGraph G)
{
    int v, w, k, min;
    int final[MAXVEX]; // final[w]=1表示求得顶点v0至vw的最短路径
    int v0 = 0;
    Patharc P;
    ShortPathTable_D D;
    for (v = 0; v < G.numVertexes; v++)
    {
        final[v] = 0;        //全部顶点初始化为未知最短路径状态
        D[v] = G.arc[v0][v]; //将于v0点有连线的顶点加上权值
        P[v] = 0;            //初始化路径数组P为0
    }
    D[v0] = 0;     // v0至v0路径为0
    final[v0] = 1; // v0至v0不需求路径
    //开始主循环，每次求得v0到某个v顶点的最短路径
    for (v = 1; v < G.numVertexes; v++)
    {
        min = INFINITY_G; //当前所知离v0顶点的最近距离
        for (w = 0; w < G.numVertexes; w++)
        { //寻找离v0最近的顶点
            if (!final[w] && D[w] < min)
            {
                k = w;
                min = D[w]; // w顶点离v0顶点更近
            }
        }
        final[k] = 1; //将目前找的的最近顶点置为1
        for (w = 0; w < G.numVertexes; w++)
        { //修正当前最短路径及距离
            //如果经过v顶点的路径比现在这条路径的长度短的话
            if (!final[w] && (min + G.arc[k][w] < D[w]))
            {                             //说明找到了更短的路径，修正D[w]和P[w]
                D[w] = min + G.arc[k][w]; //修改当前路径长度
                P[w] = k;
            }
        }
    }
    //打印最短路径
    for (v = 1; v < G.numVertexes; v++)
    {
        printf("v%d-v%d\tweight: %d \n%d ", v0, v, D[v], v);

        w = v;
        while (P[w] != 0)
        {
            printf("%d ", P[w]);
            w = P[w];
        }
        printf("0\n");
    }
}

typedef int Pathmatrix[MAXVEX][MAXVEX];
typedef int ShortPathTable_F[MAXVEX][MAXVEX];
// Floyd算法，求各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]
void ShortestPath_Floyd(MGraph G)
{
    int v, w, k;
    Pathmatrix P;
    ShortPathTable_F D;
    for (v = 0; v < G.numVertexes; v++)
    { //初始化D与P
        for (w = 0; w < G.numVertexes; w++)
        {
            D[v][w] = G.arc[v][w]; // D[v][w]值即为对应点间的权值
            P[v][w] = w;           //初始化P
        }
    }
    for (k = 0; k < G.numVertexes; k++)
    {
        for (v = 0; v < G.numVertexes; v++)
        {
            for (w = 0; w < G.numVertexes; w++)
            {
                if (D[v][w] > D[v][k] + D[k][w])
                { //如果经过下标为k顶点路径比原两点间路径更短
                    //将当前顶点权值改为更小的一个
                    D[v][w] = D[v][k] + D[k][w];
                    P[v][w] = P[v][k]; //路径设置经过下标为k的顶点
                }
            }
        }
    }
    //打印最短路径
    for (v = 0; v < G.numVertexes; v++)
    {
        for (w = v + 1; w < G.numVertexes; w++)
        {
            printf("v%d-v%d weight: %d ", v, w, D[v][w]);
            k = P[v][w];           //获得第一个路径顶点下标
            printf("path: %d", v); //打印源点
            while (k != w)
            {                        //如果路径顶点下标不是终点
                printf(" -> %d", k); //打印路径顶点
                k = P[k][w];         //获得下一个路径顶点下标
            }
            printf(" -> %d\n", w); //打印终点
        }
        printf("\n");
    }
}
void main()
{
    MGraph G;
    VertexType ver[] = "ABCDEFGHI";
    Edge edge[] = {{1, 0, 1}, {2, 0, 5}, {2, 1, 3}, {3, 1, 7}, {4, 1, 5}, {4, 2, 1}, {4, 3, 2}, {5, 2, 7}, {5, 4, 3}, {6, 3, 3}, {6, 4, 6}, {7, 4, 9}, {7, 5, 5}, {7, 6, 2}, {8, 6, 7}, {8, 7, 4}};
    int edgelen = sizeof(edge) / sizeof(edge[0]);
    CreateMGraph(&G, ver, edge, edgelen);
    PrintAdjMatrix(G);
    ShortestPath_Dijkstra(G);
    ShortestPath_Floyd(G);
}