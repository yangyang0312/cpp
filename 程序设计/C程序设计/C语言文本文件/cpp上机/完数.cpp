#include<stdio.h>

int a,b,c,x,y;
int main(){
	scanf("%d%d",&x,&y);
	b=x;
	while(b<=y){
		a=1;
		c=0;
		while(a<b){
			if(b%a==0){
				c=c+a;
				a=a+1;
			}
			else a=a+1;
		}
		if(c==b){
			printf("%d\n",c);
			b=b+1;
		}
		else b=b+1;
	}
	return 0;
}