#include <stdio.h>
int fx(int a, int b, int c)
{
	a = b + c;
	return a;
}

int a, aa, bb;
main()
{
	scanf("%d", &aa);
	if (aa == 0)
	{
		printf("0\n");
	}
	if (aa == 1)
	{
		printf("1\n");
	}
	if (aa != 0 && aa != 1)
	{
		int c = 0;
		int b = 1;
		for (int i = 1; i <= aa; i++)
		{
			bb = fx(a, b, c);
			printf("%d\n", bb);
			c = b, b = bb;
		}
	}
}
