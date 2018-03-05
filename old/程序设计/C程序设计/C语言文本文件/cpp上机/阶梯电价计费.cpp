#include <stdio.h>

int a,i;
float du;
 main (){
scanf("%d",&a);
if (a<100&&a>0){
	for (i=1;i<=a;i++){
	scanf ("%f",&du);
	if (du>0&&du<=110){
	printf("%.2f\n",0.5*du);
	}
	if (du>110&&du<=210){
	printf("%.2f\n",55+(du-110)*0.55);
	}
	if (du>210){
	printf("%.2f\n",110+(du-210)*0.7);
	}
	}

}
}
