#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{                                                        //定义结构体
      char name[20],sex[4],phone[20],email[20],address[30];
	  int id;
	  struct node *next;
}Listnode;
typedef Listnode * Linklist;
void printf_title();                                                        //函数申明
int menu();
int slect_menu();
Listnode *read_file();
void write_file(Linklist head);
void printf_file();
void delet_file();
void add_file();
void modify_file();
void printf_title()
{	                                                    //标题函数
	printf("\t\t\t\t通信录管理系统\n");
}

int menu()
{                                                                 //菜单函数
	  int select;
      system("cls");
	  printf_title();
	  printf("\t\t\t1.人员查询\n");
	  printf("\t\t\t2.人员增加\n");
	  printf("\t\t\t3.人员删除\n");
	  printf("\t\t\t4.人员信息修改\n");
	  printf("\t\t\t5.系统退出\n");
	  printf("\t\t\t输入要操作的功能号:");
	  scanf("%d",&select);
	  while(select<1||select>5){
	     printf("您的选择有问题，请重新输入\n");	  
		 scanf("%d",&select);
	  }
	  return select;                                                           //返回要操作的编号
}

int select_menu()
{                                                              //菜单挑选函数
       int sel=menu(),a=0;
	   switch(sel)
	   {
	   case 1:printf_file();system("PAUSE");break;
       case 2:add_file();system("PAUSE");break;
       case 3:delet_file();system("PAUSE");break;
       case 4:modify_file();system("PAUSE");break;
	   case 5:a=1;break;
	   }
	   
	   return a;
}

Listnode *read_file()
{                                                          //文件读取函数
        FILE *np;
		Listnode *p,*q,*head,A;
		head=p=NULL;
		if((np=fopen("a.txt","r"))==NULL)
			printf("wrong\n");
	    fscanf(np,"%d%s%s%s%s%s",&A.id,A.name,A.sex,A.phone,A.email,A.address);
		while(!feof(np))
		{
			p=(Listnode*)malloc(sizeof(Listnode));		
			p->id=A.id,strcpy(p->name,A.name);strcpy(p->sex,A.sex);
			strcpy(p->phone,A.phone);strcpy(p->email,A.email);strcpy(p->address,A.address);
			if(head==NULL) head=p;
			else q->next=p;
			q=p;
	        fscanf(np,"%d%s%s%s%s%s",&A.id,A.name,A.sex,A.phone,A.email,A.address);
		}
		q->next=NULL;fclose(np);
		return head;
}

void write_file(Linklist head)
{                                                //文件重新写入函数
	Linklist p=head;FILE *np;
		if((np=fopen("a.txt","w"))==NULL)
			printf("wrong\n");
		while(p!=NULL)
		{
		      fprintf(np,"%d\t%s\t\t%s\t%s\t%s\t%s\n",p->id,p->name,p->sex,p->phone,p->email,p->address);
				  p=p->next;		
		}
		fclose(np);
}

void printf_file()
{                                                              //信息查询函数
    Linklist p=read_file();system("cls");
    printf_title();
	printf("编号\t姓名\t性别\t电话\t\temail\t\t\t地址\n");
	while(p!=NULL)
	{
	      printf("%d\t%s\t%s\t%s\t%s\t%s\n",p->id,p->name,p->sex,p->phone,p->email,p->address);
		  p=p->next;
	}
}

void delet_file()
{                                                             //人员删除函数
      int i,n=1;
	  Linklist head,p=read_file(),q=p;head=p; 
      printf_file();
	  printf("请输入要删除的人员编号\n");scanf("%d",&i);
      while(p!=NULL)
	  {
          if(i==p->id)
			  if(n==1)
			  {
				  head=p->next;break;
			  }
			  else break;	 
	       q=p;
		   p=p->next; 
		   ++n;
	  }
	  q->next=p->next;
	  printf("删除成功\n");
      write_file(head);
}

void add_file()
{                                                         //人员添加函数
      Linklist head,p=read_file(),q;
	  head=p;
      printf_file();
	  printf("输入要添加的人员的信息\n");		
	  q=(Listnode*)malloc(sizeof(Listnode));
	  scanf("%d%s%s%s%s%s",&q->id,q->name,q->sex,q->phone,q->email,q->address);
      while(1)
	  {
		   if(p->next!=NULL)p=p->next;
		   else {p->next=q;break;
		   }
	  }
	  q->next=NULL;
	  printf("添加成功\n");
      write_file(head);
}

void modify_file()
{
      Linklist head,p=read_file(),q,f;
	  int i;
	  head=p;
      printf_file();
	  printf("输入要修改的人员的编号\n");
	  scanf("%d",&i);
	  while((i!=p->id)&&p!=NULL
		  ){
		  f=p;p=p->next;
	  }
	  printf("输入修改后的信息\n");
	  q=(Listnode*)malloc(sizeof(Listnode));
	  scanf("%d%s%s%s%s%s",&q->id,q->name,q->sex,q->phone,q->email,q->address);
      if(i==head->id){head=q;q->next=p->next;
	  }
	  else{f->next=q;q->next=p->next;
	  }
	  printf("修改成功\n");
	  write_file(head);
}


int main()
{
	int a;
	while(a!=1)
	  a=select_menu();
	printf("\t\t\t退出成功\n");
return 0;
}
