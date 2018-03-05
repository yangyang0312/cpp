#include <stdio.h>
#include<string.h>

int main()
{
    while(1)
    {
        char a[1000]= {0},b[100]= {0};
        scanf("%s%s",a,b);
        int i=0,j=0;
        for(; i<strlen(a); )
        {
            if(a[i]==b[j])
            {
                ++i;
                ++j;
            }
            else
            {
                i=i-j+1;
                j=0;
            }
            if(j>=strlen(b))
            {
                printf("%d\n",i-j+1);
                break;
            }
        }
    }
    return 0;
}
