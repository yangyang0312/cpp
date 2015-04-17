#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
enum{IN=1,OUT=0};

typedef struct 
{
       char word[100];
	   int count;
}KEY;
void sum(KEY p[],int m)
{
     int i,n;
     for(i=0;i<m;++i)
           p[i].count=1;
	 for(i=0;i<m;++i)
		 for(n=i+1;n<m;++n)
		 {
			 if(strcmp(p[i].word,p[n].word)==0)
			 {
				   ++(p[i].count);
			       p[n].word[0]='\0';
			 }
		 }
	 printf("单词数量\n");
     for(i=0;i<m;++i)
		 if(p[i].word[0]!='\0')printf("%s--%d\n",p[i].word,p[i].count);
}
void chati(KEY p[],int m,char a[],char b[])
{
            int i,found=0;
			for(i=0;i<m;++i)
				if(strcmp(p[i].word,a)==0)
				{
					strcpy(p[i].word,b);found=1;
				}
           if(found==0)printf("no find\n");
}
int main()
{
    FILE *fp;
	KEY keytable[1024];
	int n,i=0,j=0,state=OUT;
	char c,str[1024],a[1024],b[1024];
	if((fp=fopen("English.txt","r"))==NULL)
	{
	      printf("wrong\n");
		  exit(0);
	}
	while(!feof(fp))
	{
	       c=fgetc(fp);
		   if(isspace(c)||c==-1)
		   {
			   if(state==IN){state=OUT;str[i]='\0';i=0;strcpy(keytable[j].word,str);++j;
			   }
		   }
		   else{state=IN;str[i]=c;++i;
		   }
	}
    for(n=0;n<j;++n)
		printf("%s%c",keytable[n].word,n==j-1 ?'\n':' ');

	printf("输入要查找的单词\n");gets(a);
	printf("输入要将其替换为\n");gets(b);
	chati(keytable,j,a,b);
    for(n=0;n<j;++n)
		printf("%s%c",keytable[n].word,n==j-1 ?'\n':' ');
	sum(keytable,j);
return 0;
}
