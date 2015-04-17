#include <iostream>
#include <cstring>
using namespace std;
void postOrder(char *pre,char *mid,int n)
{
	int pos;
	for(int i=0;i<n;++i)
		if (mid[i]==pre[0])
		{
			pos=i;
			break;
		}
	if(pos)
		postOrder(pre+1,mid,pos);
	if(n-1-pos)
		postOrder(pre+pos+1,mid+pos+1,n-1-pos);
	cout<<*pre;
}
int main()
{
	char pre[50],mid[50];
	gets(pre);
	gets(mid);
	postOrder(pre,mid,strlen(pre));
	getchar();
	getchar();
	return 0;
}