#include<stdio.h>
#include<string.h>
void main(){
	char a[100]={0},b[100]={0};
	int m,j,i;
	while(1){
		j=0;
		char a[100]={0};
		char b[100]={0};
		gets(a);
		if(a[0]==' ') break;
		for(i=0;a[i]!='\0';i++){
			if(a[i]=='{'||a[i]=='}'||a[i]=='['||a[i]==']'||a[i]=='('||a[i]==')'){
				b[j]=a[i];
				j++;
			}
		}
		if(j%2==0){
			do{m=strlen(b);
			    for(i=0;i<j;i++){
				if((b[i]=='{'&&b[i+1]=='}')||(b[i]=='('&&b[i+1]==')')||(b[i]=='['&&b[i+1]==']'))
				break;
				}
				for(;i+1<=j;i++){
					b[i]=b[i+2];
				}
				j=j-2;
			}while(m!=strlen(b));
			if(b[0]==0){
				printf("yes\n");
			}
			else printf("no\n");
		}
		else printf("no\n");
	}
}
