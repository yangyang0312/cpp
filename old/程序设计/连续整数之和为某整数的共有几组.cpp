#include<iostream>
//.连续整数之和为 1000 的共有几组?
using namespace std;
int main()
{
    int n,count=0;
    cout<<"input a number please!"<<endl;
    cin>>n;
    for(int i=1;;++i)
    {
        count+=i;
        if(count>=n)
        {
            count=i;
            break;
        }
    }
    for(int i=1;i<count;++i)
    {
        if(n%i==0&&i%2==1||n%i==i/2&&i%2==0)
        {
            if(i%2==1)
            {
                for(int j=n/i-i/2;j<=n/i+i/2;++j)
                    cout<<j<<" ";
                cout<<endl;
            }
            else
            {
                for(int j=n/i-i/2+1;j<=n/i+i/2;++j)
                    cout<<j<<" ";
                cout<<endl;
            }
        }
    }
    return 0;
}
