#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

double keybordsound(void)
{
    double start=0.0,finish=0.0;
    char ch[1000];
    int i=0;
    for(;i<100000;i++)
    {
        ch[i]=getchar();
        switch(ch[i])
        {
            case 'z':Beep(262*2,500);break;
            case 'x':Beep(294*2,500);break;
            case 'c':Beep(330*2,500);break;
            case 'v':Beep(349*2,500);break;
            case 'b':Beep(392*2,500);break;
            case 'n':Beep(440*2,500);break;
            case 'm':Beep(494*2,500);break;
            default :break;
        }
    }
    return 0;
}

int main()
{
    keybordsound();
    return 0;
}
