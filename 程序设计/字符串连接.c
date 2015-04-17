#include<stdio.h>

void *fun(char *a,char *s)
{
    int i=0,j=0;
    while(a[i]!='\0')i++;
    while(s[j]!='\0')
    {
        a[i++]=s[j++];
        a[i]='\0';
    }
    return a;
}                           //s[]连接到a[]后边

int main()
{
    char a[100]={0},s[50]={0};
    scanf("%s",a);
    scanf("%s",s);
    fun(a,s);
    printf("%s\n",a);
    return 0;
}
