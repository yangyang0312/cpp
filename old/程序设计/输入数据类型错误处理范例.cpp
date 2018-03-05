#include <stdio.h>

int main(int argc, char *argv[])
{
    int i=0;
    while (scanf("%d", &i)!=1)
    {
        printf("输入数据类型错误！\n请重新输入数据：");
        while(getchar()!='\n');   //输入缓冲区在输入处理错误时会将数据停留在缓冲区，getchar（）将错误的信息“吃掉”
    }
    for(;i<10;++i)printf("%d",i);
    return 0;
}
//中文编码为UTF-8
