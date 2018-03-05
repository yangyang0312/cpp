#include <stdio.h>

void caidan();
void sushupanduan();
void main();
void gong();
void paixu();
void jiecheng();
void jisuanqi();
void jia();
void jian();
void cheng();
void chu();
void chengfang();
void main();
void an();
void jinzhizhuanhuan();
void fujinzhi();
void shujinzhi();
void yanghuisanjiao();
void yanghui();
void caidan()
{
	printf
		("1.素数判断\n2.最小公倍数与最大公约数\n3.排序\n4.阶乘\n5.简易计算器\n6.十进制转换\n7.杨辉三角\n请选择:");
	int a;
	scanf("%d", &a);
	switch (a)
	{
	case 1:
		sushupanduan();
		break;
	case 2:
		gong();
		break;
	case 3:
		paixu();
		break;
	case 4:
		jiecheng();
		break;
	case 5:
		jisuanqi();
		break;
	case 6:
		jinzhizhuanhuan();
		break;
	case 7:
		yanghuisanjiao();
		break;
	default:
		caidan();
	}
	caidan();
}


int sushu(int shu)
{

	if (shu % 1 == 0 && shu > 1)
	{
		for (int i = 2; i <= shu; i++)
		{
			if (shu % i == 0 && shu != i)
			{
				return 0;
				break;
			}
			if (shu % i == 0 && shu == i)
			{
				return 1;
			}
		}
	}
}


void sushupanduan()
{
	long d;
	int a, b;
	printf("请输入一个大于1的整数(0结束):");
	scanf("%d", &a);
	if (a == 0)
	{
		caidan();
	}
	else
	{
		b = sushu(a);
		if (b == 1)
		{
			printf("%d是素数！\n", a);
		}
		else
		{
			printf("%d不是素数！\n", a);
		}
	}
}

void main()
{
	printf("       数学工具\n          王茂斌\n");
	caidan();
}




void gong()
{
	long aa, bb, cc, dd, d, i;
	printf("请输入两个数，以空格隔开(0结束):");
	scanf("%ld%ld", &aa, &bb);
	if (aa != 0 && bb != 0)
	{
		if (aa > bb)
		{
			cc = aa;
			dd = bb;
		}
		else
		{
			cc = bb;
			dd = aa;
		}
		for (long ff = 1; ff <= cc; ff++)
		{
			i = ff * cc;
			if (i % dd == 0)
			{
				printf("%d与%d的最小公倍数是%d\n", aa, bb, i);
				break;
			}
		}
		for (long gg = dd;; gg--)
		{
			if (cc % gg == 0 && dd % gg == 0)
			{
				printf("%d与%d的最大公约数是%d\n", aa, bb, gg);
				gong();
			}
		}
	}
	else
	{
		caidan();
	}
}


void paixu()
{
	int a[10000], b;
	long d;
	printf("请输入要排序的数字，以0结束\n");
	for (b = 0; b < 10000; b++)
	{

		scanf("%d", &a[b]);
		if (a[b] == 0)
		{
			break;
		}

	}
	printf("从大到小顺序为:");
	for (int c = 0; c < b; c++)
	{
		for (int d = 0; d < b - 1; d++)
		{
			if (a[d] < a[d + 1])
			{
				int e = a[d];
				a[d] = a[d + 1];
				a[d + 1] = e;
			}
		}
	}
	for (int f = 0; f < b; f++)
	{
		printf("%d  ", a[f]);
	}
	printf("\n");
	printf("1.继续\n2.退出\n请选择:");
	scanf("%ld", &d);
	switch (d)
	{
	case 1:
		paixu();
	case 2:
		caidan();
	default:
		caidan();
	}
}

void jiecheng()
{
	long a, c = 1, d;
	printf("请输入想要阶乘的数:");
	scanf("%ld", &a);
	for (long b = 1; b <= a; b++)
	{
		c *= b;
	}
	printf("%ld!=%ld\n", a, c);
	printf("1.继续\n2.退出\n请选择:");
	scanf("%ld", &d);
	switch (d)
	{
	case 1:
		jiecheng();
	case 2:
		caidan();
	default:
		caidan();
	}
}

void jia(long double a, long double b)
{
	char cc;
	printf("=%g\n", a + b);
	an();
}

void jian(long double a, long double b)
{
	char cc;
	printf("=%g\n", a - b);
	an();
}

void cheng(long double a, long double b)
{
	char cc;
	printf("=%g\n", a * b);
	an();
}

void chu(long double a, long double b)
{
	char cc;
	printf("=%g\n", a / b);
	an();
}

void chengfang(long double a, long double b)
{
	char cc;
	printf("=%g\n", pow(a, b));
	an();
}

long double a, b;
char c;
void an()
{
	scanf("%lf%c%lf", &a, &c, &b);
	switch (c)
	{
	case '+':
		jia(a, b);
		break;
	case '-':
		jian(a, b);
		break;
	case '*':
		cheng(a, b);
		break;
	case '/':
		chu(a, b);
		break;
	case '^':
		chengfang(a, b);
		break;
	case 'n':
		caidan();
	default:
		an();
	}
}

void jisuanqi()
{
	printf
		("本计算器能计算算简单的“+-*/^”\n当运算符为n时结束！\n");
	an();
}

void shujinzhi(long a, long x)
{
	printf("%ld转为16位%ld进制:", a, x);
	long i, jieguo[16] = { 0 };
	for (i = 15; i >= 0; i--)
	{
		jieguo[i] = a % x;
		a /= x;
	}
	for (i = 0; i < 16; i++)
	{
		printf("%ld ", jieguo[i]);
	}
	printf("\n");
}

void fujinzhi(char c[], long x)
{
	long chang, a, i, j, jieguo[16] = { 0 };
	chang = strlen(c);
	for (j = 0; j < chang; j++)
	{
		a = c[j];
		printf("%c转为16位%ld进制:", c[j], x);
		for (i = 15; i >= 0; i--)
		{
			jieguo[i] = a % x;
			a /= x;
		}
		for (i = 0; i < 16; i++)
		{
			printf("%ld ", jieguo[i]);
		}
		printf("\n");
	}
}

void jinzhizhuanhuan()
{
	char a[1024] = { 0 };
	long b, c, d;
	printf("请输入转换进制:");
	scanf("%ld", &d);
	printf("1.字符串\n2.数字\n3.退出\n请选择:");
	scanf("%ld", &b);
	switch (b)
	{
	case 1:
		printf("请输入:");
		scanf("%s", &a);
		fujinzhi(a, d);
		break;
	case 2:
		printf("请输入:");
		scanf("%ld", &c);
		shujinzhi(c, d);
		break;
	case 3:
		caidan();
	default:
		jinzhizhuanhuan();
	}
	jinzhizhuanhuan();
}

void yanghuisanjiao()
{
	long a;
	printf("请输入想要输出的行数(0结束):");
	scanf("%ld", &a);
	if (a == 0)
	{
		caidan();
	}
	else
	{
		yanghui(a);
		yanghuisanjiao();
	}
}

void yanghui(long a)
{
	long i, j;
	long double s[1000][1000] = { 0 };
	for (i = 0; i < a; i++)
	{
		printf("第%-2ld行:", i + 1);
		for (j = 0; j <= i; j++)
		{
			if (j == 0 || j == i)
			{
				s[i][j] = 1;
			}
			else
			{
				s[i][j] = s[i - 1][j - 1] + s[i - 1][j];
			}
			printf("%g ", s[i][j]);
		}
		printf("\n");
	}
}
