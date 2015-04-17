#include<stdio.h>
#include<string.h>
int m,i,j;
void main(){
   char a[20]={0},b[20]={0};
   scanf("%d",&m);
   if(m>0&&m<20){
	   for(j=0;j<m;j++){
	      scanf("%s%s",a,b);
	      for(i=0;a[i]==b[i];i++){
		      printf("%c",a[i]);
		  }
		  if(i==0) printf("no");
		  printf("\n");
	   }
   }
}