#include<stdio.h>
#include<math.h>

int m,i,a,c,d,j;
void main(){
	scanf("%d",&m);
	if(m>0&&m<100){
		for(i=0;i<m;i++){
			int b[1024]={0};
			scanf("%d",&a);
			for(j=1;a>pow(10,j);j++){
			}
			for(c=0;c<j;c++){
				d=a%10;
				b[c]=d;
				a=a/10;
			}
			for(c=0;c<j/2;c++){
				if(b[c]==b[j-1-c]){
					continue;
				}
				else{
					break;
				}
			}
			if(c>=j/2){
				d=0;
				for(c=0;c<j;c++){
					d=d+b[c];
				}
				printf("%d\n",d);
			}
			else{
				printf("no\n");
			}
		}
	}
}