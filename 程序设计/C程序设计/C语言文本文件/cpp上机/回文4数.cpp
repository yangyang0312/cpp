#include <stdio.h>
#include <math.h>

 main(){
	int g;
	scanf ("%d",&g);
	int a,aaa;
	for (int i=0;i<g;i++){
		scanf ("%d",&aaa);
		a=aaa;
		int j;
		for (j=1;;j++){
			if (a<pow(10,j)){
				break;
			}
		}
		int k,bb=0,cc=0,aa;
		for (k=0;k<j;k++){
			aa=a%10;
			a/=10;
			bb+=(pow(10,j-k-1)*aa);
			cc+=aa;
		}
		if (bb==aaa){
			printf("%d\n",cc);
		}
		else {
			printf("no\n");
		}
	}
}
