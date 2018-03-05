#include<stdio.h>
#include<string.h>

void zuichanghang(void)
{
    FILE *p;
    int i=0,n=0;
    char a[100]={0},b[100]={0};
    p=fopen("line.txt","r");
    while(fgets(a,100,p)!=NULL)
    {
        i=strlen(a);
        if(n<i)
        {
            n=i;
            strcpy(b,a);
        }
    }
    fclose(p);
    printf("文件中最长行长度为：%d\n",n);
    puts(b);
    putchar('\n');
    printf("%d",'\n');
}

int main()
{
    zuichanghang();
    return 0;
}
