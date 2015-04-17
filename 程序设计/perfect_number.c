#include <stdio.h>

int main()
{
	int n,i,sum;

	for(n=1;n<=10000;n++)
	{
		//求n的因子之和 
		for(sum=0,i=1;i<=n/2;i++)
		{
			if(n%i==0)
				sum+=i;
		}
		//判断n是不是完数 
		if(sum==n)
			printf("%d\n",n);
	}
	return 0;
}
