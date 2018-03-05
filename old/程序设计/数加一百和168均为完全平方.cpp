#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;
/*题目：一个整数，它加上100后是一个完全平方数，再加上168又是一个完全平方数，请问该数是多少？*/
int main(int agc,char **agv)
{
    for(int i=0;i<100000;++i)
    {
        if(((int)sqrt(i+268))*((int)sqrt(i+268))==(i+268)&&((int)sqrt(i+100))*((int)sqrt(i+100))==(i+100))cout<<i<<"  "<<i+100<<"  "<<i+268<<"  "<<sqrt(i+100)<<"  "<<sqrt(i+268)<<endl;
    }
    return 0;
}
