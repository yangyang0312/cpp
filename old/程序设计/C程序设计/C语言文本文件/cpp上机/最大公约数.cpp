#include<stdio.h>

int a=1,b,c;
void gcd(int x,int y){

	if(x<y)
		b=y;
	else b=x;
for (a=1;a<=b;a++){
		if (x%a==0&&y%a==0){
			c=a;
		}
		}
printf("%d\n",c);
}

long m,n;
void main(){
	do{
		scanf ("%d %d",&m,&n);
		if (m!=0||n!=0){
			gcd (m,n);
		}
	}
	while (m!=0||n!=0);
}
	
