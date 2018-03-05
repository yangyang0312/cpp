#include<stdio.h>
#include<math.h>

int shuixianhua(int n,int a)
{
    int sum=0,k=n;
    while(n>0)
    {
        sum+=pow(n%10,a);
        n/=10;
    }
return sum==k;
}

int main()
{
    int a,n;
    printf("请输入大于等于3的位数:");
    scanf("%d",&a);
    for(n=pow(10,a-1);n<=pow(10,a)-1;n++)if(shuixianhua(n,a))printf("%d is a shuixianhuashu\n",n);
return 0;
}
