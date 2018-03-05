#include<stdio.h>
int m,n,a[256][256]={0},i,j,sum=0;
float arr=0;
void main(){
	scanf("%d%d",&m,&n);
	if(m>=0&&m<=256&&n>=0&&n<=256){
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				sum=sum+a[i][j];
			}
		}
		arr=sum/(m*n);
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				if(a[i][j]>=arr){
					a[i][j]=1;
				}
				else a[i][j]=0;
			}
		}
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
	}
}