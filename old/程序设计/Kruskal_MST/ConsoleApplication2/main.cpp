#include <iostream>
#include "class.h"
using namespace std;
int main()
{
	int n,m;
	cout<<"输入边数及顶点数：";
	cin>>n>>m;
	MST mst=MST(n,m);
	cout<<endl<<endl;
	mst.display();
	getchar();
	getchar();
	return 0;
}