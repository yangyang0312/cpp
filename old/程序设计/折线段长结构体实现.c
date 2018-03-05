#include<stdio.h>
#include<math.h>
#define MAXPOINT 100                    //定义点的数量

typedef struct
{
    double x;
    double y;
}point;                                  //结构体定义

int input(point p[])
{
    int n=0;
    printf("请输入点的坐标，不必加括号：\n");
    while(scanf("%lf%lf",&p[n].x,&p[n].y)==2)n++;
    return n;
}                                        //输入函数

double polylength(point p[],int n)
{
    int i=0;
    double length=0.0;
    for(;i<n-1;i++)
    {
        length+=sqrt(pow((p[i+1].x-p[i].x),2.0)+pow((p[i+1].y-p[i].y),2.0));
    }
    return length;
}                                         //折线段长度计算函数

void output(double length)
{
    printf("折线段长度为:%.4f\n",length);
}                                         //输出函数

int main()
{
    point p[MAXPOINT];
    int count=input(p);
    output(polylength(p,count));
    return 0;
}                                            //主函数
