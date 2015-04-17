#include<stdio.h>
void main(){
	int m,n,i,j,sum,a[20][20]={0};
	scanf("%d%d",&m,&n);
	if(m>0&&m<20&&n>0&&n<20){
		for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(sum=0,i=0;i<m;i++){
			for(j=0;j<n;j++){
				if(a[i][j]!=0){
					sum=sum+1;}
			}
		}
		printf("%d %d %d\n",m,n,sum);
		for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				if(a[i][j]!=0){
					printf("%d %d %d\n",i,j,a[i][j]);
				}
			}
		}
	}
}