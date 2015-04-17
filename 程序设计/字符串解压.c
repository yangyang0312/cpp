#include<stdio.h>
#include<string.h>

int main()
{
    char a[50]={0},b;
    int n,i,j=0,k;
    printf("ÇëÊäÈëÑ¹ËõºóµÄ×Ö·û´®£º");
    gets(a);
    for(i=0;i<strlen(a);i++)
    {
        if(a[i]<'0'||a[i]>'9')
        {
            if(a[i+1]>'0'&&a[i+1]<='9')
            {
                if(a[i+2]>='0'&&a[i+2]<='9')
                {
                    n=10*(a[i+1]-'0')+(a[i+2]-'0');
                }
                else n=a[i+1]-'0';
            }
            else n=1;
        }
        for(j=0;j<n;j++)
        {
            printf("%c",a[i]);
        }
        if(n>1)
        {
            i++;
            if(n>9)
            {
                i++;
            }
        }
    }
    printf("\n");
    return 0;
}
