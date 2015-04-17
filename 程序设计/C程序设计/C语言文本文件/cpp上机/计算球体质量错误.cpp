#include <stdio.h>
int main(){  
      int a,b;
      float m,n;
      scanf("%d%d",&a,&b);
      double pi=3.1415926;       m=(4.0/3.0)*pi*(a*a*a/1000.0)*7.86/8.0;
    n=(4.0/3.0)*pi*(a*a*a/1000.0)*19.3/8.0;
     printf("%.3lf %.3lf\n",m,n);
     return 0;
}
