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

//二叉树的二叉线索存储结构定义
typedef enum
{
    Link,
    Thread
} PointerTag; // Link=0，表示指向左右孩子指针
              // Thread=1，表示指向前驱或后继的线索
typedef struct BiThrNode
{
    ElemType data;                     //结点数据
    struct BiThrNode *lchild, *rchild; //左右孩子指针
    PointerTag LTag;
    PointerTag RTag; //左右标志
} BiThrNode, *BiThrTree;

void InThreading(BiThrTree p);
Status InOrderTraverse_Thr(BiThrTree T);

void CreateBiThrTree(BiThrTree *T);
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T);

BiThrTree pre; //全局变量，始终指向刚刚访问过的结点
//中序遍历进行中序线索化
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild); //递归左子树线索化
        if (!p->lchild)
        {                     //没有左孩子
            p->LTag = Thread; //前去线索
            p->lchild = pre;  //左孩子指针指向前驱
        }
        if (!pre->rchild)
        {                       //前驱没有右孩子
            pre->RTag = Thread; //后继线索
            pre->rchild = p;    //前驱右孩子指针指向后继（当前结点p）
        }
        pre = p;                //保持pre指向p的前驱
        InThreading(p->rchild); //递归右子树线索化
    }
}

//中序遍历中序线索二叉树（无递归）
Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild; // p指向根结点
    while (p != T)
    { //空树或遍历结束时，p==T
        while (p->LTag == Link)
        { //当LTag==0时循环到中序序列的第一个结点
            p = p->lchild;
        }
        printf("%c", p->data); //显示结点数据，可更改为其他操作
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            printf("%c", p->data);
        }
        p = p->rchild; // p进至其右子树根
    }
    return OK;
}

//----------------------------
//以下是自己写的
int INDEX = 0;
char str[] = "ABDH##I##EJ###CF##G##";
//按前序遍历输入二叉树中结点的值（一个字符）
//#表示空树，构造二叉链表表示二叉树T
void CreateBiThrTree(BiThrTree *T)
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
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if (!*T)
        {
            exit(OVERFLOW); //越界溢出
        }
        (*T)->data = ch;                //生成根结点
        CreateBiThrTree(&(*T)->lchild); //构造左子树
        if ((*T)->lchild)
        { //有左孩子
            (*T)->LTag = Link;
        }
        CreateBiThrTree(&(*T)->rchild); //构造右子树
        if ((*T)->rchild)
        { //有右孩子
            (*T)->RTag = Link;
        }
    }
}

//中序遍历二叉树T,并将其中序线索化,Thrt指向头结点
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    *Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    if (!*Thrt)
    {
        exit(OVERFLOW);
    }
    (*Thrt)->LTag = Link; //建头结点
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = (*Thrt); //右指针回指
    if (!T)
    { //若二叉树空,则左指针回指
        (*Thrt)->lchild = *Thrt;
    }
    else
    {
        (*Thrt)->lchild = T;
        pre = (*Thrt);
        InThreading(T); //中序遍历进行中序线索化
        pre->rchild = *Thrt;
        pre->RTag = Thread; //最后一个结点线索化
        (*Thrt)->rchild = pre;
    }
    return OK;
}

void main()
{
    BiThrTree T;
    BiThrTree Thrt;
    printf("String=%s", str);
    CreateBiThrTree(&T);
    InOrderThreading(&Thrt, T);
    printf("\nPre: ");
    InOrderTraverse_Thr(Thrt);
    printf("\n");
}