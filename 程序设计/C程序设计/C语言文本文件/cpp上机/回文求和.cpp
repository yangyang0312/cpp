#include <stdio.h>
#include <string.h>
char c[1024] = { 0 }, d[1024] =

{
0};

int main()
{
	int i, x = 0;
	scanf("%s", &c);
	int b = strlen(c);
	for (i = 0; i < b; i++)
	{
		d[i] = c[b - 1 - i];
	}
	if (strcmp(c, d) == 0)
	{
		for (i = 0; i < b; i++)
		{
			x += (c[i] - 48);
		}
		printf("%s回文\n各项之和为%d", c, x);
	}
	else
	{
		printf("%s不回文", c);
	}
}
