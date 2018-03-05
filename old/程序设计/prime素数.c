#include<stdio.h>
#include<math.h>

int prime(int a)
{
int i;
for(i=2;i<=(int)(sqrt(a));i++)if(a%i==0)break;
return i>(int)(sqrt(a));
}

int main()
{
    int i,n;
    printf("请输入要求的素数上限：");
    scanf("%d",&n);
    for(i=2;i<=n;i++)if(prime(i))printf("%d is a prime\n",i);
    return 0;
}
