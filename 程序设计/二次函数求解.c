#include<stdio.h>
#include<math.h>

void fun(void)
{
    START:
    printf("请输入待求解的二次方程的系数a、b、c(分别为二次，一次和常数项系数)：");
    double a,b,c;
    scanf("%lf%lf%lf",&a,&b,&c);
    if(a==0)
    {
        if(b==0)
        {
            if(c==0)
            {
                printf("方程的解为任意数值。\n");
            }
            else
            {
                printf("输入有误，因为等式不可能成立，请检查后重新输入。\n");
                goto START;
            }
        }
        else
        {
            printf("方程的解为：%lf\n",-c/b);
        }
    }
    else
    {
        if((b*b-4*a*c)<0)printf("该方程无解。\n");
        else if((b*b-4*a*c)==0)printf("方程仅有一个解，其解为：%lf\n",-b/(2*a));
        else printf("方程有两个解，分别为 %lf 和 %lf \n",-((b+sqrt(b*b-4*a*c))/(2*a)),(-b+sqrt(b*b-4*a*c))/(2*a));
    }
}

int main()
{
    while(1)
    {
        fun();
    }
    return 0;
}
