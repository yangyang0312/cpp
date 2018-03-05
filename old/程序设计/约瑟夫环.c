#include<stdio.h>

int main()
{
    int i,j=0,sum=0,m,n,a[100]={0};
    printf("请输入人的个数及初始随机数：");
    scanf("%d %d",&n,&m);
    if(n>0&&n<101&&m>0&&m<99999999)
    {
        for(i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]<1||a[i]>99999998)
            {
                printf("数据输入错误！");
                main();
            }
        }
        for(i=0;i<n&&sum<n+1;i++)
        {
            if(a[i]!=0)
            {
                j++;
            }
            if(j==m)
            {
                printf("%d ",i+1);
                m=a[i];
                a[i]=0;
                sum++;
                j=0;
            }
            if(i==n-1)
            {
                i=-1;
            }
        }
    }
    else
    {
        printf("数据输入错误！\n");
        main();
    }
    printf("\n");
    return 0;
}
