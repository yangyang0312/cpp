#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct list//struct part
{
    int xi;
    int zhi;
    struct list *next;
}Node,*List;
List input(void)//to get data
{
    List head=NULL,p,tail=NULL;
    cout<<"请输入系数和指数(输入非数字字符结束)："<<endl;
    while(1)   //creat list from it's tail
    {
        int a,b;
        if(scanf("%d%d",&a,&b)==2)  //make sure it's type is int
        {
            p=(List)malloc(sizeof(Node));//malloc
            p->xi=a;
            p->zhi=b;         //data
            if(head==NULL)head=p;  //creat the head of the list
            else tail->next=p;//link node p to tail
            tail=p;//make p to tail
        }
        else
        {
            while(getchar()!='\n');
            break;
        } //data copelete
    }
    if(tail!=NULL)tail->next=NULL;//tail->next =null
    return head;//create compelete
}
List add(List head1,List head2)
{
    List p=head1,q=head2;
    while(p&&q)
    {
        if(p->zhi>q->zhi)
        {
            List r=p->next;
            p->next=q;
            q=q->next;
            p->next->next=r;
            p=r;
        }
        else if(p->zhi==q->zhi)//if zhi is same
        {
            p->xi+=q->xi;//add xi
            p=p->next;
            List r=q;
            q=q->next; //p q to next
            free(r);
        }
        else p=p->next;  //not same ,p to next
    }
    p=head1;
    while(p->next)p=p->next;
    if(q)p->next=q;
    free(head2);
    return head1;
}
int main(int _Argc,char **agv)
{
    List h1,h2,h3,p;
    h1=input();
    h2=input();
    h3=add(h1,h2);
    p=h3;
    while(p->next!=NULL)
    {
        cout<<p->xi<<"x^"<<p->zhi<<"+";
        p=p->next;
    }
    cout<<p->xi<<"x^"<<p->zhi<<endl;
	return 0;
}
