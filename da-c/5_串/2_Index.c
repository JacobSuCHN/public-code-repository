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
// T为非空串，返回子串T在主串S中第pos个字符之后的位置
int Index(String S, String T, int pos)
{
    int i = pos; // i用于主串S中当前位置下标，若pos不为1，则从pos位置开始匹配
    int j = 1;   // j用于子串T中当前位置的下标值
    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {                  //指针后退重新开始匹配
            i = i - j + 2; // i退回上次匹配首位的下一位
            j = 1;         // j回到子串T的首位
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
    pos = Index(S, T, 1);
    printf("pos=%d\n", pos);
}