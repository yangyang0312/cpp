#include<stdio.h>

int a[20][20]={0},m,i,j,b[42]={0},c;
void main(){
	scanf("%d",&m);
	if(m>2&&m<=20){
		for(i=0;i<m;i++){
			for(j=0;j<m;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(i=0;i<m;i++){
			int n=0;
			for(j=0;j<m;j++){
				n=n+a[i][j];
			}
			b[i]=n;
		}
		c=i;
		for(i=0;i<m;i++){
			int n=0;
			for(j=0;j<m;j++){
				n=n+a[j][i];
			}
			b[c+i]=n;
		}
		int n=0,j=0;
		for(i=0;i<m;i++){
			n=n+a[i][i];
			j=j+a[i][m-1-i];
		}
		b[2*c+1]=n;
		b[2*c+2]=j;
		for(i=0;i<2*c+2;i++){
			for(j=0;j<2*c+2;j++){
				if(b[j]<b[j+1]){
					n=b[j];
					b[j]=b[j+1];
					b[j+1]=n;
				}
			}
		}
		for(i=0;i<2*c+2;i++){
			printf("%d ",b[i]);
		}
		printf("\n");
	}
}