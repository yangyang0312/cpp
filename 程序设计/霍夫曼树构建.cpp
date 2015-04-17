#include <iostream>
using namespace std;
typedef struct HFTree
{
	double num;
	struct HFTree *left,*right;
}HFTNode,*HF;
HF connect(HF h,HF t)//两棵树链接为一棵树
{
	HF p;
	p=new HFTNode;
	p->num=(h->num)+(t->num);
	p->left=h;
	p->right=t;
	return p;
}
void preview(HF t)//先序遍历树
{
	if(t)
	{
		cout<<t->num<<endl;
		preview(t->left);
		preview(t->right);
	}
}
int main()
{
	int n;
	cout<<"输入数据数量："<<endl;
	cin>>n;
	cout<<"请输入数据：";
	HF *h=new HF[n];
	for (int i=0;i<n;++i)
	{
		double temp;
		cin>>temp;
		h[i]=new HFTNode;//建立节点
		h[i]->num=temp;
		h[i]->left=NULL;
		h[i]->right=NULL;
	}
	int max=0,root=0;
	for (int i=0;i<n;++i)
		if (h[max]->num>h[i]->num)
			max=i;
	int *flag=new int[n];//标志数组，辅助寻找最小的两个数
	for (int i=0;i<n;++i)
		flag[i]=0;
	for(int i=1;i<n;++i)
	{
		int min=0,j=0;
		for (j=0;j<n;++j)
			if (0==flag[j])
			{
				root=j;
				break;
			}//初始未用过的树
		for (j=0;j<n;++j)
			if(flag[j]==0&&h[root]->num>h[j]->num)
				root=j;//最小的树
		for (j=0;j<n;++j)
			if (0==flag[j]&&j!=root)
			{
				min=j;
				break;
			}//初始未用过的树
		for (j=0;j<n;++j)
			if (flag[j]==0&&j!=root&&h[j]->num<h[min]->num)
				min=j;//第二小的树
		flag[min]=1;
		cout<<"root:"<<root<<" "<<min<<endl;
		h[root]=connect(h[root],h[min]);//连接两棵树，小树作为根
	}
	preview(h[root]);//先序输出
	cout<<endl<<endl;
	getchar();
	getchar();
	return 0;
}