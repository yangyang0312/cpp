#include<stdio.h>
#include<string.h>
#include<math.h>

int main()
{
    int n,m;
    printf("请输入数据组数：");
    scanf("%d",&n);
    for(m=0;m<n;m++)
    {
        printf("请输入数据：");
        char s[100]={0};
        int a[100]={0};
        gets(s);
        int j,l=0;
        for(j=0;j<strlen(s);j++)
        {
            if(s[j]>='0'&&s[j]<='9')
            {
                a[l]=s[j]-48;
                l++;
            }
        }
        int h=0,i;
        for(j=0;j<l;j++)
        {
            h+=a[l-j-1]*pow(10,j);
        }
        for(i=2;i<=sqrt(h);i++)
        {
            if(h%i==0)
            {
                break;
            }
        }
        if(i<=sqrt(h))
        {
            printf("%d\n",h/i);
        }
        else printf("%d\n",h);
    }
    return 0;
}
