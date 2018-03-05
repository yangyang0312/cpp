#include<stdio.h>
#include<string.h>

void jiema(void)
{
	int i=0,j=0;
    char c[20]={0},d[20]={0},b[20]={0};
    printf("请输入您要解密的字符串：");
    scanf("%s",c);
    printf("请输入密码：");
    scanf("%s",b);
    for(i=0,j=0;i<strlen(c);i++)
    {
        d[i]=c[i]-(b[j]-'0');
		j++;
        if(j>=strlen(b))j=0;
    }
    printf("解密后字符串为：");
	puts(d);
}

void jiami(void)
{
    int i=0,j=0;
	char c[20]={0},d[20]={0},b[20]={0};
    printf("请输入您要加密的字符串：");
    scanf("%s",c);
    printf("请输入不超过20位的密码：");
    scanf("%s",b);
    for(i=0,j=0;j<strlen(c);j++)
    {
        d[j]=c[j]+(b[i]-'0');
		i++;
		if(i>=strlen(b))i=0;
    }
    printf("加密后的字符串为：");
	puts(d);
}

void select(void)
{
    int n;
    printf("1、加密     2、解密\n");
    printf("请输入您的选项：");
    scanf("%d",&n);
	getchar();
    if(n==1)jiami();
    if(n==2)jiema();
}

int main()
{
    while(1)
    {
        select();
    }
    return 0;
}
