#include <stdio.h>
#include <math.h>
int main(){
long double a,b;
int wei,i;
scanf("%lf",&a);
for(i=-9;;i++){
if (pow(10,i)>a){
wei=i;
break;
}
}
char *p,aa[1024]="00000000000";
long d,c,j;
if (wei>0){
d=a;
for(j=i;j>0;j--){
c=d%10;
d/=10;
aa[j-1]=c+48;
}
aa[wei]='.';
d=a;
a=a-d;
d=1000000000*a;
for(i=0;i<9;i++){
c=d%10;
d/=10;
aa[wei-i+9]=c+48;
}
}
else{
a+=1;
for(i=-9;;i++){
if (pow(10,i)>a){
wei=i;
break;
}
}
d=a;
for(j=i;j>0;j--){
c=d%10;
d/=10;
aa[j-1]=c+48;
}
aa[wei]='.';
d=a;
a=a-d;
d=1000000000*a;
for(i=0;i<9;i++){
c=d%10;
d/=10;
aa[wei-i+9]=c+48;
}
aa[1]='.';
aa[0]='0';
p=aa;
}
printf("%s\n",p);
}
