#include<stdio.h>

int main()
{
    printf("请输入方阵行列数m：");
    int i,j,m;
    scanf("%d",&m);
    int a[20][20]={0},b[52]={0};
    printf("请输入方阵：");
    for(i=0;i<m;++i)
    {
        for(j=0;j<m;++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    for(i=0;i<m;++i)
    {
        for(j=0;j<m;++j)
        {
            b[i]+=a[i][j];
        }
    }
    for(j=0;j<m;++j)
    {
        for(i=0;i<m;++i)
        {
            b[m+j]+=a[i][j];
        }
    }
    for(i=0;i<m;++i)
    {
        b[2*m]+=a[i][i];
        b[2*m+1]+=a[i][m-i];
    }
    printf("\n");
    int max,k;
    for(i=0;i<2*m+1;++i)
    {
        for(j=i;j<=2*m+1;++j)
        {
            max=b[i];
            if(b[j]>max)
            {
                max=b[j];
                k=j;
                max=b[i];
                b[i]=b[k];
                b[k]=max;
            }
        }
    }
    for(i=0;i<=2*m+1;++i)
    {
        printf("%d  ",b[i]);
    }
    printf("\n");
    return 0;
}
