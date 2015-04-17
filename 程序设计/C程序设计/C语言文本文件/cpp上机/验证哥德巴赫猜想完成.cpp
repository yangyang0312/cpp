#include<stdio.h>
int isprime(int n)
{
int j=2;
if(n<=1) return 0;
for( ;j*j<=n;++j)
{
	if(n%j==0)
		return 0;
}
return 1;
}
int main()
{
	int x,i,m,a;
	scanf("%d",&x);
	for(i=0;i<x;i++)
	{
	scanf("%d",&a);
	for(m=3;m<=a/2;m+=2)
	{
		if(isprime(m)&&isprime(a-m))
		{
			printf("%d %d\n",m,a-m);
				break;
		}
	}
	}
	return 0;
}
