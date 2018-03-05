# include <stdio.h>


void gcb(long num1,long num2)
{
	long aa,bb,cc;
	if (num1>num2){
		cc=num1;
	}
	else {
		cc=num2;
	}
	for (aa=1;aa<=cc;aa++){
		if (num1%aa==0&&num2%aa==0){
			bb=aa;
		}
	}
	printf ("%ld\n",bb);
}



long a,b;
void main (){
	do{
		scanf ("%d %d",&a,&b);
		if (a!=0||b!=0){
			gcb (a,b);
		}
	}
	while (a!=0||b!=0);
}
	
