#include<stdio.h>
#include<math.h>
#include<string.h>

int main(){
	int m,i,j,c,n;
	while(1){
		char a[100]={0};
		int b[100]={0};
		gets(a);
		if(a[0]==' '){
			break;
		}
		j=strlen(a);
		n=0;
		for(c=0;c<j;c++){
			if(a[c]>='0'&&a[c]<='9'){
				b[n]=a[c]-48;
				n++;
			}
		}
		j=0;
		for(c=0;c<=n;c++){
			j=j+b[c]*pow(10,n-c-1);
		}
		for(c=2;j%c!=0;c++){
			if(c>=sqrt(j))
				break;
		}
		if(c>=sqrt(j)){
			printf("%d\n",j);
		}
		else{
			printf("%d\n",j/c);
		}
	}
	return 0;
}
