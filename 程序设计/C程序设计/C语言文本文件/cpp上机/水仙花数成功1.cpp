#include<stdio.h>
int fun (int a,int b)
{
int i,j,z,c,e,sum,d,f=0,p;
for(i=a;i<=b;i++)
{
	j=0;z=i;c=i;p=i;sum=0;
	while(p) {
		p=p/10;
		j++;
	}
	while(z) {
		d=1;
		for(e=0;e<j;e++)
		{d=d*(z%10);}
		z=z/10;
	    sum=sum+d;
	}
	if(sum==c) f++;
}
return f;
}
int main()
{
	int g,h,m,n,t;
	scanf("%d",&g);
	for(h=0;h<g;h++) {
		scanf("%d %d",&m,&n);
		if(m>n){t=m;m=n;n=t;}
		if(m<100) m=100;
		printf("%d\n",fun(m,n));
	}
	return 0;
}