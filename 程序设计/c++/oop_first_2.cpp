#include<iostream>
using namespace std;
//对3个变量按由小到大顺序排序，要求使用变量的引用。
void sort(int &a,int &b);

int main()
{
    int a,b,c;
    cin>>a>>b>>c;
    sort(a,b);
    sort(a,c);
    sort(b,c);
    cout<<a<<" "<<b<<" "<<c<<endl;
    return 0;
}

void sort(int &a,int &b)
{
    int t=a;
    if(b<a)
    {
        a=b;
        b=t;
    }
}
