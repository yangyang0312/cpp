#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
typedef struct list
{
	int num;
	struct list *next;
}node,*link;
link  linklist(void)//链表建立函数
{
	link tail,p,head;
    tail=(link)malloc(sizeof(node));
    tail->next=NULL;
    head=tail;
    p=tail;
    cout<<"please enter five numbers!"<<endl;
    for(int i=0;;++i)
    {
	    int n;
	    cin>>n;
    	head->num=n;
	    if (4==i)break;
	    head=(link)malloc(sizeof(node));
		head->next=p;
		p=head;
	}
	cout<<endl;
	p=head;
	while (p)
	{
		cout<<p->num<<endl;
		p=p->next;
	}
	return head;
}
link lianjie(void)//链表连接函数
{	
	link p,q,r;
	p=linklist();
	q=linklist();
	r=p;
	p=p->next;
	while(p)p=p->next;
	p=q;
	p=q->next;
	while(p)p=p->next;
	return r;
}
int main(int agc,char **agv)
{
	link head=lianjie(),p;
	p=head;
	while (p)
	{
		cout<<p->num<<endl;
		p=p->next;
	}
	getchar();
	getchar();
    return 0;
}//链表1和链表2都是逆序的，所以最终链接输出的链表也会是逆序的。。
