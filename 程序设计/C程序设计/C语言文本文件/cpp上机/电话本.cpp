#include <new.h>
ST H{
CH o[20];
CH p[20];
CH q[20];
ST H *next;
}a[1024];
IN i,j;
H* cun(){
H *r;
P("人数:");
S("%d",&j);
P("姓名           电话            E-mall\n");
F(i=0;i<j;i++){
S("%s%s%s",&a[i].o,&a[i].p,&a[i].q);
}
F(i=0;i<j-1;i++){
a[i].next=&a[i+1];
}
r=&a[0];
a[j-1].next=NULL;
RE r;
}
V du(H* r){
F(i=0;i<j;i++){
P("%s    %s   %s\n",r->o,r->p,r->q);
r=r->next;
}
}

M(){
IN j;
H *r;
P("1.存   2.读\nmake a choice:");
S("%d",&j);
SW(j){
C 1:r=cun();
B
C 2:du(r);
B;
default:M();
}
M();
}