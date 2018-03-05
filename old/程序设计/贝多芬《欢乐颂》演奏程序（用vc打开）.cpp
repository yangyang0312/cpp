#include<stdio.h>
#include<windows.h>
#include<conio.h>

const unsigned PER=225;

enum{Do=262,Re=294,Mi=330,Fa=349,So=392,La=440,Xi=494};

void play(int f,int a,int t)
{
    int i=0;
    Beep((unsigned)(f*a),t*PER);
}

void stop(int t)
{
    Sleep(t*PER);
}

int main()
{
    play(Mi,2,2);play(Mi,2,2);play(Fa,2,2);play(So,2,2);play(So,2,2);play(Fa,2,2);play(Mi,2,2);play(Re,2,2);
    play(Do,2,2);play(Do,2,2);play(Re,2,2);play(Mi,2,2);play(Mi,2,2);play(Re,2,2);play(Re,2,4);

    play(Mi,2,2);play(Mi,2,2);play(Fa,2,2);play(So,2,2);play(So,2,2);play(Fa,2,2);play(Mi,2,2);play(Re,2,2);
    play(Do,2,2);play(Do,2,2);play(Re,2,2);play(Mi,2,2);play(Re,2,2);play(Do,2,2);play(Do,2,4);
}
