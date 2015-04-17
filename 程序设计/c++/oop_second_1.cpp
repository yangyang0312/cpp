#include<iostream>
using namespace std;

class date
{
public:
    date(){cout<<"constructor!"<<endl;};
    ~date(){cout<<"destructor!"<<endl;}
    void input();
    void output();
private:
    int year,month,day;
};
void date::input()
{
    cout<<"please enter date!"<<endl;
    int y,m,d;
    cin>>y>>m>>d;
    year=y;
    month=m;
    day=d;
}
void date::output()
{
    input();
    cout<<year<<" "<<month<<" "<<day<<endl;
}
date da;
int main()
{
    da.output();
    return 0;
}
