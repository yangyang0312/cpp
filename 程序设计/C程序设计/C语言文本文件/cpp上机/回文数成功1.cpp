#include<stdio.h>
int main()
{
	char a;
	int i,j,t,n,sum,b[40]={0},flag;
	scanf("%d",&n);
	getchar();
	for(i=0;i<n;i++)
	{
		t=0;
		while((a=getchar())!='\n')
		{b[t]=a-'0';t++;}
		for(j=0;j<=t/2;j++)
		{
			flag=1;
			if(b[j]-b[t-1-j]!=0)
			{flag=0;break;}
		}
		if(flag==0)
			printf("no\n");
		else{
			for(j=0,sum=0;j<t;j++)
				sum+=b[j];
			printf("%d\n",sum);
		}
	}
	return 0;
}
