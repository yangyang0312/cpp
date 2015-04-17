#include<stdio.h>
#include<math.h>

int isprime(int n)
{
    int i;
    for(i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)break;
    }
    return i>sqrt(n)?1:0;
}

int main()
{
    int m,i;
    printf("请输入数据组数：");
    scanf("%d",&m);
    if(m>0&&m<100)
    {
        for(i=0;i<m;++i)
        {
            int n;
            printf("请输入数据：");
            scanf("%d",&n);
            if(n>2&&n%2==0)
            {
                int a;
                for(a=2;;++a)
                {
                    if(isprime(a)&&isprime(n-a))break;
                }
                printf("%d=%d+%d\n",n,a,n-a);
            }
            else printf("输入有误，请输入大于2的偶数。\n");
        }
    }
return 0;
}
