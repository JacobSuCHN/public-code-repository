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

//二叉树的二叉链表结点结构定义
typedef struct BiTNode
{
    ElemType data;                   //结点数据
    int bf;                          //结点的平衡因子
    struct BiTNode *lchild, *rchild; //左右孩子指针
} BiTNode, *BiTree;

//对以P为根的二叉排序树作右旋处理
void R_Rotate(BiTree *P)
{
    BiTree L;
    L = (*P)->lchild;         // L指向P的左子树根结点
    (*P)->lchild = L->rchild; // L的右子树挂接为P的左子树
    L->rchild = (*P);         // P挂接为L的右子树
    *P = L;                   // P指向新的根结点
}
//对以P为根的二叉排序树作左旋处理
void L_Rotate(BiTree *P)
{
    BiTree R;
    R = (*P)->rchild;         // R指向P的右子树根结点
    (*P)->rchild = R->lchild; // R的左子树挂接为P的右子树
    R->lchild = (*P);         // P挂接为R的左子树
    *P = R;                   // P指向新的根结点
}
#define LH 1  //左高
#define EH 0  //等高
#define RH -1 //右高
//对以指针T所指结点为根的二叉树作左平衡处理
void LeftBalance(BiTree *T)
{
    BiTree L, Lr;
    L = (*T)->lchild; // L指向T的左子树根结点
    switch (L->bf)
    {        //检查T的左子树的平衡度，并作相应的平衡处理
    case LH: //新结点插入在T的左孩子的左子树上，要作单右旋处理
        (*T)->bf = L->bf = EH;
        R_Rotate(T);
        break;
    case RH:            //新结点插入在T的左孩子的右子树上，要作双旋处理
        Lr = L->rchild; // Lr指向T的左孩子的右子树根上
        switch (Lr->bf)
        { //修改T及其左孩子的平衡因子
        case LH:
            (*T)->bf = RH;
            L->bf = EH;
            break;
        case EH:
            (*T)->bf = L->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            L->bf = LH;
            break;
        }
        Lr->bf = EH;
        L_Rotate(&(*T)->lchild); //对T的左子树作左旋平衡处理
        R_Rotate(T);             //对T作右旋平衡处理
        break;
    }
}
//对以指针T所指结点为根的二叉树作右平衡处理
void RightBalance(BiTree *T)
{
    BiTree R, Rl;
    R = (*T)->rchild; // R指向T的右子树根结点
    switch (R->bf)
    {        //检查T的右子树的平衡度，并作相应平衡处理
    case RH: //新结点插入在T的右孩子的右子树上，要作单左旋处理
        (*T)->bf = R->bf = EH;
        L_Rotate(T);
        break;
    case LH:            //新结点插入在T的右孩子的左子树上，要作双旋处理
        Rl = R->lchild; // Rl指向T的右孩子的左子树根上
        switch (Rl->bf)
        { //修改T及其右孩子的平衡因子
        case RH:
            (*T)->bf = LH;
            R->bf = EH;
            break;
        case EH:
            (*T)->bf = R->bf = EH;
            break;
        case LH:
            (*T)->bf = EH;
            R->bf = RH;
            break;
        }
        Rl->bf = EH;
        R_Rotate(&(*T)->rchild); //对T的右子树作右旋平衡处理
        L_Rotate(T);             //对T作左旋平衡处理
    }
}
//若在平衡二叉树T中不存在和e有相同关键字的结点，则插入一个数据元素为e的结点
//若因插入而使二叉树失去平衡，则作平衡旋转处理
//布尔变量taller反映T长高与否
Status InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!*T)
    { //插入新结点，树“长高”，置taller为TRUE
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    }
    else
    {
        if (e == (*T)->data)
        { //树中已存在和e有相同关键字的结点，则不插入
            *taller = FALSE;
            return FALSE;
        }
        if (e < (*T)->data)
        { //继续在T的左子树中进行搜索
            if (!InsertAVL(&(*T)->lchild, e, taller))
            { //未插入
                return FALSE;
            }
            if (*taller)
            { //已插入到T的左子树且左子树“长高”
                switch ((*T)->bf)
                {        //检查T的平衡度
                case LH: //原本左子树比右子树高，左平衡处理
                    LeftBalance(T);
                    *taller = FALSE;
                    break;
                case EH: //原本左子树与右子树等高，现因左子树增高而增高
                    (*T)->bf = LH;
                    *taller = TRUE;
                    break;
                case RH: //原本右子树比左子树高，现左右子树等高
                    (*T)->bf = EH;
                    *taller = FALSE;
                    break;
                }
            }
        }
        else
        { //继续在T的右子树进行搜索
            if (!InsertAVL(&(*T)->rchild, e, taller))
            { //未插入
                return FALSE;
            }
            if (*taller)
            { //以插入到T的右子树且右子树“长高”
                switch ((*T)->bf)
                {        //检查T的平衡度
                case LH: //原本左子树比右子树高，现左右子树等高
                    (*T)->bf = EH;
                    *taller = FALSE;
                    break;
                case EH: //原本左子树与右子树等高，现因右子树增高而增高
                    (*T)->bf = RH;
                    *taller = TRUE;
                    break;
                case RH: //原本右子树比左子树高，右平衡处理
                    RightBalance(T);
                    *taller = FALSE;
                    break;
                }
            }
        }
    }
    return TRUE;
}
//创建平衡二叉树
Status CreateAVL(BiTree *T)
{
    int i;
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    *T = NULL;
    Status taller;
    for (i = 0; i < 10; i++)
    {
        InsertAVL(&*T, a[i], &taller);
    }
}
//前序遍历
void PreOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    printf("%d ", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
void main()
{
    BiTree T;
    CreateAVL(&T);
    PreOrderTraverse(T);
}