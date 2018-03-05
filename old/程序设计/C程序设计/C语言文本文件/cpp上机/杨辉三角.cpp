#include <stdio.h>
void yanghui();
void main();
void main(){
long a;
printf("请输入想要输出的行数:");
scanf("%ld",&a);
yanghui(a);
main();
}
void yanghui(long a){
long  i,j;
long double s[1000][1000]={0};
for(i=0;i<a;i++){
printf("第%-2ld行:",i+1);
for(j=0;j<=i;j++){
if(j==0||j==i){
s[i][j]=1;
}
else{
s[i][j]=s[i-1][j-1]+s[i-1][j];
}
printf("%g ",s[i][j]);
}
printf("\n");
}
}