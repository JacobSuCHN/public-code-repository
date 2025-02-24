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
    struct BiTNode *lchild, *rchild; //左右孩子指针
} BiTNode, *BiTree;

Status Delete(BiTree *p);
Status DeleteBST(BiTree *T, int key);
//递归查找二叉排序树T中是否存在key
//指针f指向T的双亲，其初始调用值为NULL
//若查找成功，则指针p指向该数据元素结点；否则指针p指向查找路径上访问的最后一个结点
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if (!T)
    { //查找不成功
        *p = f;
        return FALSE;
    }
    else if (key == T->data)
    { //查找成功
        *p = T;
        return TRUE;
    }
    else if (key < T->data)
    { //在左子树继续查找
        return SearchBST(T->lchild, key, T, p);
    }
    else
    { //在右子树继续查找
        return SearchBST(T->rchild, key, T, p);
    }
}
//当二叉排序树T中不存在关键字等于key的数据元素时，插入key
Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;
    if (!SearchBST(*T, key, NULL, &p))
    { //查找不成功
        s = (BiTree)malloc(sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;
        if (!p)
        {
            *T = s; //插入s为新的根结点
        }
        else if (key < p->data)
        {
            p->lchild = s; //插入s为左孩子
        }
        else
        {
            p->rchild = s; //插入s为右孩子
        }
        return TRUE;
    }
    else
    {
        return FALSE; //树中已有关键字相同的结点，不插入
    }
}
//创建二叉排序树
Status CreateBST(BiTree *T)
{
    int i;
    int a[10] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
    *T = NULL;
    for (i = 0; i < 10; i++)
    {
        InsertBST(&*T, a[i]);
    }
}

//若二叉排序树T中存在关键字等于key的数据元素，删除该数据元素结点
Status DeleteBST(BiTree *T, int key)
{
    if (!*T)
    { //不存在关键字等于key的元素
        return FALSE;
    }
    else
    {
        if (key == (*T)->data)
        { //找到关键字等于key的元素
            return Delete(T);
        }
        else if (key < (*T)->data)
        {
            return DeleteBST(&(*T)->lchild, key);
        }
        else
        {
            return DeleteBST(&(*T)->rchild, key);
        }
    }
}

//从二叉树中删除结点p，并重接它的左或右子树
Status Delete(BiTree *p)
{
    BiTree q, s;
    if ((*p)->rchild == NULL)
    { //右子树空则只需重接它的左子树
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    else if ((*p)->lchild == NULL)
    { //左子树空则只需重接它的右子树
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else
    { //左右子树均不空
        q = *p;
        s = (*p)->lchild;
        while (s->rchild)
        { //转左，然后向右到尽头（找待删结点的前驱）
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data; // s指向被删结点的直接前驱
        if (q != *p)
        {
            q->rchild = s->lchild; //重接q的右子树
        }
        else
        {
            q->lchild = s->lchild; //重接q的左子树
        }
        free(s);
    }
    return TRUE;
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
    CreateBST(&T);
    PreOrderTraverse(T);
    printf("\n");
    DeleteBST(&T,47);
    PreOrderTraverse(T);
    printf("\n");
}