#include <stdio.h>
#include <time.h>

int aa,bb,cc,dd;
void main (){
	scanf("%d %d",&aa,&bb);
	double t1,t2;
	t1=clock();
	if (aa!=0&&bb!=0){
		if (aa>bb){
			cc=aa,dd=bb;
		}
		else{
			cc=bb,dd=aa;
		}
		for (int ee=cc;;ee+=cc){
			if (ee%dd==0){
				printf ("%d\n",ee);
				
				t2=clock();
				printf("%f\n",(t2-t1)/1000);
				break;
			}
		}
	}
}