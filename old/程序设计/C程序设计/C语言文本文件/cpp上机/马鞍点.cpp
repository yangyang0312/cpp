#include<stdio.h>

int m,n,a[100][100]={0},i,j,b,c,d,p;
void main(){
	scanf("%d %d",&m,&n);
	if(m>0&&m<100&&n>0&&n<100){
		for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				scanf("%d",&a[i][j]);
			}
		}
	for(i=0;i<m;i++){
		b=a[i][0];
		for(j=0;j<n;j++){
			if(b<=a[i][j]){
				continue;
			}
			else{
				b=a[i][j];
				d=j;
			}
		}
		for(c=0;c<m;c++){
			if(b>=a[c][d]){
				continue;
			}
			else{
				b=a[c][d];
				break;
			}
		}
		if(b==a[i][d]){
            printf("%d %d %d\n",i,d,b);
		}
		else p=0;
	}
    if(p=0) printf("no\n");
	}
}