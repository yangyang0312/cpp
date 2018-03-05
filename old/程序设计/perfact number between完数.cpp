#include<stdio.h>

int perfact_number(int a)
{
    int i,j=0;
    for(i=1;i<=a/2;i++)
    {
        if(a%i==0)j+=i;
    }
    if(j==a)return 1;
	else return 0;
}

int main()
{
    int i,n;
    printf("请输入要求的完数上限:");
    scanf("%d",&n);
    for(i=1;i<=n;i++)if(perfact_number(i))printf("%dis a perfact numbers\n",i);
return 0;
}
