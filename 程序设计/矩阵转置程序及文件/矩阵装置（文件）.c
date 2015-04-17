#include<stdio.h>
#define MAXROW 10
#define MAXCOL 10

void fun()
{
    FILE *p;
    int i,j,row,col,a[MAXROW][MAXCOL];
    p=fopen("in.txt","r");
    if(p==NULL)
    {
        printf("未知错误，输入文件打开失败！\n");
    }
    fscanf(p,"%d%d",&row,&col);
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            fscanf(p,"%d",&a[i][j]);
        }
    }
    fclose(p);
    p=fopen("out.txt","w");
    if(p==NULL)
    {
        printf("未知错误，输出文件打开失败！\n");
    }
    fprintf(p,"%d %d",col,row);
    fprintf(p,"\n");
    for(j=0;j<col;j++)
    {
        for(i=0;i<row;i++)
        {
            fprintf(p,"%d ",a[i][j]);
        }
        fprintf(p,"\n");
    }
    fclose(p);
    printf("操作成功，矩阵已成功转置！请在文件out.txt中查看！");
}

int main()
{
    fun();
    return 0;
}
