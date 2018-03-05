#include <iostream>
#include<climits>
#include<cstdio>
using namespace std;

int main()
{
    cout<<"max short        "<<SHRT_MAX<<endl;
    cout<<"max int          "<<INT_MAX<<endl;
    cout<<"max long         "<<LONG_MAX<<endl;
    cout<<"max long long    "<<LONG_LONG_MAX<<endl;
    cout<<"max char         "<<CHAR_MAX<<endl;
    cout<<"max unsign long  "<<ULONG_MAX<<endl<<endl;

    printf("char         %d     bytes\n",sizeof(char));
    printf("short        %d     bytes\n",sizeof(short));
    printf("int          %d     bytes\n",sizeof(int));
    printf("long         %d     bytes\n",sizeof(long));
    printf("long long    %d     bytes\n",sizeof(long long));
    printf("float        %d     bytes\n",sizeof(float));
    printf("double       %d     bytes\n",sizeof(double));
    printf("long double  %d    bytes\n",sizeof(long double));

    cout<<CHAR_BIT;              //一字节的位数

    return 0;
}
