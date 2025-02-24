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

typedef char String[MAXSIZE];

//生成一个其值等于chars的串T
Status StrAssign(String T, char *chars)
{
    int i;
    if (strlen(chars) > MAXSIZE)
        return ERROR;
    else
    {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++)
        {
            T[i] = *(chars + i - 1);
        }
        return OK;
    }
}

//通过计算返回子串T的next数组
void get_next(String T, int *next)
{
    int i, j;
    i = 1;
    j = 0;
    next[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        { // T[i]表示后缀的单个字符，T[j]表示前缀的单个字符
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j]; //若字符不相同，则j值回溯
        }
    }

    // for (int k = 1; k <= T[0]; k++)
    // {
    //     printf("%d ", next[k]);
    // }
    // printf("\n");
}
//求模式串T的next函数修正值并存入数组nextval
void get_nextval(String T, int *nextval)
{
    int i, j;
    i = 1;
    j = 0;
    nextval[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        { // T[i]表示后缀的单个字符，T[j]表示前缀的单个字符
            i++;
            j++;
            if (T[i] != T[j])
            {                   //当前字符与前缀字符不同
                nextval[i] = j; //则当前的j为nextval在i位置的值
            }
            else
            {                            //当前字符与前缀字符相同
                nextval[i] = nextval[j]; //字符的nextval值赋值给nextval在i位置的值
            }
        }
        else
        {
            j = nextval[j]; //若字符不相同，则j值回溯
        }
    }

    // for (int k = 1; k <= T[0]; k++)
    // {
    //     printf("%d ", nextval[k]);
    // }
    // printf("\n");
}

// T为非空串，返回子串T在主串S中第pos个字符之后的位置
int Index_KMP(String S, String T, int pos)
{
    int i = pos;       // i用于主串S中当前位置下标，若pos不为1，则从pos位置开始匹配
    int j = 1;         // j用于子串T中当前位置的下标值
    int next[255];     //定义一next数组
    get_next(T, next); //对串T做分析，得到next数组
    // get_nextval(T, next);
    // O(n)
    while (i <= S[0] && j <= T[0])
    {
        if (j == 0 || S[i] == T[j])
        { //两字符相等则继续，增加了j=0判断
            i++;
            j++;
        }
        else
        {                //指针后退重新开始匹配
            j = next[j]; // j回退到适合的位置，i值不变
        }
    }
    if (j > T[0])
    { //若查找成功j=T[0]+1
        return i - T[0];
    }
    else
    {
        return 0;
    }
}

void main()
{
    int pos;
    char *s = "goodgoogle";
    char *t = "google";
    String S, T;
    StrAssign(S, s);
    StrAssign(T, t);
    pos = Index_KMP(S, T, 1);
    printf("pos=%d\n", pos);
}