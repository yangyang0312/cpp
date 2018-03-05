#include<stdio.h>

int main()
{
    int n,i;
    printf("请输入数据组数:");
    scanf("%d",&n);
    if(n>0&&n<100)
    {
    for(i=1;i<=n+1;++i)
    {
        double sum,fee;
        scanf("%lf",&sum);
        if(sum>=0&&sum<=110)fee=sum*0.5;
        if(sum>110&&sum<=210)fee=(sum-110)*0.55+55;
        if(sum>210)fee=(sum-210)*0.7+110;
        printf("电费分别为%.2f\n",fee);
    }
    }
return 0;
}
