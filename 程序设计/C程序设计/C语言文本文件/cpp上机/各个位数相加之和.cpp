#include<stdio.h>
int m,a,b=1,c;
int main(){
	scanf("%d",&m);
	if(m>0&&m<100){
		while(b<=m){
			scanf("%d",&a);
			c=0;
			if(a>0&&a<1000000000){
			while(a!=0){
			c=c+a%10;
			a=a/10;
			}
			}
			b=b+1;
	
			printf("%d\n",c);
		}
	
	}
return  0;
	}