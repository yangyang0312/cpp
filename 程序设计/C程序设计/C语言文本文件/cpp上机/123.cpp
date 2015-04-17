#include <stdio.h>
#include <string.h>
#include <math.h>

char a[100]={0},aa[100]={0};
int chang;
main ()
{
	for(;;)
	{	
		gets(a);
		if (a[0]==' ')
		{
			break;
		}
		else{
			int	c=0;
			char b[100]={0};
			int i=0;
			chang=strlen(a);
			for (i=0;i<chang;i++)
			{
				if (a[i]<='9'&&a[i]>='0')
				{
					b[c]=a[i];
					c++;
				}
			}
			c=strlen(b);
			chang=0;
			for (i=0;i<c;i++)
			{
				chang+=(pow(10,c-i-1))*((int)b[i]-48);
			}
			for (i=chang-1;;i--)
			{
				if(i==1)
				{
					printf("%d\n",chang);
					break;
				}
				if (chang%i==0)
				{
					if (i<0){printf("0\n");
					break;
					}
					else{
						printf("%d\n",i);
						break;
					}
				}
			}
		}
	}
}
