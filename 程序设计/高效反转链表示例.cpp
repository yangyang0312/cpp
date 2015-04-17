#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
struct ListNode
{
	int i;
	struct ListNode*next;
};
ListNode* ReverseList(ListNode* pHead)
{
	if (!pHead)
		return pHead;
	ListNode*p = pHead, *q = pHead->next;
	pHead->next = NULL;
	while (q)
	{
		pHead = q;
		q = q->next;
		pHead->next = p;
		p = pHead;
	}
	return pHead;
}
ListNode*build(int *c, int n)
{
	ListNode*p = (ListNode*)malloc(sizeof(ListNode)), *T;
	T = p;
	int i = 0;
	for (; i < n; ++i)
	{
		p->i = c[i];
		if (i == n - 1)
			p->next = NULL;
		else
		{
			p->next = (ListNode*)malloc(sizeof(ListNode));
			p = p->next;
		}
	}
	return T;
}
void print(ListNode*T)
{
	while (T)
	{
		cout << T->i << " ";
		T = T->next;
	}
	cout << endl;
}
int main()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7 };
	int n = sizeof a / sizeof(int);
	ListNode*T = build(a, n);
	print(T);
	T = ReverseList(T);
	print(T);
	getchar();
	getchar();
	return 0;
}