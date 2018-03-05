#include <stdio.h>

int zu,a,b,i;
int main () 
{
	scanf("%d",&zu);
	if (zu<=100)
	{
		for (i=1;i<=zu;i++)
		{
			scanf ("%d %d",&a,&b);
			if ((a%400==0)||(a%100!=0&&a%4==0))
			{
				if (b==2){
					printf("29\n");
				}
				if (b==1||b==3||b==5||b==7||b==8||b==10||b==12)
				{
					printf("31\n");
				}
				if (b==4||b==6||b==9||b==11)
				{
					printf("30\n");
				}
			}
			else{
				if (b==2)
				{
					printf("28\n");
				}
				if (b==1||b==3||b==5||b==7||b==8||b==10||b==12)
				{
					printf("31\n");
				}
				if (b==4||b==6||b==9||b==11)
				{
					printf("30\n");
					
				}
				
			}
		}
	}
	return 0;
}