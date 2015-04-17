#include <stdio.h>
int a,b,c[20][20]={0},k,l,m,n,d[100]={0},h,i,j,max;
main (){
	scanf ("%d",&a);
	if (a>2&&a<20){
		for (b=0;b<a;b++){
			for (k=0;k<a;k++){
				scanf("%d",&c[b][k]);
			}
		}
		for(m=0;m<a;m++){
			for (n=0;n<a;n++){
				d[m]+=c[m][n];
			}
		}
		
		for(m=a;m<2*a;m++){
			for (n=0;n<a;n++){
				d[m]+=c[n][m-a];
			}
		}
		
		for (m=0,n=0;m<a;m++,n++){
			d[2*a]+=c[m][n];
		}
		for (m=0,n=a-1;m<a;m++,n--){
			d[2*a+1]+=c[m][n];
		}
		for (int i=0;i<2*a+2;i++){
			for (int j=0;j<2*a+1;j++){
				if(d[j]<d[j+1]){
				int h=d[j];
				d[j]=d[j+1];
				d[j+1]=h;
				}
			}
		}
		for (int ii=0;ii<2*a+2;ii++){
		printf ("%d ",d[ii]);
		}
		printf("\n");
	}
}




