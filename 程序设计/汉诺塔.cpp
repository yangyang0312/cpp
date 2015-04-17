#include<stdio.h>

unsigned int i=0;

void move(char from,char to)
{
    i++;
    printf("%c-->%c     %d\n",from,to,i);
}

void henoi(int n,char from,char to,char by)
{
    if(1==n)move(from,to);
    else
    {
        henoi(n-1,from,by,to);
        move(from,to);
        henoi(n-1,by,to,from);
    }
}

int main()
{
    while(1)
    {
        i=0;
        int n;
        scanf("%d",&n);
        henoi(n,'a','b','c');
        putchar('\n');
    }
    return 0;
}
