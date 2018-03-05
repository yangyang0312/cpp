#include<stdio.h>
#include<string.h>

int main()
{
    printf("请输入字符串！\n");
    char a[100]={0},b[100]={0},c[]="***end***";
    int m,n;
    while(1)
    {
        gets(a);
        n=strlen(a);
        m=strlen(b);
        if(strcmp(a,c)==0)
        {
            break;
        }
        if(n>m)
        {
            strcpy(b,a);
        }
    }
    puts(b);
    printf("最长行长度为：%d",m);
    return 0;
}
