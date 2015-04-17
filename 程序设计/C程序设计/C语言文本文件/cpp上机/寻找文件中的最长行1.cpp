#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main(){
	FILE*fp;
	int max=0;
	char m[100]={0},n[100]={0};
	fp=fopen("line.txt","r");
	if(fp==NULL){
		exit(0);}
	while(fgets(m,100,fp)!=0){
		if(max<strlen(m)){
			max=strlen(m);
			strcpy(n,m);
		}
	}
	fclose(fp);
	printf("%d\n%s\n",max,n);
}