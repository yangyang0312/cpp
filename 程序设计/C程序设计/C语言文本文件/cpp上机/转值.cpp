#include <stdio.h>
main(){
	int a[2][3]={1,2,3,4,5,6},b[3][2],i,j;
	for (i=0;i<2;i++){
		for (j=0;j<3;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	for (i=0;i<3;i++){
		for (j=0;j<2;j++){
			b[i][j]=a[j][i];
		}
	}
	for(i=0;i<3;i++){
		for (j=0;j<2;j++){
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
}