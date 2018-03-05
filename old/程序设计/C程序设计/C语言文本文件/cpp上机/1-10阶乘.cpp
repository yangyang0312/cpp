#include <stdio.h>

long jiecheng(long a){
	int i;
	long j=1;
	for (i=1;i<a+1;i++){
		j*=i;
	}
	return j;
}
main(){
	int i;
	long j=0;
	for (i=1;i<11;i++){
		j+=jiecheng(i);
	}
	printf("%ld\n",j);
}