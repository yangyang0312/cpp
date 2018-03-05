#include <stdio.h>
#include <string.h>
#include <math.h>
void jia();
void jian();
void cheng();
void chu();
void chengfang();
void main();
void an();
void jia(long double a,long double b){
char c;
printf("=%g\n",a+b);
a+=b;
j:scanf("%c%lf",&c,&b);
switch (c){
case 43:jia(a,b);
break;
case 45:jian(a,b);
break;
case '*':cheng(a,b);
break;
case '/':chu(a,b);
break;
case '^':chengfang(a,b);
break;
case 110:an();
break;
default:
goto j;
}
}

void jian(long double a,long double b){
char c;
printf("=%g\n",a-b);
a-=b;
ji:scanf("%c%lf",&c,&b);
switch (c){
case 43:jia(a,b);
break;
case 45:jian(a,b);
break;
case '*':cheng(a,b);
break;
case '/':chu(a,b);
break;
case '^':chengfang(a,b);
break;
case 110:an();
break;
default:
goto ji;
}
}
void cheng(long double a,long double b){
char c;
printf("=%g\n",a*b);
a*=b;
c:scanf("%c%lf",&c,&b);
switch (c){
case 43:jia(a,b);
break;
case 45:jian(a,b);
break;
case '*':cheng(a,b);
break;
case '/':chu(a,b);
break;
case '^':chengfang(a,b);
break;
case 110:an();
break;
default:
goto c;

}
}

void chu(long double a,long double b){
char c;
printf("=%g\n",a/b);
a/=b;
ch:scanf("%c%lf",&c,&b);
switch (c){
case 43:jia(a,b);
break;
case 45:jian(a,b);
break;
case '*':cheng(a,b);
break;
case '/':chu(a,b);
break;
case '^':chengfang(a,b);
break;
case 110:an();
break;
default:
goto ch;

}
}

void chengfang(long double a,long double b){
char c;
printf("=%g\n",pow(a,b));
a=pow(a,b);
cf:scanf("%c%lf",&c,&b);
switch (c){
case 43:jia(a,b);
break;
case 45:jian(a,b);
break;
case '*':cheng(a,b);
break;
case '/':chu(a,b);
break;
case '^':chengfang(a,b);
break;
case 110:an();
break;
default:
goto cf;

}
}

long double a,b;
char c;
void an(){
scanf("%lf%c%lf",&a,&c,&b);
switch (c){
case 43:jia(a,b);
break;
case 45:jian(a,b);
break;
case '*':cheng(a,b);
break;
case '/':chu(a,b);
break;
case '^':chengfang(a,b);
break;
default:
}
}
void main(){
printf("本计算器能计算算简单的“+-*/^”\n当运算符为n时结束！\n");
an();
}
