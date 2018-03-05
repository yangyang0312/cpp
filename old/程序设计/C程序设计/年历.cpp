#include<stdio.h>
#include<stdio.h>
#include<math.h>

int isleayear(int year){
          return  year%4==0&&year%100!=0||year%400==0;
}                                                                             //闰年判断
int NUM(int year,int k){
	int x;
	 if(k==0||k==2||k==4||k==7||k==9||k==11)x=31;
     if(k==3||k==5||k==6||k==8||k==10)x=30;
	 if(isleayear(year)&&k==1)x=29;
	 if(isleayear(year)==0&&k==1)x=28;
	return x;
}                                                                             //判断每月天数

int main(){
       int n,k,year,m,i,j; 
	   char mon[12][12]={"一月","二月","三月","四月","五月","六月","七月","八月","九月","十月","十一月","十二月"};
	   printf("输入年份\n");
	   scanf("%d",&year);
	   if(isleayear(year)==1 || year<2000)
	     n=(int)(fabs(year-2000)*365+(int)fabs(year-2000)/4)%7;                //判断某年一月一号为星期几
	   else
         n=(int)(fabs(year-2000)*365+(int)fabs(year-2000)/4+1)%7;
	   if(year<2000)n=7-n;                                                     //当年份小于2000是一月一号星期几
	   for(k=0;k<12;++k){
	      printf("%s\n日 一 二 三 四 五 六\n",mon[k]);
          if(n==0) n+=7;
		  else 
			  if(n==8)
				  n=1;
	      m=1;
		  for(j=0;j<n-1;++j)					
			  printf("   ");
		  for(j=n-1;j<7;++j){
			  printf("%2d%c",m,j==6? '\n': ' ');
			  m=m+1;
		  }	
		  for(i=1;i<=5;++i){
			  for(j=0;j<7&&m<=NUM(year,k);++j){
			  	   printf("%2d%c",m,j==6? '\n': ' ');
				   m=m+1;
                   if(m-1==NUM(year,k)){n=j+2;printf("\n");break;}                //输出年历
			  }
		  }
		 }
return 0;
}
