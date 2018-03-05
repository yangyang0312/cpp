#include<stdio.h>

void shudu(void)
{
    int i,j,flag,a[9][9]={0};
    FILE *p;
    char s[20]={0};
    printf("请输入数独文件名：");
    scanf("%s",s);
    p=fopen(s,"r");
    if(p==NULL)printf("数独文件打开失败，请重试！\n");
    else
    {
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                fscanf(p,"%d",&a[i][j]);                  //文件读取
            }
        }
        while(1)
        {
            flag=0;
            for(i=0;i<9;i++)
            {
                for(j=0;j<9;j++)
                {
                    if(a[i][j]==0)
                    {
                        int k=0,l=0,c[9]={0};
                        for(k=0;k<9;k++)
                        {
                            if(a[k][j]!=0)c[a[k][j]-1]=a[k][j];        //遍历列
                        }
                        for(l=0;l<9;l++)
                        {
                            if(a[i][l]!=0)c[a[i][l]-1]=a[i][l];         //遍历行
                        }
                        for(k=(i/3)*3;k<(i/3)*3+3;k++)
                        {
                            for(l=(j/3)*3;l<(j/3)*3+3;l++)
                            {
                                if(a[k][l]!=0)c[a[k][l]-1]=a[k][l];      //遍历大九宫格
                            }
                        }
                        int sum=0;
                        for(k=0;k<9;k++)
                        {
                            if(c[k]==0)
                            {
                                sum++;                                //检查行、列、九宫格数
                                l=k;
                            }
                        }
                        if(sum==1)
                        {
                            a[i][j]=l+1;            //行、列、九宫格是否差一个
                            flag=1;
                        }
                    }
                }
            }
            if(0==flag)break;
        }
        fclose(p);
        p=fopen("soduke.txt","w");
        if(p==NULL)
        {
            printf("输出文件打开失败，请重试！\n");
        }
        else
        {
            for(i=0;i<9;i++)
            {
                for(j=0;j<9;j++)
                {
                    fprintf(p,"%d ",a[i][j]);                     //输出文件
                }
				fprintf(p,"\n");
            }
            printf("请在soduke.txt中查看数独解！\n");
        }
    }
    fclose(p);
}

int main()
{
    shudu();                                                 //主函数调用
    return 0;
}
