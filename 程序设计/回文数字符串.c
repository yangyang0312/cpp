#include<stdio.h>
#include <string.h>

int main()
{
    int b,c;
    printf("请输入数据组数：");
    scanf("%d",&b);
    printf("\n");
    for(c=0;c<b;++c)
    {
        int i,a[100]={0};
        printf("请输入类型，数字1代表数字类型，数字2代表字符：");
        scanf("%d",&i);
        printf("\n");
        if(i==1)
        {
            int m,j=0,k,d;
            printf("请输入数字：");                 //数字
            scanf("%d",&m);
            d=m;
            while(m>0)
            {
                a[j]=m%10;
                m/=10;
                j++;
            }
            for(k=0;k<j;k++)
            {
                if(a[k]!=a[j-k-1])
                {
                    break;
                }
            }
            if(k>=j/2)printf("数字%d是回文数\n",d);
            else printf("数字%d不是回文数\n",d);
        }
        if(i==2)
        {
            printf("请输入字符串：");
            char d[100]={0},e[100]={0};
            scanf("%s",&d);
            int j,k=strlen(d);
            putchar('\n');
            for(j=0;j<k;j++)
            {
                e[j]=d[k-j-1];
            }
            if(strcmp(e,d)==0)printf("字符串%s是回文数\n",d);
            else printf("字符串%s不是回文数\n",d);
        }
    }
    return 0;
}
