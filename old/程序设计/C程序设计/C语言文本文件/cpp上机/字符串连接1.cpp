#include <string.h>
#include <stdio.h>
int main()
{
	char a[30]="aaa",a2[4]="bbb";
	int i;
    strcat(a,"ccc");
	strcpy(a2,"d");
    strcat(a,a2);

	for(i=0;i<30;i++)
	{
		printf("%c",a[i]);
	}
	putchar('\n');
 for(i=0;i<2;i++)
	{
		printf("%c",a2[i]);
	}
   
		return 0;
}





