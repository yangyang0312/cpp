#include<stdio.h>
#define MIN 1e-6

int fun(int n)
{
    int i=1,sum=1;
    for(;i<=n;i++)
    {
        sum*=i;
    }
    return sum;
}

int main()
{
    int n=1;
    double e=1.0;
    while(1)
    {
        e+=1.0/fun(n);
        if(1.0/fun(n)<MIN)break;
        n++;
    }
    printf("e的近似值为:%lf\n",e);
    return 0;
}
