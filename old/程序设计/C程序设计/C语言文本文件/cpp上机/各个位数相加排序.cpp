#include<stdio.h>
int a[1000]={0},b[1000]={0},m,i,s,n,p;
void main(){
	scanf("%d",&m);
	if(m>0&&m<1000){
		for(i=0;i<m;i++){
			scanf("%d",&a[i]);
			p=a[i];
			s=0;
			while(p!=0){
				n=p%10;
				s=s+n;
				p=p/10;
			}
			b[i]=s;
		}
		for(i=0;i<m;i++){
			for(s=0;s<m-1;s++){
				if(b[s]>b[s+1]){
					n=b[s];
					b[s]=b[s+1];
					b[s+1]=n;
				}
			}
		}
		for(i=0;i<m;i++){
			printf("%d ",b[i]);
		}
		printf("\n");
	}
}