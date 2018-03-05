#include <stdio.h>
#include <string.h>
char c[1024] = { 0 }, d[1024] ={0};

main()
{
	scanf("%s", &c);
	int b = strlen(c);
	for (int i = 0; i < b; i++)
	{
		d[i] = c[b - 1 - i];
	}
	if (strcmp(c, d) == 0)
	{
		printf("%s回文", c);
	}
	else
	{
		printf("%s不回文", c);
	}
}
