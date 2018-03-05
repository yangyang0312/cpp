#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

void zifu(void)
{
    ifstream infile;
    cout<<"请输入文件名：";
    char a[20]={0};
    cin.getline(a,20);
    infile.open(a);
    if(infile.is_open())
    {
        int count=0,space=0,num=0,letter=0,other=0;
        char c;
        while(!infile.eof())
        {
            infile.get(c);
            if(c>='0'&&c<='9')++num;
            else if(c<='z'&&c>='a'||c>='A'&&c<='Z')++letter;
            else if(c==' ')++space;
            else ++other;
            ++count;
        }
        cout<<"文件"<<a<<"中共有"<<count<<"个字符."<<endl;
        cout<<"数字:"<<num<<"个\n"<<"字母："<<letter<<"个\n"<<"空格:"<<space<<"个\n"<<"其他字符:"<<other<<"个"<<endl;
    }
    else cout<<"文件打开失败！";
    infile.close();
}

int main()
{
    zifu();
    return 0;
}
