#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main()
{
    FILE *fp,*np;
	int n,i,j=0;
	char c,str[1024],a[1024],b[1024],A[26];
	if((fp=fopen("English.txt","rb"))==NULL)
	{
	      printf("wrong\n");
		  exit(0);
	}
	if((np=fopen("1.txt","w"))==NULL)
	{
	      printf("wrong\n");
		  exit(0);
	}
    for(i=0;i<26;++i)A[i]=0;
	while(!feof(fp))
	{
       if(isalpha(c= fgetc(fp)))
	   {
	      c=tolower(c);
          ++A[c-'a'];
	   }		  
	}
	printf("字母数量\n");
	for(i=0;i<26;++i)
		printf("%c--%d ",'a'+i,A[i]);
	printf("\n输入要查找的字符串\n");
	rewind(fp);
	gets(a);
	printf("将其替换为：\n");
	gets(b);
	n=strlen(a);
	while(!feof(fp))
	{
		fseek(fp,j*sizeof(char),0);++j;
	      fgets(str,n+1,fp);
		  if(strcmp(str,a)==0)
		  {
			  strcpy(str,b);
		      fputs(str,np);
			  j=j-1+n;
		  }
		  else fputc(str[0],np);
	}
	printf("操作成功，在1.txt中查看\n");
	fclose(fp);
	fclose(np);
return 0;
}
