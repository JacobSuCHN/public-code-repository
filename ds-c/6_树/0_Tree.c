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

//树的双亲表示法结点结构定义
//结点结构
typedef struct PTNode
{
    ElemType data; //结点数据
    int parent;    //双亲位置
} PTNode;
//树结构
typedef struct
{
    PTNode nodes[MAXSIZE]; //结点数组
    int r, n;              //根的位置和结点数
} PTree;
//树的孩子表示法结点结构定义
//孩子结点
typedef struct CTNode
{
    int child;
    struct CTNode *next;
} * ChildPtr;
//表头结构
typedef struct
{
    ElemType data;
    ChildPtr firstchild;
} CTBox;
//树结构
typedef struct
{
    CTBox nodes[MAXSIZE]; //结点数组
    int r, n;             //根的位置和结点数
} CTree;
//树的孩子兄弟表示法结点结构定义
typedef struct CSNode
{
    ElemType data;
    struct CSNode *firstchild, *rightsib;
} CSNode, *CSTree;
