#include<iostream>
using namespace std;
//编写一个程序，用同一个函数名对几个数据进行从小到大排序，数据类型可以是整型、浮点型。用重载函数实现
template <class T>
void fun(T *a,int i)
{
    int n=0,j=0;
    for(n=0;n<i;++n)
    {
        for(j=0;j<i;++j)
        {
            if(a[n]>a[j])
            {
                T t=a[n];
                a[n]=a[j];
                a[j]=t;
            }
        }
    }
    for(n=0;n<i;++n)cout<<a[n]<<" ";
    cout<<endl;
}
template <class T>
void input(T *t)
{
    int i=0;
    while(cin>>t[i])++i;
    fun(t,i);
}

int main()
{
    int a[100];
    double b[100];
    input(a);
    return 0;
}
