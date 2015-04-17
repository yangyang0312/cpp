#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

int *input( int n){
    int *p=NULL,i;
    p=(int *)malloc(sizeof(int) * n);
    if( p!=NULL ){
        for(i=0;i<n;i++){
            scanf("%d", p+i );
        }
    }
    return p;
}

int main(){
    int *data, a[10], n, i;
    scanf("%d",&n);
    data = input(n);
    printf("alloc address is %x\n",data);
    if(data!=NULL){
        memset(a, 0, sizeof(int)*10 );
        memcpy(a, data, n*sizeof(int) );
        for(i=0;i<10;i++)
            printf("a[%d]=%d\n", i, a[i]);
        free(data);
    }
    return 0;
}
