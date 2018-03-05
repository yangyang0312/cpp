#include<stdio.h>

const int maxn=1e9+7;

int sum(int n)
{
    int i=1,j=1,k=1;
    long long num=0;
    for(;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            for(k=1;k<=n;k++)
            {
                int t=0;
                if(i==j)t++;
                if(j==k)t++;
                if(i==k)t++;
                if(t!=1)num=(num+i*j*k)%maxn;
            }
        }
    }
    printf(" %d\n",num);
    return 0;
}

int main()
{
    int t,i=1;
    scanf("%d",&t);  //test num
    for(;i<=t;i++)
    {
        int n;
        scanf("%d",&n);   //each num
        printf("Case %d:",i);
        sum(n);
    }
    return 0;
}
