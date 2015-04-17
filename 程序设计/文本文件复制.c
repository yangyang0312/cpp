#include<stdio.h>

void copy(void)
{
    START:;
    FILE *in,*out;
    char infile[20]={0},outfile[20]={0};
    printf("请输入需要复制的文本文件：");
    scanf("%s",infile);
    printf("复制到：");
    scanf("%s",outfile);
    in=fopen(infile,"r");
    out=fopen(outfile,"w");
    if(in==NULL)
    {
        printf("文件文件%s打开失败，请重试。\n",infile);
        goto START;
    }
    if(out==NULL)
    {
        printf("文本文件%s打开失败，请重试。\n",outfile);
        goto START;
    }
    char c;
    while((c=fgetc(in))!=EOF)
    {
        fputc(c,out);
    }
    fclose(in);
    fclose(out);
    printf("文本文件复制成功，请在%s中查看。\n",outfile);
}

int main()
{
    copy();
    return 0;
}
