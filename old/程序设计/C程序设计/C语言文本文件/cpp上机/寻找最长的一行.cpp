#include <stdio.h>
#include <string.h>
int main()
{
	char a[100]="0",b[100]="0",c[10]="***end***";
	int n=0,m,d,i;
	while(1)
	{
		gets(a);
		m=strlen(a);
		d=strcmp(a,c);
		if(d==0)break;
		if(m>n)
		{
			n=m;
			strncpy(b,a,m);
		}
	}
	printf("%d\n",n);
	for(i=0;i<n;i++)
	{
		printf("%c",b[i]);
	}
	printf("\n");

	return 0;
}
