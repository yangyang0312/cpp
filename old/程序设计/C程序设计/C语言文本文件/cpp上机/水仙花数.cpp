#include<stdio.h>
#include<math.h>

int fun(int a,int b){
	int max,min,n,j,d,s,m;
	if(a>=b){
		max=a;
		min=b;
	}
	else{
		max=b;
		min=a;
	}
	if(min<100){
		min=100;
		if(min>max){
			return 0;
		}
	}
	for(d=0;min<=max;min++){
		for(j=0;min>pow(10,j);j++){}
		m=min;
		s=0;
		while(m!=0){
			n=m%10;
			s=s+pow(n,j);
			m=m/10;
		}
		if(s==min){
			d=d+1;
		}
	}
	return d;
}

void main(){
	int m,i,a,b;
	scanf("%d",&m);
	for(i=0;i<m;i++){
		scanf("%d%d",&a,&b);
		printf("%d\n",fun(a,b));
	}
}
