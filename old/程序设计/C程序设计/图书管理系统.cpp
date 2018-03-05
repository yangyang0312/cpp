#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#define pause system("pause");
#define cls system("cls");

struct lib{										//图书信息结构体
	char book[50];
	char hao[20];
	float jia;
	char zuo[30];
	int zhuang;
	char name[30];
	int sex;
	char stuhao[10];
};

struct zhu{										//用户信息结构体
	char name[10];
	char code[30];
	int sex;
	char mingzi[30];
}baocun;

int deng=0;							//普通用户与管理员的登录状态

int main();
void zhuce();
void denglu();
void chashu();
void huanshu();
void zhuxiao();
void jieshu(lib,zhu);
void jian(char *,char *);
int cha(char *,char *);
void zhuijia(char *,char *);
void gaimi();
void guihuan(lib);
void zengshu();
void shanshu();
void xiushu();
void chaalib();
void biaoti();
void gllib();
using namespace std;
int main(){										//入口
	cls
		biaoti();
		jian("book.list"," ");
	jian("name.dat"," ");
	cout<<"				  主菜单\n\n\n"<<endl;
	cout<<"				*1.注册		*\n				*2.登陆		*\n				*3.借书		*\n				*4.还书		*\n				*5.注销		*\n				*6.改密		*\n				*7.退出		*\n				*8.管理书籍	*\n				请选择:";
	char xuan[50];
	cin>>xuan;
	switch(xuan[0]){
		case '8':gllib();
		break;
	case '1':zhuce();
		break;
	case '2':denglu();
		break;
	case '3':chashu();
		break;
	case '4':huanshu();
		break;
	case '5':zhuxiao();
		break;
	case '6':gaimi();
		break;
	case '7':exit(0);
	default:cout<<"\a\a输入有误!"<<endl;
		pause
			main();
	}
	main();
	return 0;
}

void denglu(){									//普通用户登陆函数
	FILE *p;
	struct zhu temp;
	struct zhu mess;
	cls
		printf("请输入学号:");
	cin>>mess.name;
	if(cha("black.list",mess.name)==1){
		printf("\a\a此用户被管理员加入黑名单，请联系管理员!\n");
		pause
			main();
	}
	printf("请输入密码:");
	cin>>mess.code;
	p=fopen("name.dat","r");
	for(;;){
		fscanf(p,"%s",temp.name);
		fscanf(p,"%s",temp.code);
		fscanf(p,"%s",temp.mingzi);
		fscanf(p,"%d",&temp.sex);
		if(strcmp(temp.name,mess.name)==0&&strcmp(temp.code,mess.code)==0){
			fclose(p);
			baocun=temp;
			deng=1;								//登陆成功
			return;
		}
		if(feof(p)){
			fclose(p);
			printf("\a\a学号或密码错误!若忘记密码请与管理员联系\n");		//登录失败
			pause
				main();
		}
	}
}
void zhuce(){															//新用户注册函数
	FILE *p;
	char temp1[30],temp2[30];
	struct zhu temp;
	struct zhu mess;
	cls
		printf("请输入学号:");
	cin>>mess.name;
	if(cha("black.list",mess.name)==1){
		printf("\a\a此用户被管理员加入黑名单，请联系管理员!\n");
		pause
			main();
	}
	p=fopen("name.dat","r");
	for(;;){
		fscanf(p,"%s",temp.name);
		fscanf(p,"%s",temp.code);
		if(strcmp(temp.name,mess.name)==0){
			fclose(p);
			printf("\a\a此用户已存在!\n");									//注册失败
			pause
				main();
		}
		if(feof(p)){
			fclose(p);
			break;
		}
	}
	printf("请输入密码:");
	cin>>temp1;
	printf("请再次输入:");
	cin>>temp2;
	if(strcmp(temp1,temp2)!=0){
		printf("\a\a两次输入密码不一样!\n");									//注册失败
		pause
			main();
	}
	else{
		strcpy(mess.code,temp1);
		printf("请输入姓名:");
		cin>>mess.mingzi;
		printf("请输入性别(1.女2.男):");
		cin>>mess.sex;
		p=fopen("name.dat","a");
		fprintf(p,"%s\n%s\n%s\n%d\n",mess.name,mess.code,mess.mingzi,mess.sex);
		fclose(p);
		cls
			cout<<"\a\a注册成功!\n您的用户名为"<<mess.name<<"\n密码为:"<<mess.code<<endl;   //注册成功
		deng=1;																		//记住登录状态
		baocun=mess;																//保存登录信息
		pause
			main();
	}
}
void chashu(){																	//借书函数
	int queren;
	int jie;
	struct lib temp1;
	struct lib list[1000];														//保存搜索到的图书信息
	int i;
	FILE *p;
	cls
		char temp[50];
	printf("请输入书名:");
	cin>>temp;
	p=fopen("book.list","r");
	int shumu;
	shumu=0;
	for(;;){
		if(feof(p)){
			fclose(p);
			break;
		}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1.book,temp1.hao,&temp1.jia,temp1.zuo,&temp1.zhuang,temp1.name,&temp1.sex,temp1.stuhao);
		if(strstr(temp1.book,temp)!=NULL){
			list[shumu]=temp1;
			shumu++;
		}
	}
	if(shumu==0){
		printf("\a\a没有符合条件的书籍!\n");
		pause
			main();
	}
	cls
		printf("序号\t书名\t\tISBN号\t单价\t作者\t状态\t借者\t性别\t学号\n");
	for(i=0;i<shumu-1;i++){
		printf("%d\t%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",i+1,list[i].book,list[i].hao,list[i].jia,list[i].zuo,list[i].zhuang,list[i].name,list[i].sex,list[i].stuhao);
	}
	printf("请输入借书序号:");
	cin>>jie;
	cls
		printf("书名\t\tISBN号\t单价\t作者\t状态\t借者\t性别\t学号\n");
	printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",list[jie-1].book,list[jie-1].hao,list[jie-1].jia,list[jie-1].zuo,list[jie-1].zhuang,list[jie-1].name,list[jie-1].sex,list[jie-1].stuhao);
	if(list[jie-1].zhuang==0){
		printf("\a\a此书已被用户%s借出!\n",list[jie-1].name);
		pause
			main();
	}
	else{
		if(deng!=0){
			printf("确认借出？\n1.是2.否\n请选择:");
			cin>>queren;
			if(queren==1){

				jieshu(list[jie-1],baocun);
			}
			else{
				cls
					printf("\a\a您已放弃借书!\n");
				pause
					main();
			}
		}
		else{
			printf("\a\a您尚未登录!请登录!\n");
			pause
				denglu();
			cls
				printf("确认借出？\n1.是2.否\n请选择:");
			cin>>queren;
			if(queren==1){

				jieshu(list[jie-1],baocun);
			}
			else{
				cls
					printf("\a\a您已放弃借书!\n");
				pause
					main();
			}
		}
	}
}

void zhuxiao(){
	cls
		int zhu;
	if(deng==0){
		printf("\a\a您尚未登录!\n");
		pause
			main();
	}
	printf("确认注销？\n1.是2.否\n请选择:");
	cin>>zhu;
	if(zhu==1){
		deng=0;
		printf("\a\a您已注销!\n");
		pause
			main();
	}
	else{
		printf("\a\a您未被注销!\n");
		pause
			main();
	}
}
void jieshu(lib shu,zhu ren){
	cls
		FILE *p;
	int i,j;
	struct lib temp1[1000];
	p=fopen("book.list","r");
	for(i=0;;i++){
		if(feof(p)){
			fclose(p);
			break;
		}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1[i].book,temp1[i].hao,&temp1[i].jia,temp1[i].zuo,&temp1[i].zhuang,temp1[i].name,&temp1[i].sex,temp1[i].stuhao);
	}
	for(j=0;j<i;j++){
		if(strcmp(shu.hao,temp1[j].hao)==0&&strcmp(shu.book,temp1[j].book)==0){
			temp1[j].zhuang=0;
			strcpy(temp1[j].name,ren.mingzi);
			strcpy(temp1[j].stuhao,ren.name);
			temp1[j].sex=ren.sex;
			break;
		}
	}
	p=fopen("book.list","w");
	for(j=0;j<i-1;j++){
		fprintf(p,"%s\n%s\n%g\n%s\n%d\n%s\n%d\n%s\n",temp1[j].book,temp1[j].hao,temp1[j].jia,temp1[j].zuo,temp1[j].zhuang,temp1[j].name,temp1[j].sex,temp1[j].stuhao);
	}
	fclose(p);
	printf("\a\a%s借书%s成功!\n",ren.mingzi,shu.book);
	pause
		main();
}
void jian(char *file,char *name){
	FILE *p;
	if((p=fopen(file,"r"))==NULL){
		if(strcmp(name," ")==0){
			p=fopen(file,"w");
			fclose(p);
			return;
		}
		else{
			p=fopen(file,"w");
			fprintf(p,"%s\n",name);
			fclose(p);
			return;
		}
	}
	else{
		fclose(p);
		return;
	}
}
void huanshu(){
	cls
		lib temp1;
	lib list[1000];
	char shu[50];
	int shumu=0,jie,queren,i;
	FILE *p;
	printf("请输入要归还的书名:");
	cin>>shu;
	p=fopen("book.list","r");
	for(i=0;;i++){
		if(feof(p)){
			fclose(p);
			break;
		}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1.book,temp1.hao,&temp1.jia,temp1.zuo,&temp1.zhuang,temp1.name,&temp1.sex,temp1.stuhao);
		if(strstr(temp1.book,shu)!=NULL&&temp1.zhuang==0){
			list[shumu]=temp1;
			shumu++;
		}
	}
	if(shumu==0){
		printf("\a\a没有符合条件的书籍!\n");
		pause
			main();
	}
	cls
		printf("序号\t书名\t\tISBN号\t单价\t作者\t状态\t借者\t性别\t学号\n");
	for(i=0;i<shumu;i++){
		printf("%d\t%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",i+1,list[i].book,list[i].hao,list[i].jia,list[i].zuo,list[i].zhuang,list[i].name,list[i].sex,list[i].stuhao);
	}
	printf("请输入还书序号:");
	cin>>jie;
	cls
		printf("书名\t\tISBN号\t单价\t作者\t状态\t借者\t性别\t学号\n");
	printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",list[jie-1].book,list[jie-1].hao,list[jie-1].jia,list[jie-1].zuo,list[jie-1].zhuang,list[jie-1].name,list[jie-1].sex,list[jie-1].stuhao);

		printf("确认归还？\n1.是2.否\n请选择:");
		cin>>queren;
		if(queren==1){
			guihuan(list[jie-1]);
		}
		else{
			cls
				printf("\a\a您已放弃还书!\n");
			pause
				main();
		}
}
int cha(char *file,char *str){
	FILE *p;
	char temp[100];
	p=fopen(file,"r");
	for(;;){
		fscanf(p,"%s",temp);
		if(strcmp(temp,str)==0){
			fclose(p);
			return 1;
		}
		if(feof(p)){
			fclose(p);
			return 0;
		}
	}
}
void guihuan(lib shu){
	FILE *p;
	int i,j;
	lib temp1[1000];
	p=fopen("book.list","r");
	for(i=0;;i++){
		if(feof(p)){
			fclose(p);
			break;
		}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1[i].book,temp1[i].hao,&temp1[i].jia,temp1[i].zuo,&temp1[i].zhuang,temp1[i].name,&temp1[i].sex,temp1[i].stuhao);
	}
	for(j=0;j<i;j++){
		if(strcmp(shu.hao,temp1[j].hao)==0&&strcmp(shu.book,temp1[j].book)==0){
			temp1[j].zhuang=1;
			strcpy(temp1[j].name,"0");
			strcpy(temp1[j].stuhao,"0");
			temp1[j].sex=0;
			break;
		}
	}
	p=fopen("book.list","w");
	for(j=0;j<i-1;j++){
		fprintf(p,"%s\n%s\n%g\n%s\n%d\n%s\n%d\n%s\n",temp1[j].book,temp1[j].hao,temp1[j].jia,temp1[j].zuo,temp1[j].zhuang,temp1[j].name,temp1[j].sex,temp1[j].stuhao);
	}
	fclose(p);
	printf("\a\a还书%s成功!\n",shu.book);
	pause
		main();
}
void zhuijia(char *file,char *str){
	FILE *p;
	p=fopen(file,"a");
	fprintf(p,"%s\n",str);
	fclose(p);
}
void zhuijia(char *file,float str){
	FILE *p;
	p=fopen(file,"a");
	fprintf(p,"%g\n",str);
	fclose(p);
}
void gaimi(){
	cls
		FILE *p;
	zhu temp[1000];
	int i,j;
	char temp1[30],temp2[30];
	if(deng==0){
		printf("\a\a您尚未登录，不能进行改密操作!\n");
		pause
			main();
	}
	else{
		printf("请输入新密码:");
		cin>>temp1;
		printf("请再次输入:");
		cin>>temp2;
		if(strcmp(temp1,temp2)!=0){
			printf("\a\a两次输入密码不一样，改密失败!\n");
			pause
				main();
		}
		else{
			p=fopen("name.dat","r");
			for(i=0;;i++){
				if(feof(p)){
					fclose(p);
					break;
				}
				fscanf(p,"%s%s%s%d",temp[i].name,temp[i].code,temp[i].mingzi,&temp[i].sex);
			}
			for(j=0;j<i;j++){
				if(strcmp(temp[j].name,baocun.name)==0){
					strcpy(temp[j].code,temp1);
					break;
				}
			}
			p=fopen("name.dat","w");
			for(j=0;j<i-1;j++){
				fprintf(p,"%s\n%s\n%s\n%d\n",temp[j].name,temp[j].code,temp[j].mingzi,temp[j].sex);
			}
			fclose(p);
			deng=0;
			printf("\a\a改密成功!请重新登录!\n");
			pause
				main();
		}
	}
}

void gllib(){
	cls
		char xuan[20];
	printf("				 管理图书\n");
	printf("			*************************\n			*1.新增图书		*\n			*2.修改图书信息		*\n			*3.删除图书		*\n			*4.查看全部图书信息	*\n			*5.返回			*\n			*************************\n请选择:");
	cin>>xuan;
	switch (xuan[0]){
	case '1':zengshu();
		break;
	case '2':xiushu();
		break;
	case '3':shanshu();
		break;
	case '4':chaalib();
		break;
	case '5':main();
		break;
	default:printf("\a\a输入有误!\n");
		pause
			gllib();
	}
}
void biaoti(){
	char titles[100]="图书管理系统 ";
	if(deng==1){
	strcat(titles,"普通用户");
	strcat(titles,baocun.name);
	strcat(titles,"已登录");
	}
	else{
	strcat(titles,"普通用户未登录  ");
	}

	char temp[100]="title ";
	strcat(temp,titles);
	system(temp);
}

void zengshu(){
	cls
		lib shu;
	printf("请输入书名:");
	cin>>shu.book;
	printf("请输入ISBN号:");
	cin>>shu.hao;
	if(cha("book.list",shu.hao)==1){
		printf("\a\a添加书籍失败!此ISBN号已存在!\n");
		pause
			gllib();
	}
	else{
		printf("请输入单价:");
		cin>>shu.jia;
		printf("请输入作者:");
		cin>>shu.zuo;
		printf("请输入状态(1.再架上0.已借出):");
		cin>>shu.zhuang;
		printf("请输入借者姓名(若未借出输入0):");
		cin>>shu.name;
		printf("请输入借者性别(1.男2.女,若未借出输入0):");
		cin>>shu.sex;
		printf("请输入借者学号(若未借出输入0)");
		cin>>shu.stuhao;
		zhuijia("book.list",shu.book);
		zhuijia("book.list",shu.hao);
		zhuijia("book.list",shu.jia);
		zhuijia("book.list",shu.zuo);
		zhuijia("book.list",(float)shu.zhuang);
		zhuijia("book.list",shu.name);
		zhuijia("book.list",(float)shu.sex);
		zhuijia("book.list",shu.stuhao);
		printf("\a\a图书%s新增成功!\n",shu.book);
		pause
			gllib();
	}
}
void xiushu(){
	cls
		FILE *p;
	char shu[50],book[50],hao[50];
	lib shus[1000];
	int i,j,k=0,xuan;
	printf("请输入您要修改信息的书名:");
	cin>>shu;
		p=fopen("book.list","r");
		for(i=0;;i++){
			if(feof(p)){
				fclose(p);
				break;
			}
			fscanf(p,"%s%s%f%s%d%s%d%s",shus[i].book,shus[i].hao,&shus[i].jia,shus[i].zuo,&shus[i].zhuang,shus[i].name,&shus[i].sex,shus[i].stuhao);
		}
		for(j=0;j<i-1;j++){
			if(strstr(shus[j].book,shu)!=NULL){
				k++;
				cls
		printf("书名\t\tISBN号\t单价\t作者\t状态\t借者\t性别\t学号\n");
	printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",shus[j].book,shus[j].hao,shus[j].jia,shus[j].zuo,shus[j].zhuang,shus[j].name,shus[j].sex,shus[j].stuhao);
	printf("是否修改?(1.是2.否):");
	cin>>xuan;
	if(xuan==2){
	cls
		continue;
	}
	printf("请输入书名:");
	cin>>book;
	printf("请输入ISBN号:");
	cin>>hao;
	if(cha("book.list",hao)==1){
		printf("\a\a修改书籍失败!此ISBN号已存在!\n");
		pause
	}
	else{
		strcpy(shus[j].book,book);
		strcpy(shus[j].hao,hao);
		printf("请输入单价:");
		cin>>shus[j].jia;
		printf("请输入作者:");
		cin>>shus[j].zuo;
		printf("请输入状态(1.再架上0.已借出):");
		cin>>shus[j].zhuang;
		printf("请输入借者姓名(若未借出输入0):");
		cin>>shus[j].name;
		printf("请输入借者性别(1.男2.女,若未借出输入0):");
		cin>>shus[j].stuhao;
		printf("请输入借者学号(若未借出输入0)");
		cin>>shus[j].stuhao;
		printf("是否继续?(1.是2.否):");
		cin>>xuan;
		if(xuan==1){
		cls
			continue;
		}
		else{
		break;
		}
	}

			}
		}
		if(k==0){
		printf("\a\a未找到此图书!\n");
		pause
			gllib();
		}
		else{
		p=fopen("book.list","w");
		for(j=0;j<i-1;j++){
		fprintf(p,"%s\n%s\n%g\n%s\n%d\n%s\n%d\n%s\n",shus[j].book,shus[j].hao,shus[j].jia,shus[j].zuo,shus[j].zhuang,shus[j].name,shus[j].sex,shus[j].stuhao);
		}
		fclose(p);
		printf("\a\a修改成功!\n");
		pause
			gllib();
		}
}
void shanshu(){
		cls
		FILE *p;
	char shu[50];
	lib shus[1000];
	int i,j,k=0,l=0,xuan,shanxu[1000],m,you;
	printf("请输入您要删除的书名:");
	cin>>shu;
		p=fopen("book.list","r");
		for(i=0;;i++){
			if(feof(p)){
				fclose(p);
				break;
			}
			fscanf(p,"%s%s%f%s%d%s%d%s",shus[i].book,shus[i].hao,&shus[i].jia,shus[i].zuo,&shus[i].zhuang,shus[i].name,&shus[i].sex,shus[i].stuhao);
		}
		for(j=0;j<i-1;j++){
			if(strstr(shus[j].book,shu)!=NULL){
				k++;
				cls
		printf("书名\t\tISBN号\t单价\t作者\t状态\t借者\t性别\t学号\n");
	printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",shus[j].book,shus[j].hao,shus[j].jia,shus[j].zuo,shus[j].zhuang,shus[j].name,shus[j].sex,shus[j].stuhao);
	printf("是否删除?(1.是2.否):");
	cin>>xuan;
	if(xuan==2){
	cls
		continue;
	}
shanxu[l]=j;
l++;
		printf("是否继续?(1.是2.否):");
		cin>>xuan;
		if(xuan==1){
		cls
			continue;
		}
		else{
		break;
		}
			}
		}
		if(k==0){
		printf("\a\a未找到此图书!\n");
		pause
			gllib();
		}
		else{
		p=fopen("book.list","w");
		for(j=0;j<i-1;j++){
			you=0;
			for(m=0;m<l;m++){
				if(shanxu[m]==j){
					you=1;
					break;
				}
			}
			if(you==0)fprintf(p,"%s\n%s\n%g\n%s\n%d\n%s\n%d\n%s\n",shus[j].book,shus[j].hao,shus[j].jia,shus[j].zuo,shus[j].zhuang,shus[j].name,shus[j].sex,shus[j].stuhao);
		}
		fclose(p);
		printf("\a\a删除成功!\n");
		pause
			gllib();
		}
}
void chaalib(){
	cls
	FILE *p;
	lib temp1;
		printf("书名\t\tISBN号\t单价\t作者\t状态\t借者\t性别\t学号\n");
		p=fopen("book.list","r");
		for(;;){
			if(feof(p)){
			fclose(p);
			break;
			}
		fscanf(p,"%s%s%f%s%d%s%d%s",temp1.book,temp1.hao,&temp1.jia,temp1.zuo,&temp1.zhuang,temp1.name,&temp1.sex,temp1.stuhao);
		printf("%s\t%s\t%g\t%s\t%d\t%s\t%d\t%s\n",temp1.book,temp1.hao,temp1.jia,temp1.zuo,temp1.zhuang,temp1.name,temp1.sex,temp1.stuhao);
		}
		pause
			gllib();
}

void chaazhu(){
		cls
	FILE *p;
	zhu shus;
		printf("学号\t\t姓名\t性别\n");
		p=fopen("name.dat","r");
		for(;;){
			if(feof(p)){
			fclose(p);
			break;
			}
		fscanf(p,"%s%s%s%d",shus.name,shus.code,shus.mingzi,&shus.sex);
		printf("%s\t%s\t%d\n",shus.name,shus.mingzi,shus.sex);
		}
		pause
			main();
}
