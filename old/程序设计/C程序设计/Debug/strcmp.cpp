#include <iostream.h>

int mstrcmp(char *s1,char *s2){
	int i,a,b;
	for(i=0;;i++){
		if(s1[i]=='\0'){
			a=i;
			break;
		}
	}
	for(i=0;;i++){
		if(s2[i]=='\0'){
			b=i;
			break;
		}
	}
	if(a!=b)return -1;
	else{
		for(i=0;i<a;i++)if(s1[i]!=s2[i])return -1;
		return 0;
	}
}


int main(){
	char a[1000];
	char b[1000];
	cin>>a>>b;
	cout<<mstrcmp(a,b);
return 0;
}