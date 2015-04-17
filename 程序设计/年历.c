#include<stdio.h>

int leapyear(int year)
{
    if(year%4==0&&year%100!=0||year%400==0)return 1;
    else return 0;
}                      //闰年判断

int daysconclude(int year)
{
    int i,leap=0;
    if(year>=2000)
    {
        for(i=2000;i<year;i++)
        {
            if(leapyear(i))leap++;
        }
        return ((6+(((year-2000)*365+leap)%7))%7);
    }
    if(year<2000)
    {
        for(i=year;i<2000;i++)
        {
            if(leapyear(i))leap++;
        }
        return ((6-(((2000-year)*365+leap)%7))%7);
    }
}                        //天数差计算及第一天

int monthday(int year,int month)
{
    switch(month)
    {
        case 1:case 3:case 5:case 7:case 8:case 10:case 12:return 31;break;
        case 4:case 6:case 9:case 11:return 30;break;
        case 2:return leapyear(year)?29:28;break;
        default: return 0;break;
    }
}                            //每月天数计算

void print(int year)
{
    int i=0,j=0,k,l;
    for(i=1;i<=12;i++)
    {
        printf("\n");
        printf("                        %d月份                        \n",i);
        printf("\n");
        printf("星期一  星期二  星期三  星期四  星期五  星期六  星期日\n");
        if(i==1)
        {
            k=daysconclude(year);
        }
        for(l=1;l<k;l++)
        {
            printf("        ");
        }
        for(j=1;j<=monthday(year,i);j++)
        {
            if(j<10)
            {
                printf("  %d     ",j);
            }
            else printf("  %d    ",j);
            if(k%7==0)
            {
                printf("\n");
                k=k%7;
            }
            k++;
        }
        printf("\n");
    }
}                   //年历打印部分

int main()
{
    while(1)
    {
        printf("请输入年份：");
        int year=0;
        scanf("%d",&year);
        print(year);
    }
    return 0;
}
