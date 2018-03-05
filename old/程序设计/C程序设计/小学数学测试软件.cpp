#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define pause system("pause");
#define cls system("cls");

void jisuan(char);

main(){
	cls
		char h[20];
	printf("请输入运算类型(1.加法2.减法3.乘法):");
	scanf("%s",h);
	switch(h[0]){
	case '1':jisuan('+');
		break;
	case '2':jisuan('-');
		break;
	case '3':jisuan('*');
		break;
	default:printf("输入有误!");
		pause
			main();
	}
}


void jisuan(char a){
	int b,c,d,f,i,j=0;
	cls
	printf("请输入答题数目:");
	scanf("%d",&f);
	for(i=0;i<f;i++){
		cls
		srand(time(0));
		b=rand()%100;
		c=rand()%100;
		printf("%d%c%d=",b,a,c);
		scanf("%d",&d);
		switch(a){
		case '+':
		if(d==b+c){
			j++;
			printf("right\n");
			pause
		}
		else{
			printf("wrong\n正确答案为%d",b+c);
			pause
		}
		break;
		case '-':
		if(d==b-c){
			j++;
			printf("right\n");
			pause
		}
		else{
			printf("wrong\n正确答案为%d",b-c);
			pause
		}
		break;
		case '*':
		if(d==b*c){
			j++;
			printf("right\n");
			pause
		}
		else{
			printf("wrong\n正确答案为%d",b*c);
			pause
		}
		break;
		}
	}
	cls
	printf("共答题%d道，正确%d道！\n",f,j);
	pause 
}

