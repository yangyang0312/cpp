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
int main(int agc,char **agv)
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
	getchar();
	getchar();
    return 0;
}
