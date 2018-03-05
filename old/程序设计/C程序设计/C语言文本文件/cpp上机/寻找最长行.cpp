#include<stdio.h>
#include<string.h>

void main(){
	int max,max1;
	char m[100]={0},n[100]={0};
	gets(m);
	max=strlen(m);
	strcpy(n,m);
	while(strcmp(m,"***end***")!=0){
		if(max<strlen(m)){
			max=strlen(m);
			strcpy(n,m);
		}
		gets(m);
	}
	printf("%d\n%s\n",max,n);
}