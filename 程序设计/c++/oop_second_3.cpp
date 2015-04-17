#include<iostream>
using namespace std;
class fun
{
public:
    static int j;
    fun(){i=5;++j;cout<<"constructor!"<<endl;}
    ~fun(){--j;cout<<"destructor!"<<endl;}
    void display(){cout<<i<<"  "<<j<<endl;}
    void disj(){cout<<j<<endl;}
private:
    int i;
};
int fun::j=10;
int main()
{
    fun *f=new fun;
    f->display();
    delete f;
    cout<<fun::j<<endl;
    fun *f1=new fun;
    f1->display();
    delete f1;
    cout<<fun::j<<endl;
    fun *f2=new fun;
    f2->display();
    delete f2;
    cout<<fun::j<<endl;
    return 0;
}
