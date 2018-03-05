#include <new.h>

IN M(){
int *q,h[20]={1,2,3,4,5,6,7,8,9,0};
q = (int*)malloc(400);
I(q!=NULL){
q=h;
P("%lf\n%s\n",q,q);
}
E{
P("分配失败！\n");
}
free (q);
P("%s\n",q);
}
