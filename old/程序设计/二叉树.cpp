#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct BitNode
{
    char data;
    struct BitNode *lchild,*rchild;
}BitNode,*BitTree;
void createBitTree(BitTree &T)//构造二叉树
{
    char ch;
    cin>>ch;
    if(ch=='.')T=NULL;
    else
    {
        T=(BitTree)malloc(sizeof(BitNode));
        T->data=ch;
        createBitTree(T->lchild);
        createBitTree(T->rchild);
    }
}
void preOrder(BitTree T)//先序遍历
{
    if(T)
    {
        cout<<T->data<<"  ";
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}
void inOrder(BitTree T)//中序遍历
{
    if(T)
    {
        inOrder(T->lchild);
        cout<<T->data<<"  ";
        inOrder(T->rchild);
    }
}
void lastOrder(BitTree T)//后序遍历
{
    if(T)
    {
        lastOrder(T->lchild);
        lastOrder(T->rchild);
        cout<<T->data<<"  ";
    }
}
void display(BitTree &T)//括号表示
{
    if(T)
    {
        cout<<T->data;
        if(T->lchild||T->rchild)
        {
            cout<<"(";
            display(T->lchild);
            if(T->rchild)
            {
                cout<<",";
                display(T->rchild);
                cout<<")";
            }
        }
    }
}
int main()
{
    BitTree T;
    createBitTree(T);
    cout<<"先序：";
    preOrder(T);
    cout<<endl<<"中序：";
    inOrder(T);
    cout<<endl<<"后序：";
    lastOrder(T);
    cout<<endl<<"括号表示：";
    display(T);
    cout<<endl;
    return 0;
}
