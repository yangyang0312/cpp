#include<stdio.h>

int gcd(int n,int m)
{
    m==0?n:gcd(m,n%m);
}

int main()
{
    while(1)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        printf("%d\n",gcd(n,m));
    }
    return 0;
}
