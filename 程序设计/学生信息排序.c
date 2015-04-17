#include<stdio.h>
#include<string.h>
#define N 5

typedef struct
{
    int number;
    char name[20];
    double physics;
    double math;
    double computer;
    double sum;
}student;

void mathsort(student stu[])
{
    int i=0,j;
    student t;
    printf("按数学成绩排序结果为：\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(stu[i].math<stu[j].math)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void physicssort(student stu[])
{
    int i=0,j;
    student t;
    printf("按物理成绩排序结果为：\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(stu[i].physics<stu[j].physics)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void computersort(student stu[])
{
    int i=0,j;
    student t;
    printf("按计算机成绩排序结果为：\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(stu[i].computer<stu[j].computer)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void numbersort(student stu[])
{
    int i=0,j;
    student t;
    printf("按学号排序的结果为：\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(stu[i].number<stu[j].number)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void namesort(student stu[])
{
    int i=0,j;
    student t;
    printf("按姓名排序结果为：\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if(strcmp(stu[i].name,stu[j].name)<0)
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void sumsort(student stu[])
{
    int i=0,j;
    student t;
    printf("按总分排序结果为：\n");
    for(;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            if((stu[i].math+stu[i].physics+stu[i].computer)<(stu[j].math+stu[j].physics+stu[j].computer))
            {
                t=stu[i];
                stu[i]=stu[j];
                stu[j]=t;
            }
        }
        printf("%6d  %20s  %.2f  %.2f  %.2f  %.2f\n",stu[i].number,stu[i].name,stu[i].math,stu[i].physics,stu[i].computer,stu[i].sum);
    }
}

void select(void)
{
    student stu[N];
    printf("请输入排序学生数量：");
    int i;
    for(i=0;i<N;i++)
    {
        printf("请输入学生姓名：");
        scanf("%s",&stu[i].name);
        printf("请输入学号：");
        scanf("%d",&stu[i].number);
        printf("请输入数学成绩：");
        scanf("%lf",&stu[i].math);
        printf("请输入物理成绩：");
        scanf("%lf",&stu[i].physics);
        printf("请输入计算机成绩：");
        scanf("%lf",&stu[i].computer);
        stu[i].sum=stu[i].computer+stu[i].math+stu[i].physics;
    }
    while(1)
    {
        int n;
        printf("1、按姓名排序         2、按学号排序\n");
        printf("3、按数学成绩排序     4、按物理成绩排序\n");
        printf("5、按计算机成绩排序   6、按总分排序\n");
        printf("0、退出\n");
        printf("请输入你的选项：");
        scanf("%d",&n);
        switch(n)
        {
            case 1:namesort(stu);break;
            case 2:numbersort(stu);break;
            case 3:mathsort(stu);break;
            case 4:physicssort(stu);break;
            case 5:computersort(stu);break;
            case 6:sumsort(stu);break;
            default:break;
        }
    }
}


int main()
{
    select();
    return 0;
}
