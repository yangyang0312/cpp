#include<stdio.h>

void swap( int *x, int *y ){
  int t;
  t=*x;*x=*y;*y=t;
}

int main(){
    int p,n;
    scanf("%d",&n);
    scanf("%d",&p);
    swap(&p,&n);
    printf("%d\n%d\n",n,p);
    return 0;
}
