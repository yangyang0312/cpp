#include <iostream>
#include <stdlib.h>
#include<cstdio>
using namespace std;
typedef struct list   //Ô¼Éª·ò»·
{
	int num;//mm
	int po;//position
	struct list *next; 
}JNode,*Jlist;
int main()
{
	int n,m;
	cin>>n>>m;
	Jlist h,p,q;
	for(int i=1;i<n+1;++i)
	{
		int temp;
		cin>>temp;
		q=(Jlist)malloc(sizeof(JNode));
		q->num=temp;
		q->po=i;
		if (i==1)
		{
			h=q;
			p=q;
		}
		p->next=q;
		p=q;
	}
	getchar();
	p->next=h;
	while (true)
	{
		if(h->next==h)
		{
			cout<<h->po<<"  ";
			break;
		}
		for (int i=1;i<m-1;++i)
		{
			h=h->next;
		}
		cout<<h->next->po<<"  ";
		p=h->next;
		h->next=p->next;
		m=p->num;
		h=h->next;
		free(p);
	}
	cout<<endl;
	getchar();
	getchar();
	return 0;
}