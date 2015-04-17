#include<stdio.h>
#define MAX 3000
int qinmi(int n)
{
    int i,sum=1;
    for(i=2;i<=n/2;i++)
    {
        if(n%i==0)
        {
            sum+=i;
        }
    }
    return sum;
}

int main()
{
    int i=3;
    for(;i<=MAX;i++)
    {
        if(qinmi(qinmi(i))==i&&i!=qinmi(i))printf("%d和%d是一对亲密数\n",i,qinmi(i));
    }
    return 0;
}
