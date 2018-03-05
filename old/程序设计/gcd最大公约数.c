#include<stdio.h>

int gcd(int a,int b)
{
    int i,min=a>b?b:a;
    for(i=min;i>1;i--)if(a%i==0&&b%i==0)break;return i;
}

int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    printf("the gcd of %d and %d is %d\n",a,b,gcd(a,b));
return 0;
}
