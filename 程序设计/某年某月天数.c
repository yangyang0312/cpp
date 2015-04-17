#include<stdio.h>

int main()
{
    printf("请输入数据组数：");
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;++i)
    {
        printf("请输入年份：");
        int year,month;
        scanf("%d",&year);
        printf("请输入月份：");
        scanf("%d",&month);
        putchar('0');
        switch(month)
        {
            case 1:case 3:case 5:case 7:case 8:case 10:case 12:
            printf("%d年%d月有31天\n",year,month);
            break;
            case 4:case 6:case 9:case 11:
            printf("%d年%d月有30天\n",year,month);
            break;
            case 2:
            if(year%4==0&&year%100!=0||year%400==0)
            printf("%d年%d月有28天\n",year,month);
            else printf("%d年%d月有29天\n",year,month);
            break;
            default:
            printf("输入有误\n");
            break;
        }
    }
    return 0;
}
