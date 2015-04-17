#include<stdio.h>

int main()
{
    int n,i=1,b;
    n=rand()%100;
    printf("这是一个有趣的小游戏.\n由系统产生一个一百以内的随机数。\n你有十次机会猜中数字，次数越少分数越高哦！\n我们开始吧！！！\n");
    while(i<11)
    {
        printf("请输入您猜测的数：");
        scanf("%d",&b);
        if(n>b)printf("您输入的数字有点小哦！\n");
        if(n<b)printf("您输入的数字有点大哦！\n");
        if(n==b)
        {
            printf("真厉害，%d次就猜中了!\n正确的数字就是%d啦!\n",i,n);
            break;
        }
        i++;
    }
    printf("您的分数是：%d分\n",100-(i-1)*10);
    return 0;
}
