#include<stdio.h>

int gewei(int n)
{
    return n<10?n:n%10+gewei(n/10);
}

int main()
{
    int n;
    printf("请输入要求各位数和的数n:");
    scanf("%d",&n);
    printf("%d的各位数和为%d\n",n,gewei(n));
return 0;
}
