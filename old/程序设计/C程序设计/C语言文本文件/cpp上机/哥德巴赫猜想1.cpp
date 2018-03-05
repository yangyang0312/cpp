#include<stdio.h>

int m;
int isPrime(long n){
	int m=n-1;
	while(n%m!=0){
		m=m-1;
	}
	if(m==1){
		return 1;
	}
	else
		return 0;
}

int a,i=1,b,c=2;
void main(){
	scanf("%d",&a);
	if(a>0&&a<100){
		while(i<=a){
			scanf("%d",&b);
	        while(c<b){
		        if(isPrime(c)==1&&isPrime(b-c)==1){
			         printf("%d %d\n",c,b-c);
			         break;
				}
		        else
			         c=c+1;
			}
	        i=i+1;
		}
	}
}