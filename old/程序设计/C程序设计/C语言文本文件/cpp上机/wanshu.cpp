#include <stdio.h>

int a,b,i,h,k;
int wang(int i){
	int aa=0;
	for (h=1;h<i;h++){
		if (i%h==0){
			aa=aa+h;
		}
	}
	if (aa==i){
		return 1;
	}
	else {
		return 0;
	}
}
main (){
	scanf ("%d %d",&a,&b);
	for (i=a;i<=b;i++){
		k = wang(i);	
		if (k==1){
			printf("%d\n",i);
		}
	}
}
