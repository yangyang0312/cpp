#include "stdio.h"
int a, aa[3];
void main()
{
	scanf("%d %d %d", &aa[0], &aa[1], &aa[2]);
	while (aa[0] > aa[1] || aa[1] > aa[2])
	{
		if (aa[0] > aa[1])
		{
			a = aa[1];
			aa[1] = aa[0];
			aa[0] = a;
		}
		if (aa[1] > aa[2])
		{
			a = aa[1];
			aa[1] = aa[2];
			aa[2] = a;
		}
	}
	printf("%d\n", aa[1]);
}
