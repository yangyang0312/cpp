#include<stdio.h>
#include<string.h>

void kuohao(void)
{
   char a[100]={0};
   int i,j;
   while(gets(a))
   {
       for(i=0,j=0;i<strlen(a);i++)
       {
           if(a[i]==')'||a[i]==']'||a[i]=='}')
           {
               for(j=i;j>=0;j--)
               {
                   if(a[j]=='('||a[j]=='['||a[j]=='{')
                    {
                        if(a[i]==')'&&a[j]=='('||a[i]==']'&&a[j]=='['||a[j]=='{'&&a[i]=='}')
                        {
                            a[j]='z';
                            a[i]='z';
                            break;
                        }
                        else goto END;
                    }
               }
           }
       }
       for(i=0;i<strlen(a);i++)
       {
           if(a[i]==')'||a[i]=='('||a[i]==']'||a[i]=='['||a[i]=='{'||a[i]=='}')
           {
               END:;
               printf("no\n");
               break;
           }
       }
       if(i>=strlen(a))
       {
           printf("yes\n");
       }
    }
}

int main()
{
    kuohao();
    return 0;
}
