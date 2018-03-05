#include <stdio.h>

int sushu(int a){
	int i;
	for (i=2;i<a;i++){
		if (a%i==0) {
			return 0;
		}
		if (i==a-1){
			return 1;
			break;
		}
	}
}
main(){
	int i,j=0;
	for (i=100;i<201;i++){
		if (sushu(i)==1){
			j+=i;
		}
	}
	printf("%d\n",j);
}