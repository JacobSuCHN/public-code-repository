#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <io.h>

//折半查找
int Binary_Search(int *a, int n, int key)
{
    int low, high, mid;
    low = 1;  //定义最低下标为记录首位
    high = n; //定义最高下标为记录末位
    while (low <= high)
    {
        mid = (low + high) / 2; //折半
        if (key < a[mid])
        {                   //若查找值比中值小
            high = mid - 1; //最高下标调整到中值下标小一位
        }
        else if (key > a[mid])
        {                  //若查找值比中值大
            low = mid + 1; //最低下标调整到中值下标大一位
        }
        else
        {
            return mid; //若相等，则mid即为查找到的为止
        }
    }
    return 0;
}
//插值查找
int Interpolation_Search(int *a, int n, int key)
{
    int low, high, mid;
    low = 1;  //定义最低下标为记录首位
    high = n; //定义最高下标为记录末位
    while (low <= high)
    {
        mid = low + ((key - a[low]) / (a[high] - a[low])) * (high - low); //插值
        if (key < a[mid])
        {                   //若查找值比中值小
            high = mid - 1; //最高下标调整到中值下标小一位
        }
        else if (key > a[mid])
        {                  //若查找值比中值大
            low = mid + 1; //最低下标调整到中值下标大一位
        }
        else
        {
            return mid; //若相等，则mid即为查找到的为止
        }
    }
    return 0;
}
int F[100];
//斐波那契查找
int Fibonacci_Search(int *a, int n, int key)
{
    int low, high, mid, i, k;
    low = 1;  //定义最低下标为记录首位
    high = n; //定义最高下标为记录末位
    k = 0;
    while (n > F[k] - 1)
    { //计算n位于斐波那契数列的位置
        k++;
    }
    for (i = n; i < F[k] - 1; i++)
    { //将不满的数值补全
        a[i] = a[n];
    }
    while (low <= high)
    {
        mid = low + F[k - 1] - 1; //计算当前分隔的下标
        if (key < a[mid])
        {                   //若查找记录小于当前分隔记录
            high = mid - 1; //最高下标调整到分割下标mid-1处
            k = k - 1;      //斐波那契数列下标减一位
        }
        else if (key > a[mid])
        {                  //若查找记录大于当前分隔记录
            low = mid + 1; //最低下标调整到分割下标mid+1处
            k = k - 2;     //斐波那契数列下标减两位
        }
        else
        {
            if (mid <= n)
            {
                return mid; //若相等则说明mid即为查找到的位置
            }
            else
            {
                return n; //若mid>n说明是补全数值，返回n
            }
        }
    }
    return 0;
}
void main()
{
    int i, len, result;
    int a[] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};
    len = sizeof(a) / sizeof(a[0]) - 1;
    result = Binary_Search(a, len, 59);
    printf("Binary Search:%d\n", result);
    result = Interpolation_Search(a, len, 59);
    printf("Interpolation Search:%d\n", result);

    F[0] = 0;
    F[1] = 1;
    for (i = 2; i < 100; i++)
    {
        F[i] = F[i - 1] + F[i - 2];
    }
    result = Fibonacci_Search(a, len, 59);
    printf("Fibonacci Search:%d\n", result);
}