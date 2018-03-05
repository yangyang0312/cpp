#include<stdio.h>
void paixu(int n,int a[])
{
	int i,j;
	int t;
	for(i=1;i<n;++i)
	{
		for(t=a[i],j=i-1;j>=0&&t>a[j];--j)
			a[j+1]=a[j];
		if(j!=i-1) a[j+1]=t;
	}
}
int main()
{
	int m,j,i,b;
	int a[20][20]={{0,0}};
	int c[45]={0};
	scanf("%d",&m);
	for(j=0;j<m;j++)
	{
		for(i=0;i<m;i++)
		{
			scanf("%d",&b);
			a[j][i]=b;
		}
	}
	for(i=0;i<m;i++)
         c[42]+=a[i][i];
	for(i=0;i<m;i++)
		c[43]+=a[i][m-i-1];
    for(j=0;j<m;j++)
	{
		for(i=0;i<m;i++)
			c[j]=c[j]+a[j][i];
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
			c[20+i]+=a[j][i];
	}
	paixu(45,c);
	for(i=0;i<45;i++)
	{
		if(c[i]!=0)
		printf("%d ",c[i]);
	}


	return 0;
}

