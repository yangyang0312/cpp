#include <stdio.h>

int jiaogu(int a){
	if (a%2==0){
		return (a/2);
	}
	if (a%2==1){
		return (3*a+1);
	}
}

int aa,bb;
void main(){
	scanf ("%d",&aa);
	if (aa>0&&aa<100){
		for (int i1=1;i1<=aa;i1++){
			scanf ("%d",&bb);
			
			for (int i2=1;;i2++){
				
				if(bb==1){
					break;
				}
				else{
					bb=jiaogu(bb);
				}	
			}
			printf ("%d\n",i2);
		}
	}
}