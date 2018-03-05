#include <stdio.h>

int sushu(int shu){
	if (shu>1){
		for(int i=2;i<=shu;i++){
			if(shu%i==0){
				if(shu!=i){
					return 0;
					break;
				}
				
				if(shu==i){
					return 1;
				}
				
			}
		}
	}
}

int a,b;
void main(){
	scanf("%d",&a);
	b=sushu(a);
	if(b==1){
		printf("%d是素数！\n",a);
	}
	else{
		printf("%d不是素数！\n",a);
	}
}