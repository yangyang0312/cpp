#include<stdio.h>
#define MAXNUMBER 100

typedef struct
{
    char id[10];
    char name[20];
    double score;
}student_information;

int input(student_information st[])
{
    int n=0;
    printf("请输入学生学号、姓名以及成绩：\n");
    while(scanf("%s%s%lf",st[n].id,st[n].name,&st[n].score)==3)
    n++;
    return n;
}

void output(student_information st[],int n)
{
    int i=0;
    printf("学生成绩排名为：\n");
    for(;i<n;i++)
    {
        printf("%s  %s  %.2f  \n",st[i].id,st[i].name,st[i].score);
    }
}

void sort(student_information st[],int n)
{
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=i;j<n;j++)
        {
            if(st[i].score<st[j].score)
            {
                student_information max=st[j];
                st[j]=st[i];
                st[i]=max;
            }
        }
    }
}

int main()
{
    int count=0;
    student_information st[MAXNUMBER];
    count=input(st);
    sort(st,count);
    output(st,count);
    return 0;
}
