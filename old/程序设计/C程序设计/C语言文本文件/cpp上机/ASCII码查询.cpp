#include <stdio.h>
#include <string.h>
void erjinzhi(char c)
{
		long a, i, j, jieguo[16] = { 0 };
			a = c;
			for (i = 15; i >= 0; i--)
			{
				jieguo[i] = a % 2;
				a /= 2;
			}			printf("十六位二进制代码:");
			for (i = 0; i < 16; i++)
			{				printf("%ld", jieguo[i]);
			}
			printf("\n");
		}
	
int main(){
char a;
int b;
scanf("%c",&a);
b=a;
printf("字符:%c十进制代码:%-3d十六进制代码:%-4x八进制代码:%-4o",b,b,b,b);
erjinzhi(a);
main();
}
