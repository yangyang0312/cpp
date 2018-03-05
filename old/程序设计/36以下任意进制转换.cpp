#include<stdio.h>
#include<math.h>
#include<string.h>                 //36进制以下
void fun(int in,int out,int sum,char a[]);    //转换函数
int main()
{
    while(1)
    {
        int i,j,k;
        char a[100]={0};
        printf("输入数进制：");
        scanf("%d",&i);
        getchar();
        printf("请输入数据：");
        scanf("%s",a);
        printf("转换数进制：");
        scanf("%d",&j);
        k=strlen(a);
        fun(i,j,k,a);
    }
    return 0;
}
void fun(int in,int out,int sum,char a[])
{
    int k;
    long temp=0;
    for(k=0;k<sum;++k)
    {
        if(a[sum-k-1]>='A'&&a[sum-k-1]<='Z')a[sum-k-1]=a[sum-k-1]-'A'+'9'+1;  //A到Z的值接到‘9’的后面
        temp+=(a[sum-k-1]-'0')*pow(in,k);   //转换为10进制数，long存储
    }
    k=0;
    while(1)
    {
        a[k]=temp%out;
        temp/=out;
        if(temp==0)break;
        ++k;              //十进制转换为其他任意进制
    }
    for(in=k;in>=0;--in,--k)
    {
        if(a[in]>=0&&a[in]<=9)printf("%d",a[in]);
        else if(a[in]>=10&&a[in]<=25)printf("%c",a[in]+55);   //打印部分
        if(k%4==0)printf(" ");       //每四个值输出一个空格
    }
    putchar('\n');
}
//yangyang
