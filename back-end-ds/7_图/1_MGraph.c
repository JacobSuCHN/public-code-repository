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
#define INFINITY_G 65535   //用65535表示无穷

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
void main()
{
    MGraph G;
    VertexType ver[] = "ABCD";
    Edge edge[] = {{1, 0, 1}, {2, 0, 1}, {2, 1, 1}, {3, 0, 1}, {3, 2, 1}};
    int edgelen = sizeof(edge) / sizeof(edge[0]);
    CreateMGraph(&G, ver, edge, edgelen);
    PrintAdjMatrix(G);
}