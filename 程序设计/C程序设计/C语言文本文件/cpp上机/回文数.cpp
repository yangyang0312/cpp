#include<stdio.h>
#include<string.h>
char c[1024]={0},d[1024]={0};
void main(){
	int m,a,i,x=0;
	scanf("%d",&m);
	for(a=0;a<m;a++){
	scanf("%s",&c);
	int b=strlen(c);
	for(i=0;i<b;i++){
		d[i]=c[b-1-i];
	}
	if(strcmp(c,d)==0){
		for(i=0;i<b;i++){
			x+=(c[i]-48);
		}
			printf("%d\n",x);
	}
	else{
		printf("no\n");
	}
	}
}