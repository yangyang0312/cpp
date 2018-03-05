#include<iostream>
using namespace std;
//编写一个程序，用同一个函数名对几个数据进行从小到大排序，数据类型可以是整型、浮点型。用重载函数实现

void fun(int *a,int i)
{
    int n=0,j=0;
    for(n=0;n<i;++n)
    {
        for(j=0;j<i;++j)
        {
            if(a[n]>a[j])
            {
                int t=a[n];
                a[n]=a[j];
                a[j]=t;
            }
        }
    }
    for(n=0;n<i;++n)cout<<a[n]<<" ";
    cout<<endl;
}
void fun(double *a,int i)
{
    int n=0,j=0;
    for(n=0;n<i;++n)
    {
        for(j=0;j<i;++j)
        {
            if(a[n]>a[j])
            {
                double t=a[n];
                a[n]=a[j];
                a[j]=t;
            }
        }
    }
    for(n=0;n<i;++n)cout<<a[n]<<" ";
    cout<<endl;
}

int main()
{
    double a[100];int i=0;
    while(cin>>a[i])++i;
    fun(a,i);
    return 0;
}
