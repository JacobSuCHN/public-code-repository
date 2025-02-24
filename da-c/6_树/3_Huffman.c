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

typedef int Status;    // Status是函数的类型，其值是函数的状态代码，如OK等
typedef char ElemType; // ElemType类型根据实际情况而定，这里假设为int

//哈夫曼树的存储表示
typedef struct
{
    ElemType data;              //结点数据
    int weight;                 //结点的权值
    int parent, lchild, rchild; //结点的双亲、左孩子、右孩子
} HTNode, *HuffmanTree;         //动态分配数组存储哈夫曼树
//找权值最小的两个结点
void Select(HuffmanTree HT, int n, int *s1, int *s2)
{
    int i;
    int min = 100;
    int lable1 = 0, lable2 = 0;
    for (i = 1; i <= n; i++)
    {
        //双亲域为0且权值小于min
        if (HT[i].parent == 0 && HT[i].weight < min)
        {
            min = HT[i].weight;
            lable1 = i;
        }
    }
    *s1 = lable1;
    min = 100;
    for (i = 1; i <= n; i++)
    {
        //双亲域为0且权值小于min，且i不是lable1
        if (HT[i].parent == 0 && HT[i].weight < min && lable1 != i)
        {
            min = HT[i].weight;
            lable2 = i;
        }
    }
    *s2 = lable2;
}

//构造哈夫曼树
void CreatHuffmanTree(HuffmanTree HT, int n)
{
    int i, m, s1, s2;
    if (n <= 1)
    {
        return;
    }
    m = 2 * n - 1;
    // HT = (HTNode *)malloc(2*n*sizeof(HTNode));
    for (i = 1; i <= m; i++)
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for (i = 1; i <= n; i++)
    {
        printf("Node%d:\n", i);
        printf("Node data:");
        fflush(stdin);
        scanf("%c", &HT[i].data);
        fflush(stdin);
        printf("Node weight:");
        scanf("%d", &HT[i].weight);
    }
    //通过n-1次的选择、删除、合并来创建哈夫曼树
    for (i = n + 1; i <= m; i++)
    {
        Select(HT, i - 1, &s1, &s2); //在HT[k]中选择两个其双亲域为0且权值最小的结点
                                     //并返回它们在HT中的序号s1、s2
        HT[s1].parent = i;
        HT[s2].parent = i; //得到新结点i，从森林中删除s1、s2，将s1和s2的双亲域由0改为i
        HT[i].lchild = s1;
        HT[i].rchild = s2;                            // s1、s2分别作为i的左右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight; // i的权值为左右孩子的权值之和
    }
}
void CreatHuffmanCode(HuffmanTree HT, int n)
{
    char cd[n + 1][n + 1];
    int i, j, c, p;
    int start;

    printf("Node\tHuffmanCode\n");
    for (i = 1; i <= n; i++)
    {
        cd[i][n - 1] = '\0'; //从右向左存放编码
        start = n - 1;       //开始时指向最后，即编码结束符位置
        c = i;
        p = HT[i].parent; // p指向结点c的双亲
        //从叶子结点开始向上回溯，直到根节点
        while (p != 0)
        {
            --start; //回溯一次，start湘黔之一个位置
            //结点c是p的左孩子，则生成代码0
            if (HT[p].lchild == c)
                cd[i][start] = '0';
            //结点c是p的右孩子，则生成代码1
            else
                cd[i][start] = '1';
            c = p;
            p = HT[p].parent; //继续向上回溯
        }
        //输出编码
        printf("%c\t", HT[i].data);
        for (j = start; cd[i][j] != '\0'; j++)
        {
            printf("%c", cd[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int n, i;
    HuffmanTree HT;

    printf("\tPlease enter the correct value.\n");
    printf("----------Huffman----------\n");
    printf("Enter number of nodes:");
    scanf("%d", &n);
    CreatHuffmanTree(HT, n);
    printf("node\tweight\tparent\tlchild\trchild\n");
    for (i = 1; i <= 2 * n - 1; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
    }
    CreatHuffmanCode(HT, n);
    printf("---------------------------\n");
    return 0;
}
