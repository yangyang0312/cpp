#include <new.h>
M(){
CH ch;
ch=getchar();
I(ch>='A'&&ch<='Z'){
ch+=32;
}
E{
I(ch<='z'&&ch>='a'){
ch-=32;
}
}
putchar(ch);
M();
}