#include<stdio.h>
void main(){
	int m,n,i,a[100]={0},b[100]={0},c,d,e=0,f;
	scanf("%d%d",&n,&m);
	if(m>0&&m<99999999&&n>0&&n<100){
		for(i=0;i<n;i++){
			scanf("%d",&a[i]);
			b[i]=a[i];
		}
		for(f=0;f<n;f++){
			c=(m+e)%i;
			if(c==0) {c=i;}
			m=a[c-1];
			e=c-1;
			for(d=0;m!=b[d];d++){}
			printf("%d ",d+1);
			i--;
			for(d=c;d<=i;d++){
				a[d-1]=a[d];
			}
		}
		printf("\n");
	}
}