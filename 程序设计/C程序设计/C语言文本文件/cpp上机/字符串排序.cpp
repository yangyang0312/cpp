#include <stdio.h>
#include <string.h>
 main()
{
	int i, j, chang;
	char a[1024] = { 0 }, b;
	scanf("%s", a);
	chang = strlen(a);
	for (i = 0; i < chang; i++)
	{
		for (j = 0; j < chang - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				b = a[j];
				a[j] = a[j + 1];
				a[j + 1] = b;
			}
		}
	}
	printf("%s\n", a);
}
