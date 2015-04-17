#include <stdio.h>
#include<math.h>
#include<iostream>
#include<time.h>
using namespace std;
int main()
{
    double begin,end;
    const int M=2000000;
	int i,j,co=1,N=M*2+1;
	bool a[M];
	for(i=0;i<M;++i)a[i]=1;
    cout<<"2  ";
    float s=sqrt(N);begin=clock();
    for (i=3;i<=s;i+=2)
    {
        if(a[(i-1)/2-1]==1)
        {
            for(j=(i*i-1)/2-1;j<M;j+=i)a[j] = 0;//去除掉所有素数的倍数
        }
    }
    for(i=0;i<M;++i)if(a[i]==1)
    {
        printf("%d  ",(i+1)*2+1);
        ++co;//素数数量统计
    }end=clock();
    cout<<endl;
    printf("%d\n",co);
    cout<<end-begin<<endl;
    return 0;
}
