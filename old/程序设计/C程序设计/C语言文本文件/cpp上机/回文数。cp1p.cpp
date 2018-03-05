#include <stdio.h>
#include <math.h>

void main(){
	int g;
	scanf ("%d",&g);
	int a;
	for (int i=0;i<g;i++){
		scanf ("%d",&a);
		int j;
		for (j=1;;j++){
			if (a<pow(10,j)){
				break;
			}
		}
		int k,bb=0,cc=0,aa;
		for (k=0;k<j;k++){
			aa=a%10;
			bb+=(pow(10,k)*aa);
			cc+=aa;
		}
		if (aa==a){
			printf("%d\n",cc);
		}
		else {
			printf("no\n");
		}
	}
}