#include<stdio.h>

int main()
{
    printf("请输入华氏温度值：");
    int n;
    double h=0.0;
    scanf("%d",&n);
    h=(n-32)*5.0/9;
    printf("华氏温度%d为实时温度%.2f\n",n,h);
return 0;
}
