#include <math.h>
#include <stdio.h>
int shui(int a)
{
	int b = a, c = 1000, i, j, k = 0;
	for (i = 3;; i++)
	{
		if (a < c)
		{
			for (j = 0; j < i; j++)
			{
				k += pow((b % 10), i);
				b /= 10;
			}
			if (a == k)
			{
				return 1;
				break;
			}
			else
			{
				return 0;
				break;
			}
		}
		else
		{
			c *= 10;
		}
	}
}

main()
{
	int a, i, b, c,j;
	scanf("%d", &a);
	for (i = 0; i < a; i++)
	{
		scanf("%d%d", &b, &c);
		for (j= b; j< c + 1; j++)
		{
			if (shui(j) == 1)
			{
				printf("%d\n", j);
			}
		}
	}
}
