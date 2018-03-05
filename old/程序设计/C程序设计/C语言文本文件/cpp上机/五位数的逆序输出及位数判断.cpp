#include<stdio.h>

int main()
{
	int x;
	scanf("%d",&x);
	if(x>=0&&x<=99999)
	{
		int a=x/10000;
		int b=(x-10000*a)/1000;
		int c=(x-10000*a-1000*b)/100;
		int d=(x-10000*a-1000*b-100*c)/10;
		int e=x-10000*a-1000*b-100*c-10*d;
		int y=a+10*b+100*c+1000*d+10000*e;                   //提取各位数
		printf("%d\n",y);
		printf("%d  %d  %d  %d  %d\n",a,b,c,d,e);
		if(a==0)                                  
		{
			if(b==0)
			{
				if(c==0)
				{
					if(d==0)
					{
					printf("一位数");
					}
					else
						printf("二位数");
				}
				else
					printf("三位数");
			}
			else
				printf("四位数");
		}
		else
		printf("五位数");                            //位数判断
	}	
return 0;
}