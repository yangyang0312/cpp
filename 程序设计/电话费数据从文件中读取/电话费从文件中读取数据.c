#include<stdio.h>
#include<string.h>

void dianhuafei(void)
{
    char a[25];
    int i,sum=0;
    FILE *p;
    p=fopen("fee.txt","r");
    while(fgets(a,25,p)!=NULL)
    {
        if(a[0]=='O')
        {
            int n=0;
            for(i=0;i<strlen(a);i++)
            {
                if(a[i]>='0'&&a[i]<='9')
                {
                    n=n*10+(a[i]-'0');
                }
            }
            sum+=n;
        }
    }
    fclose(p);
    printf("电话费计算成功！电话费M为%.2f元.\n",(sum%180)==0?0.17*sum/180:0.17*((int)(sum/180)+1));
}

int main()
{
    dianhuafei();
    return 0;
}
