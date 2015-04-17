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

void main()
{
	int a, b;
	scanf("%d", &a);
	b = sushu(a);
	if (b == 1)
	{
		printf("yes!\n");
	}
	else
	{
		printf("no!\n");
	}
	main();
}
