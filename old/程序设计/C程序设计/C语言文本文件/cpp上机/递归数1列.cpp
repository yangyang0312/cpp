#include <stdio.h>

void hanshu(int a){
float b=1.0;
for (int i=0;i<a-1;i++){
b=1.0/(1.0+b);
}
printf("%.6f\n",b);
}
 main(){
int a,i,b;
scanf ("%d",&a);
for (i=0;i<a;i++){
scanf ("%d",&b);
hanshu(b);
}
}
