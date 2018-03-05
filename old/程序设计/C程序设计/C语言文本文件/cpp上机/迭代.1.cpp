#include<stdio.h>
long fib1(int n)
{
	long f1=1,f2=1,f3,i;
	if(n<=1) return 1;
	for(f3=f1+f2,i=2;i<n;++i)
	{
		f1=f2;
		f2=f3;
		f3=f1+f2;
	}
	return f3;
}
int main()
{
	int a;
	scanf("%d",&a);
	printf("%ld",fib1(a));
}