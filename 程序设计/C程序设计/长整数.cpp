#include <stdio.h>
#include <string.h>

int main(){
	int i;
	char cchang[10000];
	int chang[10000];
	printf("请输入一个长整数:");
	scanf("%s",cchang);
	chang[0]=strlen(cchang);
	for(i=0;i<chang[0];i++){
		chang[i+1]=cchang[chang[0]-i-1]-'0';
	}
	int a;
	printf("请输入一个整数，与之相乘:");
	scanf("%d",&a);
	int de[10000];
	int temp=0;
	de[0]=chang[0];
	for(i=0;i<chang[0];i++){
		de[i+1]=(chang[i+1]*a+temp)%10;
		temp=(chang[i+1]*a+temp)/10;
	}
	de[chang[0]+1]=temp;
	if(temp>0)de[0]++;
	for(i=de[0];i>0;i--){
		printf("%d",de[i]);
	}
	printf("\n");
	return 0;
}