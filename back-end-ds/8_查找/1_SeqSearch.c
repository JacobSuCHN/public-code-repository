#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <io.h>

//顺序查找，a为数组，n为要查找的数组长度
int Sequential_Search1(int *a, int n, int key)
{
    int i;
    for (i = 0; i <= n; i++)
    {
        if (a[i] == key)
        {
            return i;
        }
    }
    return 0;
}
//有哨兵顺序查找
int Sequential_Search2(int *a, int n, int key)
{
    int i;
    a[0] = key; //设置a[0]为关键字值，称之为“哨兵”
    i = n;      //循环从组尾部开始
    while (a[i] != key)
    {
        i--;
    }
    return i; //返回0则说明查找失败
}

void main()
{
    int i, len, result;
    int a[] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};
    len = sizeof(a) / sizeof(a[0])-1;
    result = Sequential_Search1(a, len, 59);
    printf("No sentinel:%d\n", result);
    result = Sequential_Search2(a, len, 59);
    printf("Sentinel:%d\n", result);
}