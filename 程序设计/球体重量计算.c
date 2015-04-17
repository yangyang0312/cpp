#include<stdio.h>
#include<math.h>
#define PI 3.1415926

int main()
{
   int a,b;
   double c,d;
   printf("请输入铁球和金球的直径（单位毫米）：");
   scanf("%d%d",&a,&b);
   c=pow((a/2000.0),3)*PI*(4.0/3.0)*7860000;
   d=pow((b/2000.0),3)*PI*(4.0/3.0)*19300000;
   printf("铁球的质量为%.3f克\n金球质量为%.3f克\n",c,d);
return 0;
}
