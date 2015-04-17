#include<stdio.h>
#include<stdio.h>

int pan(double a,double b,double c)
{
    if((a+b)>c&&(b+c)>a&&(a+c)>b)return 1;
    else
    {
        printf("输入错误，不能构成三角形！\n");
        return 0;
    }
}

void rec(void)
{
    double a,b,c;
    printf("请输入三角形的三条边：");
    scanf("%lf%lf%lf",&a,&b,&c);
    double s=(a+b+c)/2;
    if(pan(a,b,c))
    {
        printf("以%.2f,%.2f,%.2f为边的三角形面积为%lf：\n",a,b,c,sqrt(s*(s-a)*(s-b)*(s-c)));
    }
}

int main()
{
    while(1)rec();
    return 0;
}
