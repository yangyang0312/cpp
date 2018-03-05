#include<stdio.h>

void main(){
	char string[100]={0};
	int i=0,j=0,m,n=0,a;
	char c;
	gets(string);
	while((c=string[i])!='\0'){
		if(c<'0'||c>'9'){
			for(j=0;string[i+1+j]<'0'||string[i+1+j]>'9';j++){
				printf("%c",string[i+j]);
			}
			n=string[i+j+1]-48;
			for(m=1;string[i+j+1+m]>='0'&&string[i+j+1+m]<='9';m++){
				n=n*10+string[i+j+1+m]-48;
			}
			for(a=0;a<n;a++){
				printf("%c",string[i+j]);
			}
		}
		else break;
		i=i+1+j+m;
	}
	printf("\n");
}