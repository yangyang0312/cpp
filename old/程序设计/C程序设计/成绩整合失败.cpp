#include <iostream.h>
#include <string.h>
#include <stdio.h>

struct he1{
char name[20];
float math;
float english;
float average;
}he[10000];

struct ma{
char name[20];
float math;
}math[10000];

struct en{
char name[20];
float english;
}english[10000];

int hang(FILE *q){
int a;
char temp[1000];
for(a=0;;a++){
fgets(temp,1000,q);
if(feof(q)){return a;}
}
}

int main(){
	FILE *p;
	int i,j,k,l,m=0,a;
	p=fopen("file1.txt","r");
	a=hang(p);
	fclose(p);
	p=fopen("file1.txt","r");
	for(i=0;i<=a;i++){
	fscanf(p,"%s%f",math[i].name,&math[i].math);
	}
	fclose(p);
	p=fopen("file2.txt","r");
	a=hang(p);
	fclose(p);
	p=fopen("file2.txt","r");
	for(j=0;j<=a;j++){
	fscanf(p,"%s%f",english[j].name,&english[j].english);
	}
	fclose(p);
	for(k=0;k<i;k++){
		for(l=0;l<j;l++){
			if(strcmp(math[k].name,english[l].name)==0){
			strcpy(he[m].name,math[k].name);
			he[m].english=english[l].english;
			he[m].math=math[k].math;
			he[m].average=(he[m].english+he[m].math)/2.0;
			m++;
			}
		}
	}
	p=fopen("file3.txt","w");
	fprintf(p,"Name\tMath\tEnglish\tAverage\n");
	for(i=0;i<m;i++){
	fprintf(p,"%s\t%g\t%g\t%g\n",he[i].name,he[i].math,he[i].english,he[i].average);
	}
	fclose(p);
return 0;
}