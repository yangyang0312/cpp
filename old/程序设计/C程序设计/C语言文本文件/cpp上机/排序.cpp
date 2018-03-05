#include <stdio.h>

void main()
{
	int a[10000], b;
	for (b = 0; b < 10000; b++)
	{
		scanf("%d", &a[b]);
		if (a[b] == 0)
		{
			break;
		}
	}
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
}
