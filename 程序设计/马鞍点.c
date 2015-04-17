#include<stdio.h>

int main()
{
    int min,m,n,k,i,j,l,a[100][100]={0};
    printf("请输入矩阵行列值：");
    scanf("%d%d",&m,&n);
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        scanf("%d",&a[i][j]);
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            min=a[i][j];
            for(k=0;k<n;k++)
            {
                if(a[i][k]<min)
                {
                    break;
                }
            }
            for(l=0;l<m;l++)
            {
                if(a[l][j]>min)
                {
                    break;
                }
            }
            if(k>=n&&l>=m)
            {
                printf("方阵%d行%d列数字%d是马鞍点！\n",i+1,j+1,a[i][j]);
            }
        }
    }
    return 0;
}
