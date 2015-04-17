#include <iostream.h>

void mstrcpy(char *s1,char *s2){
int a,i;
for(i=0;;i++){
	if(s2[i]=='\0'){
	a=i;
	break;
	}
}

for(i=0;i<=a;i++)s1[i]=s2[i];
}

int main(){
	char a[100],b[100];
	cin>>a>>b; 
	mstrcpy(a,b);
	cout<<a;
	return 0;
}