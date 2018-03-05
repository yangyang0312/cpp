#include<stdio.h>
int main()
{
    int n,i,cold=0,hot=0,suit=0;
    double avg=0.0;
    scanf("%d",&n);//get data num
    for(i=1;i<=n;i++)
    {
        int temp;
        scanf("%d",&temp);//get temperature data
        avg+=temp;
        if(temp>=30)hot++;
        if(temp<15)cold++;
        else suit++;
        printf("%.2f\n",avg);
    }
    avg/=n;
    printf("cold day is %d\nhot day is %d\nsuitble day is %d\naverage temperature is %.2f\n",cold,hot,suit,avg);
return 0;
}
