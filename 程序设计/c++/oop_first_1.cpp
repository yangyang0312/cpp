#include<iostream>
using namespace std;
//求2个数或3个正整数中的最大数，用带有默认参数的函数实现。
int max(int a,int b,int c=0);

int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    if(a>0&&b>0&&c>0)cout<<max(a,b,c)<<endl<<max(a,b)<<endl;
    return 0;
}

int max(int a,int b,int c)
{
    if(b>a)a=b;
    if(c>a)a=c;
    return a;
}
