#include<stdio.h>


double fun(int n){
	int i=1;
double g=0;
	while(i<=n){
	    g=1/(1+g);
		i=i+1;
	}
	return g;
}

int j=0,m,x;
void main(){
	scanf("%d",&m);
	if(m>0&&m<100){
		while(j<m){
		    scanf("%d",&x);
		    printf("%.6lf\n",fun(x));
			j=j+1;
		}
	}
}
