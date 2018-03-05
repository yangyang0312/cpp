#include <stdio.h>
#include <math.h>
char a[1024]={0};
void main(){
scanf("%s",&a);
long double sum=0;
int c;
int b=strlen(a);
for (int i=0;i<b;i++){
if (a[i]=='.'){
c=i;
break;
}
if(i==b-1){
c=b;
}
}
for (int i=0;i<b;i++){
if (i<c){
sum+=pow(10,c-1-i)*(a[i]-48);
}
if (i>c){
sum+=pow(10.0,c-i)*(long double)(a[i]-48);
}
}
printf("%lf",sum);
}