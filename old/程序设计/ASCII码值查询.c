#include<stdio.h>

int main()
{
    printf("请输入选项：");
    int i;
	printf("1、按ASCII码查找   2、按字符查找   3、打印ASCII码表\n");
    scanf("%d",&i);
    getchar();
    if(1==i)
    {
        int j;
        printf("请输入ASCII码值：");
        scanf("%d",&j);
        char c=j;
        if(j>=0&&j<128)printf("值为%d的字符为：%c\n",j,c);
        else
        {
            printf("输入值错误：");
            main();
        }
        main();
    }
    if(2==i)
    {
        char c;
        printf("请输入要查找的字符：");
        scanf("%c",&c);
        int j=c;
        printf("字符%c的ASCII码值为：%d\n",c,j);
        main();
    }
    if(3==i)
    {
        int j;
        for(j=0;j<128;j++)
        {
            if(j<100)printf("%d    %c    ",j,j);
            else printf("%d   %c    ",j,j);
			if(0==j%5)printf("\n");
        }
        putchar('\n');
        main();
    }
    else main();
    return 0;
}
