#include <stdio.h>
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


int acm2(int a)
{
	int bu = 0;
	printf("\n1=%d", a);
  g:
	if (a != 1)
	{
		if (sushu(a) == 1)
		{
			printf("÷%d", a);
			a /= a;
			bu++;
		}
		else
		{
			if (sushu(a - 1) == 1)
			{
				printf("-1)");
				a -= 1;
				bu++;
				goto g;
			}

			for (int i = a - 2;; i--)
			{
				if (sushu(i) == 1)
				{
					if (a % i == 0)
					{
						printf("÷%d)", i);
						a /= i;
						bu++;
						goto g;
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}

		}
	}
	else
	{
		return bu;
	}
}

int shu1, shu2;
void main()
{
	int jieguo = 0;
	scanf("%d%d", &shu1, &shu2);
	for (int j = shu1; j <= shu2; j++)
	{
		jieguo += acm2(j);
	}
	printf("\n共有%d步\n", jieguo);
	main();
}
