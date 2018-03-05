#include<stdio.h>

void zifu(void)
{
    FILE *p;
    int letter=0,number=0,space=0,other=0,i=0;
    char c;
    p=fopen("1.txt","r");
    if(p==NULL)
    {
        printf("文件未能成功打开！\n");
    }
    else
    {
        while((c=fgetc(p))!=EOF)
        {
            if(c>='a'&&c<='z'||c>='A'&&c<='Z')letter++;
            else if(c>='0'&&c<='9')number++;
            else if(c==' ')space++;
            else other++;
        }
        printf("在文件1.txt中字母有%d个\n数字%d个\n空格%d个\n其他字符有%d个\n文件中共有字符%d个",letter,number,space,other,letter+number+space+other);
    }
    fclose(p);
}

int main()
{
    zifu();
    return 0;
}
