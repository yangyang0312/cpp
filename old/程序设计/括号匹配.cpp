#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
	int n,i=0;
	cout<<"请输入数量"<<endl;
	cin>>n;
	for(i=0;i<n;++i)
	{
		int flag=1;
		cout<<"请输入表达式"<<endl;
		char a[100]={0},b[100]={0};
		cin>>a;
		int l=strlen(a),k=0;
		for(int j=0;j<l;++j)
		{
			if('('==a[j]||'['==a[j]||'{'==a[j])
			{
				b[k]=a[j];
				++k;
			}
			else if(')'==a[j]||']'==a[j]||'}'==a[j])
			{
				--k;
				if (k<0)
				{
				    flag=0;
					break;
				}
				if(')'==a[j]&&'('==b[k]||']'==a[j]&&'['==b[k]||'}'==a[j]&&'{'==b[k])b[k]=0;
				else 
				{
				    flag=0;
					break;
				}
			}
		}
		if(0==k&&1==flag)cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
	getchar();
	getchar();
	return 0;
}