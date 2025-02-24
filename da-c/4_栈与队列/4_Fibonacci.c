#include <stdio.h>
//斐波那契数列的递归函数
int Fib(int i)
{
    if (i < 2)
    {
        return i == 0 ? 0 : 1;
    }
    return Fib(i - 1) + Fib(i - 2); //调用自己
}
void main()
{
    for (int i = 0; i < 10; i++)
    {
        printf("%2d  ", Fib(i));
    }
}
