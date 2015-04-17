#include<stdio.h>
#include<string.h>

int main()
{
    int n,i,a[100]={0},b[100]={0};
    printf("请输入数据数量：");
    scanf("%d",&n);
    printf("\n");
    if(n<=100&&n>0)
    {
        for(i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]<-32768||a[i]>32767)
            {
                printf("输入数据错误！\n");
                break;
            }
        }
        int j,k,max;
        for(i=0,j=0;i<n;i++)
        {
            if(a[i]%2==0)
            {
                b[j]=a[i];
                j++;
            }
            k=j;
        }
        for(i=0,j=k;i<n;i++)
        {
            if(a[i]%2==1)
            {
                b[j]=a[i];
                j++;
            }
        }
        for(i=0;i<k-1;i++)
        {
            for(j=i;j<k;j++)
            {
                if(b[j]>b[i])
                {
                    max=b[j];
                    b[j]=b[i];
                    b[i]=max;
                }
            }
        }
        for(i=k;i<n-1;i++)
        {
            for(j=i;j<n;j++)
            {
                if(b[j]>b[i])
                {
                    max=b[j];
                    b[j]=b[i];
                    b[i]=max;
                }
            }
        }
    }
    else printf("数据数量输入错误！\n");
    for(i=0;i<n;i++)
    {
        printf("%d  ",b[i]);
    }
    printf("\n");
    return 0;
}
