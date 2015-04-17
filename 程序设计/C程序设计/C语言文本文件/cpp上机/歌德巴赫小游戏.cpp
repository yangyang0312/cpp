#include <stdio.h>

int kaishi();
int renji();
int renren();
int shu1, shu2, aa, bb;
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

void gdbh(int aa)
{
	for (int i = 2;; i++)
	{
		if (sushu(i) == 1 && sushu(aa - i) == 1)
		{
			printf("%d %d\n", i, aa - i);
			break;
		}
	}
}

void pshu()
{
	printf("             player lose!\n");
	if (shu2 != 0)
	{
		printf("正确答案为:");
		gdbh(shu2);
	}
	printf
		("		restart?\n           1.是    2.返回主菜单\nplease make a choice:");
	int replay;
	scanf("%d", &replay);
	if (replay == 1)
	{
		renji();
	}
	if (replay == 2)
	{
		kaishi();
	}
	if (replay != 1 && replay != 2)
	{
	}
}

void p1shu()
{
	printf("             player1 lose!\n");
	if (shu2 != 0)
	{
		printf("正确答案为:");
		gdbh(shu2);
	}
	printf
		("          restart?\n           1.是    2.返回主菜单\nplease make a choice:");
	int replay;
	scanf("%d", &replay);
	if (replay == 1)
	{
		renren();
	}
	if (replay == 2)
	{
		kaishi();
	}
	if (replay != 1 && replay != 2)
	{
	}
}

void p2shu()
{
	printf("             player2 lose!\n正确答案为:");
	gdbh(shu1);

	printf
		("          restart?\n           1.是    2.返回主菜单\nplease make a choice:");
	int replay;
	scanf("%d", &replay);
	if (replay == 1)
	{
		renren();
	}
	if (replay == 2)
	{
		kaishi();
	}
	if (replay != 1 && replay != 2)
	{
	}
}

int renren()
{
	printf("player1请输入一个大于等于4的偶数:");
	scanf("%d", &shu1);
	if (shu1 < 4 || shu1 % 2 != 0)
	{
		shu2 = 0;
		p1shu();
	}
	else
	{
		for (int i = 1;; i++)
		{
			if (i % 2 == 1)
			{
				printf("player2请输入结果:");
				scanf("%d %d", &aa, &bb);
				if (sushu(aa) != 1 || sushu(bb) != 1 || aa + bb != shu1)
				{
					p2shu();
				}
				else
				{
					printf
						("请player2输入一个大于player1输入的数的偶数:");
					scanf("%d", &shu2);
					if (shu2 <= shu1 || shu2 % 2 != 0)
					{
						p2shu();
					}
				}
			}
			if (i % 2 == 0)
			{
				printf("player1请输入结果:");
				scanf("%d %d", &aa, &bb);
				if (sushu(aa) != 1 || sushu(bb) != 1 || aa + bb != shu2)
				{
					p1shu();
				}
				else
				{
					printf
						("请player1输入一个大于player2输入的数的偶数:");
					scanf("%d", &shu1);
					if (shu1 <= shu2 || shu1 % 2 != 0)
					{
						p1shu();
					}
				}
			}
		}
	}
	return 0;
}

int renji()
{
	printf("player1请输入一个大于等于4的偶数:");
	scanf("%d", &shu1);
	if (shu1 < 4 || shu1 % 2 != 0)
	{
		shu2 = 0;
		pshu();
	}
	else
	{
		for (int i = 2;; i++)
		{
			printf("电脑给出的答案为:");
			gdbh(shu1);
			shu2 = shu1 + 2;
			printf("电脑给出的问题为:%d\n", shu2);
			printf("player请输入结果:");
			scanf("%d %d", &aa, &bb);
			if (sushu(aa) != 1 || sushu(bb) != 1 || aa + bb != shu2)
			{
				pshu();
			}
			else
			{
				printf
					("请player输入一个大于电脑输出的数的偶数:");
				scanf("%d", &shu1);
				if (shu1 <= shu2 || shu1 % 2 != 0)
				{
					pshu();
				}
			}
		}
		return 0;
	}
}

int kaishi()
{
	int jin;
	printf("1.双人对战\n2.人机对战\n3.退出\nplease make a choice:");
	scanf("%d", &jin);
	if (jin == 1)
	{
		renren();
	}
	if (jin == 2)
	{
		renji();
	}
	if (jin != 1 && jin != 2)
	{
	}
	return 0;
}
main()
{
	printf
		("               歌德巴赫小游戏\n                     制作人:王茂斌\n歌德巴赫猜想:任一大于2的偶数都可写成两个素数之和\n规则:由一方给出一个大于等于4的偶数，另一方写出它的哥德巴赫猜想结果,两质数以空格分离\n");
	kaishi();
}
