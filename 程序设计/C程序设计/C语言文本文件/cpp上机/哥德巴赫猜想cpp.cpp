#include <stdio.h>

int sushu(int shu){
	if (shu>1){
		for(int i=2;i<=shu;i++){
			if(shu%i==0){
				if(shu!=i){
					return 0;
					break;
				}
				
				if(shu==i){return 1;}
				
			}
		}
	}
}
int a,b;
void main(){
	scanf("%d",a);
	if (a>5){
		for (b=2;b<=a/2;b++){
			int c=a-b;
			if (sushu(b)==1&&sushu(c)==1){
				printf("%d=%d+%d",a,b,c);
			}
		}
	}
}