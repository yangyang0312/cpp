#include<stdio.h>
#include<stdlib.h>
int main(){
	FILE*fp,*out;
	char ch,str[20]={0};
	int i,a=0,b=0;
	float sum=0;
	fp=fopen("fee.txt","r");
	if(fp==NULL){
		exit(0);
	}
	while(fgets(str,20,fp)!=NULL){
        if(str[0]=='I'&&str[1]=='N'){}
		else if(str[0]=='O'&&str[1]=='U'&&str[2]=='T'){
			for(i=4,b=0;str[i]!='\n'&&str[i]!='\0';i++){
				a=str[i]-48;
			    b=b*10+a;
			}
		if(b>0&&b<86400){
		sum=sum+((b/180)+1)*0.17;
		}
		}
	}
	printf("%.2f\n",sum);
	fclose(fp);
	return 0;
}