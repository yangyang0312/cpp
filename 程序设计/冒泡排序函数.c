#include<stdio.h>
#define MAX 100
int bublesort(int a[])
{
    int i=0,n,j,t,flag=0;
    printf("请输入待排序数据，输入非数字字符是表示结束：\n");
    while(scanf("%d",&a[i]))i++;
    n=i;
    for(i=0;i<n-1;i++)
    {
        flag=0;
        for(j=i;j<n;j++)
        {
            if(a[i]>a[j])
            {
                t=a[i];
                a[i]=a[j];
                a[j]=t;
                flag=1;
            }
        }
        if(flag==0)break;
    }
    for(i=0;i<n;i++)
    {
        printf("%d  ",a[i]);
    }
    putchar('\n');
}

int main()
{
    int a[MAX];
    bublesort(a);
    return 0;
}
