#include <stdio.h>
int main (){
    int tie,jin;
	double PI=3.1415926;
	scanf ("%d %d",&tie,&jin);
	if (tie>=0&&jin>=0){
		float tie1=4.0/3*PI*(tie/2.0)*(tie/2.0)*(tie/2.0)*7.86/1000;
		float jin1=4.0/3*PI*(jin/2.0)*(tie/2.0)*(tie/2.0)*19.3/1000;
		printf("%.3f %.3f",tie1,jin1);
		return 0;
	}
}