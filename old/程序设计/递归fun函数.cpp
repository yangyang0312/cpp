#include<stdio.h>

double fun(int n)
{
    return n==1?1:1/(1+fun(n-1));
}

int main()
{
    int m,i;
    printf("请输入数据组数：");
    scanf("%d",&m);
    if(m>0&&m<100)
    {
        for(i=1;i<=m;++i)
        {
            int n;
            scanf("%d",&n);
            printf("fun(%d)=%.6f\n",n,fun(n));
        }
    }
return 0;
}
