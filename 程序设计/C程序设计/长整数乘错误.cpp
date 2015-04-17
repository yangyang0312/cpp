#include<stdio.h>
int main(){
	int i,m,n,b[1024];
    printf("注意：请用数组表示一个长整数（只用输入数字长度n，以及个位数即可）\n");
	printf("输入长整数的长度n\n");scanf("%d",&n);
	printf("请输入各位数字\n");
	for(i=n;i>=1;--i)
		scanf("%d",&b[i]);
	b[0]=n;
	printf("请输入要乘的整数\n");
	scanf("%d",&m);
	for(i=n;i>=2;--i)
		printf("%d*10^%d+",b[i]*m,i-1);
	printf("%d\n",b[1]*m);
	return 0;
}
