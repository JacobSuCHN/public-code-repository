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

//二叉树的二叉链表结点结构定义
//结点结构
typedef struct BiTNode
{
    ElemType data;                   //结点数据
    struct BiTNode *lchild, *rchild; //左右孩子指针
} BiTNode, *BiTree;

void PreOrderTraverse(BiTree T);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);
void CreateBiTree(BiTree *T);

//二叉树的前序遍历递归算法
void PreOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    printf("%c", T->data);       //显示结点数据，可更改为其他操作
    PreOrderTraverse(T->lchild); //再先序遍历左子树
    PreOrderTraverse(T->rchild); //最后先序遍历右子树
}

//二叉树的中序遍历递归算法
void InOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    InOrderTraverse(T->lchild); //中序遍历左子树
    printf("%c", T->data);      //显示结点数据，可更改为其他操作
    InOrderTraverse(T->rchild); //最后中序遍历右子树
}

//二叉树的后序遍历递归算法
void PostOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    PostOrderTraverse(T->lchild); //先后序遍历左子树
    PostOrderTraverse(T->rchild); //再后序遍历右子树
    printf("%c", T->data);        //显示结点数据，可更改为其他操作
}

int INDEX = 0;
char str[] = "ABDH##I##EJ###CF##G##";
//按前序遍历输入二叉树中结点的值（一个字符）
//#表示空树，构造二叉链表表示二叉树T
void CreateBiTree(BiTree *T)
{
    ElemType ch;
    // scanf("%c", &ch);
    ch = str[INDEX++];
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T)
        {
            exit(OVERFLOW); //越界溢出
        }
        (*T)->data = ch;             //生成根结点
        CreateBiTree(&(*T)->lchild); //构造左子树
        CreateBiTree(&(*T)->rchild); //构造右子树
    }
}

void main()
{
    BiTree T;
    CreateBiTree(&T);
    printf("String=%s", str);
    printf("\nPre: ");
    PreOrderTraverse(T);
    printf("\nIn:  ");
    InOrderTraverse(T);
    printf("\nPost:");
    PostOrderTraverse(T);
    printf("\n");
}