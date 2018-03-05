#include<iostream>
#include <cstdio>
using namespace std;
class UF
{
private:
	int *p,*a,m,n,sum;//a作为输入，p为操作
public:
	UF();
	void un(int i,int j);
	void fun();
};
void UF::fun()
{
	for (int i=0;i<sum;++i)
	{
		if (1==a[i])
		{
			int row=i/n,col=i%n;//行，列
			if (row>0&&row<m&&a[i]==a[i-n])//1->m-1
				un(i-n,i);
			if(row<n-1&&row>-1&&a[i]==a[i+n])//0->m-2
				un(i,i+n);
			if(col>-1&&col<n-1&&a[i]==a[i+1])//0->n-2
				un(i,i+1);
			if(col>0&&col<n&&a[i]==a[i-1])//1->n-1
				un(i-1,i);
		}
	}
	int flag=-1,i,j;
	for (i=0;i<n;++i)
		for(j=sum-1;j>sum-n;--j)
			if(p[i]==p[j])
			{
				flag=p[i];
				goto end;
			}
    end:
	if (flag!=-1)
	{
		for (i=0;i<sum;++i)
		{
			if(flag==p[i])
				cout<<" o";
			else
				cout<<" x";
			if(i%n==n-1)
				cout<<endl;
		}
		for (int i=0;i<sum;++i)
		{
			cout<<p[i]<<" ";
			if (i%n==n-1)
				cout<<endl;
		}
	}
	else
		cout<<"无连通路径！"<<endl;
}
void UF::un(int i,int j)//两块合一
{
	int z=p[i],x=p[j];
	if(z==x)return;
	for (int k=0;k<sum;++k)
		if (p[k]==x)
			p[k]=z;
}
UF::UF()//初始化
{
	FILE *f;
	cout<<"请输入文件名：";
	char *name=new char(20);
	cin>>name;
	f=fopen(name,"r");
	if (f)
	{
		fscanf(f,"%d%d",&m,&n);
		sum=m*n;
		cout<<m<<"  "<<n<<endl;
		int *a=new int[sum];
		for(int i=0;i<sum;++i)
			fscanf(f,"%d",&a[i]);
		for(int i=0;i<sum;++i)
		{
			cout<<a[i]<<" ";
			if(i%n==n-1)
				cout<<endl;
		}
		cout<<endl;
		int *p=new int[sum];
		for (int i=0;i<sum;++i)
		{
			p[i]=i;
			cout<<p[i]<<" ";
			if (i%n==n-1)
				cout<<endl;
		}
		this->a=a;
		this->p=p;
		fclose(f);
	}
}
int main()
{
	UF uf;
	uf.fun();
	getchar();
	getchar();
	return 0;
}
