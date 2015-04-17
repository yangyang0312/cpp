#include<stdio.h>
#include<windows.h>
#include<string.h>

void print(int n)
{
    int j;
    char c[20]={0};
    int i=rand()%10;
    sprintf(c,"color %d%d",i,4);
	system(c);
    Sleep(50);
    for(j=0;j<n;j++)printf("     **   **     ");printf("\n");
    for(j=0;j<n;j++)printf("   *    *    *   ");printf("\n");
    for(j=0;j<n;j++)printf("   *         *   ");printf("\n");
    for(j=0;j<n;j++)printf("     *     *     ");printf("\n");
    for(j=0;j<n;j++)printf("        *        ");printf("\n");
}

void fun(void)
{
    int i=1;
    while(i)
    {
        print(i);
        Sleep(1000);
        i++;
        if(i>4)
        {
            i=-1;printf("ÎÒ°®Äã!");
        }
        printf("\n");
    }
}

int main()
{
    char a[20]={0};
    scanf("%s",a);
    if(strcmp("woaini",a)==0)
    {
        while (1)fun();
    }
    return 0;
}
