#include<stdio.h>

int fib(int n)
{
    return n==0||n==1?1:fib(n-1)+fib(n-2);
}                     //fib函数部分

int main()
{
    int n,i;
    printf("请输入fib函数n值：");
    scanf("%d",&n);
    for(i=0;i<=n;i++)printf("fib(%d)=%d\n",i,fib(i));
return 0;
}
