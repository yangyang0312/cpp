#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
typedef struct list
{
    int num;
    struct list *next;
} Node,*List;
int main(int agc,char **agv)
{
    List p,head;
    p=(List)malloc(sizeof(Node));
    head=p;
    cout<<"please enter five numbers!"<<endl;
    for(int i=0; i<5; ++i)
    {
        int n;
        cin>>n;
        p->num=n;
        p->next=(List)malloc(sizeof(Node));
        if(4==i)p->next=NULL;
        else p=p->next;
    }
    cout<<endl;
    p=head;
    while(p!=NULL)
    {
        cout<<p->num<<endl;
        p=p->next;
    }
	getchar();
	getchar();
    return 0;
}
