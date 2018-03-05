#include<stdio.h>
int a=1,b,m,x,y;

int main(){
	scanf("%d",&m);
	while (a<=m){
		if (m>0&&m<100){
			scanf("%d %d",&x,&y);
			if(x%4==0)
				if(x%100==0){
					if(x%400==0){
						if(y==1||y==3||y==5||y==7||y==8||y==10||y==12)
							printf("31\n");
						else if(y==2)
							printf("29\n");
						else printf("30\n");
					}
					else if(y==1||y==3||y==5||y==7||y==8||y==10||y==12)
							printf("31\n");
						else if(y==2)
							printf("28\n");
						else printf("30\n");
				}
				else if(y==1||y==3||y==5||y==7||y==8||y==10||y==12)
							printf("31\n");
						else if(y==2)
							printf("29\n");
						     else printf("30\n");
			else if(y==1||y==3||y==5||y==7||y==8||y==10||y==12)
							printf("31\n");
						else if(y==2)
							printf("28\n");
						else printf("30\n");
		}
		a=a+1;
	}
	return 0;
}
