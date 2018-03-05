#include<stdio.h>

int n,a[100]={0},b[100]={0},i=1,c=0,m,d=0;
int main(){
	scanf("%d",&n);
	if(n>0&&n<=100){
		while(i<=n){
			scanf("%d",&m);
			if(m%2==0){
				a[c]=m;
				c++;
			}
			else{
				b[d]=m;
				d++;
			}
			i++;
		}
		for(i=1;i<=c||i<=d;i++){
			for(m=0;m<c;m++){
				if(a[m]>=a[m+1]){
					continue;
				}
				else{
					n=a[m];
					a[m]=a[m+1];
					a[m+1]=n;
				}
			}
			for(m=0;m<d;m++){
				if(b[m]>=b[m+1]){
					continue;
				}
				else{
					n=b[m];
					b[m]=b[m+1];
					b[m+1]=n;
				}
			}
		}
		for(i=0;i<c;i++){
			printf("%d ",a[i]);
		}
		for(i=0;i<d;i++){
			printf("%d ",b[i]);
		}
		printf("\n");
	}
	return 0;
}
