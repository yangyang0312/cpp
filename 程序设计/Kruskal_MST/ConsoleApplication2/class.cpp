#include <iostream>
#include "class.h"
using namespace std;
void MST::sort()//sort
{
	int i=1,j=0;
	for(i=1;i<n;++i)//insert
	{
		for (j=i;j>0&&a[j].value<a[j-1].value;--j)
		{
			struct side t=a[j];//exchange
			a[j]=a[j-1];
			a[j-1]=t;
		}
	}
}
void MST::display()//output
{
	mst();
	cout<<endl<<endl<<"Kruskal MST："<<endl;
	for(int i=0;i<m-1;++i)
	{
		cout<<"peak1: "<<ms[i].root<<"  peak2: "<<ms[i].peak<<" value: "<<ms[i].value<<endl;
	}
}
void MST::mst()//build
{
	sort();
	cout<<"After sort:"<<endl;
	for (int i=0;i<n;++i)
	{
		cout<<"peak1: "<<a[i].root<<"  peak2: "<<a[i].peak<<"  value: "<<a[i].value<<endl; //after sorted
	}
	for(int i=0,j=0;i<m-1&&j<n;++i)
	{
		while(find(flag[a[j].root])==find(flag[a[j].peak]))//root is different
			++j;
		un(a[j].root,a[j].peak);//union two tree
		ms[i]=a[j]; //add to tree
	}
}
int MST::find(int i)//find tree root
{
	while(i!=flag[i])
		i=flag[i];
	return i;
}
void MST::un(int i,int j)//union two tree,avoid circle
{
	int z=find(i),x=find(j);//find root
	if(x==z)
		return;
	flag[x]=flag[z];//union
}
MST::MST(int n,int m)//initialize
{
	this->n=n;//side
	this->m=m;//peak
	this->a=new side[n];//side
	this->ms=new side[m-1];//tree side
	this->flag=new int[m];//help build tree,avoid circle
	for (int i=0;i<n;++i)//input
	{
		cout<<"输入边两个顶点及权重： ";
		cin>>a[i].root>>a[i].peak>>a[i].value;
	}
	for(int i=0;i<m;++i)//initialize flag array
	{
		flag[i]=i;
	}
}
	/*for(int i=0;i<n;++i)
	{
		cout<<"顶点"<<i<<"的边数：";
		cin>>a[i].sum;
		cout<<"各边的值：";
		a[i].side=new side [a[i].sum];
		for(int j=0;j<a[i].sum;++j)
			cin>>a[i].side[j].peak>>a[i].side[j].value;
	}
	for (int i=0;i<n;++i)
	{
		for(int j=0;j<a[i].sum;++j)
			cout<<a[i].side[j].peak<<" "<<a[i].side[j].value<<" ";
		cout<<endl;
	}*/
/*struct side//
{
	int peak,value;
};
struct peak
{
	struct side*side;
	int sum;
};*/