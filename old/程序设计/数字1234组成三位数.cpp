#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<string.h>
using namespace std;
/*题目：有1、2、3、4个数字，
能组成多少个互不相同且无重复数字的三位数？
都是多少？*/
int main(int agc,char **agv)
{
    int sum=0;
    for(int i=1;i<5;++i)
    {
        for(int j=1;j<5;++j)
        {
            for(int k=1;k<5;++k)
            {
                if(i!=j&&j!=k&&k!=i)
                {
                    cout<<i<<j<<k<<endl;//三重循环遍历所有情况，输出挑选结果
                    ++sum;
                }
            }
        }
    }
    cout<<sum<<endl;
    return 0;
}
