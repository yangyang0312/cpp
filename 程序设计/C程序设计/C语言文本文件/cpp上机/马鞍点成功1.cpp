#include<stdio.h>
int main()
{
	int i,j,n,m,k,l,flag,minn,maxx;
	int a[100][100]={{0,0}};
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		scanf("%d",&a[i][j]);
	}
	flag=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			minn=a[i][j];
			for(k=0;k<m;k++)
			{
				if(minn>a[i][k])
					break;
			}
			if(k==m)
			{
				maxx=a[i][j];
				for(l=0;l<n;l++)
				{
					if(maxx<a[l][j])
						break;
				}
				if(l==n)
				{
					printf("%d %d %d",i,j,a[i][j]);
					flag=1;
				}
			}
		}
	}
	if(flag==0)
		printf("no");
return 0;
}
		
