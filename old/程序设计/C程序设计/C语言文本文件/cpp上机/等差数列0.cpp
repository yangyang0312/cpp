#include<stdio.h>

void main(){
	int i,T,n;
	scanf("%d",&T);
	if(T<=10&&T>0){
		for(i=0;i<T;i++){
			int x[100]={0},m=0,a=0,b=0;
			scanf("%d",&m);
			if(m>0&&m<100){
			    for(a=0;a<m;a++){
				    scanf("%d",&x[a]);
				}
			}
			for(b=0;b<m;b++){
			for(a=0;a<m;a++){
				if(x[a]>=x[a+1]){
					continue;
				}
				else{
					n=x[a];
					x[a]=x[a+1];
					x[a+1]=n;
				}
			}
			}
			for(a=1;a<m-1;a++){
				if(2*x[a]==x[a-1]+x[a+1])
					continue;
				else break;
			}
			if(a==m-1){
				printf("%d\n",x[1]-x[2]);
			}
			else{ 
				printf("no\n");
			}
		}
	}
}