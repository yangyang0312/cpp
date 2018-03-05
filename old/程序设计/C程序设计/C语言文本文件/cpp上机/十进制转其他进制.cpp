#include <stdio.h>
#include <string.h>
	void erjinzhi2(long a,long x){
	long i,jieguo[16]={0};	
			for (i = 15; i >= 0; i--)
			{
				jieguo[i] = a% x;
				a /= x;
			}
			for (i = 0; i < 16; i++)
			{				printf("%ld ", jieguo[i]);
			}
			printf("\n");
			}
void erjinzhi(char c[],long x)
{
		long chang, a, i, j, jieguo[16] = { 0 };
		chang = strlen(c);
		for (j = 0; j < chang; j++)
		{
			a = c[j];
			for (i = 15; i >= 0; i--)
			{
				jieguo[i] = a % x;
				a /= x;
			}
			for (i = 0; i < 16; i++)
			{				printf("%ld ", jieguo[i]);
			}
			printf("\n");
		}
	}
main()
{
	char a[1024] = { 0 };
	long b,c,d;
	printf("请输入转换进制:");
	scanf("%ld",&d);	printf("1.字符串\n2.数字\n请选择:");
	scanf ("%ld",&b);
	switch(b){
	case 1:
	printf("请输入:");
	scanf("%s", &a);
	erjinzhi(a,d);
	break;
	case 2:
	printf("请输入:");
	scanf("%ld", &c);
	erjinzhi2(c,d);
	break;
	default:main();
	}
	main();
}
