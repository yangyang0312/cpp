#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <malloc.h>
using namespace std;
template<class T>				//内存分配模板
void renew(T *&old,int size)
{
	T *temp=new T[size];
	memcpy(temp,old,_msize(old));
	delete old;
	old=temp;
}
class student			//学生类
{
protected:
	char id[30],name[30],age[5];
	int type;		  //0,normal 1,stuL 2,goodStu 3,goodStuL
public:
	student():type(0){strcpy(id,"");strcpy(name,"");strcpy(age,"");}
	student(const char*id,const char*name,const char*age):type(0){strcpy(this->id,id);strcpy(this->name,name);strcpy(this->age,age);}
	const char* getId()const{return id;}
	const char* getName()const{return name;}
	const char* getAge()const{return age;}
	int getType()const{return type;}
	void setId(const char*id){strcpy(this->id,id);}
	void setName(const char*name){strcpy(this->name,name);}
	void setAge(const char*age){strcpy(this->age,age);}
	void display()const{cout<<"TYPE:normal  "<<"ID:"<<id<<"  "<<"NAME:"<<name<<"  "<<"AGE:"<<age<<endl;}
};
class studentLeader:virtual public student	//学生干部
{
protected:
	int type;
	char post[30],college[30];				//职务，学院
public:
	studentLeader():type(1),student(){strcpy(post,"");strcpy(college,"");}
	studentLeader(const char*id,const char*name,const char*age,const char*post,const char*college):student(id,name,age),type(1){strcpy(this->post,post);strcpy(this->college,college);}
	const char*getPost()const{return post;}
	const char*getCollege()const{return college;}
	int getType()const{return type;}
	void setPost(const char*post){strcpy(this->post,post);}
	void setCollege(const char*college){strcpy(this->college,college);}
	void display()const{cout<<"TYPE:studentLeader  "<<"ID:"<<id<<"  "<<"NAME:"<<name<<"  "<<"AGE:"<<age<<"  "<<"POST:"<<post<<"  "<<"COLLEGE:"<<college<<endl;}
};
class goodStudent:virtual public student   //优秀学生类
{
protected:
	int type;
public:
	goodStudent():type(2),student(){}
	goodStudent(const char*id,const char*name,const char*age):type(2),student(id,name,age){}
	int getType()const{return type;}
	void display()const{cout<<"TYPE:goodStudent  "<<"ID:"<<id<<"  "<<"NAME:"<<name<<" "<<"AGE:"<<age<<endl;}
};

class goodStudentLeader:public goodStudent,public studentLeader	 //优秀学生干部类
{
protected:
	int type;
public:
	goodStudentLeader():type(3),studentLeader(){}
	goodStudentLeader(const char*id,const char*name,const char*age,const char*post,const char*college):type(3),student(id,name,age),studentLeader(id,name,age,post,college){}
	int getType()const{return type;}
	void display()const{cout<<"TYPE:goodStudentLeader  "<<"ID:"<<id<<"  "<<"NAME:"<<name<<"  "<<"AGE:"<<age<<"  "<<"POST:"<<post<<"  "<<"COLLEGE:"<<college<<endl;}
};
class file
{
private:
	char stuF[30],stuLF[30],goodStuF[30],goodStuLF[30];
	int stuNum,stuLNum,goodStuNum,goodStuLNum;
	student *stu;
	studentLeader *stuL;
	goodStudent *goodStu;
	goodStudentLeader *goodStuL;
public:
	file();
	~file(){rebuild();}
	student getStu()const{return *stu;}
	studentLeader getStuL()const{return*stuL;}
	goodStudent getgoodStu()const{return*goodStu;}
	goodStudentLeader getGoodStuL()const{return*goodStuL;}
	char getStuF()const{return *stuF;}
	char getStuLF()const{return *stuLF;}
	char getGoodStuF()const{return *goodStuF;}
	char getGoodStuLF()const{return *goodStuLF;}
	int getStuNum()const{return stuNum;}
	int getStuLNum()const{return stuLNum;}
	int getGoodStuNum()const{return goodStuNum;}
	int getGoodstuLNum()const{return goodStuLNum;}
	void add(int type);
	void inquire();
	void update();
	void dele();
	void rebuild();
	void stuDisplay(){if(stuNum!=0)for (int i=0;i<stuNum;++i)stu[i].display();}
	void stuLDisplay(){if(stuLNum!=0)for(int i=0;i<stuLNum;++i)stuL[i].display();}
	void goodStuDisplay(){if(goodStuNum!=0)for(int i=0;i<goodStuNum;++i)goodStu[i].display();}
	void goodStuLDisplay(){if(goodStuLNum!=0)for(int i=0;i<goodStuLNum;++i)goodStuL[i].display();}
	void statistics(){cout<<"    normal student: "<<stuNum<<endl<<"    student leader: "<<stuLNum<<endl<<"    good student: "<<goodStuLNum<<endl<<"    good student leader: "<<goodStuLNum<<endl<<"    all: "<<stuNum+stuLNum+goodStuLNum+goodStuNum<<endl;}
};
void file::rebuild()
{
	FILE *p;
	p=fopen(stuF,"w");
	if (p)
	{
		for(int i=0;i<stuNum;++i)
		{
			fputs(stu[i].getId(),p);
			fprintf(p,"\n");
			fputs(stu[i].getName(),p);
			fprintf(p,"\n");
			fputs(stu[i].getAge(),p);
			fprintf(p,"\n");
		}
	}
	p=fopen(stuLF,"w");
	if (p)
	{
		for(int i=0;i<stuLNum;++i)
		{
			fputs(stuL[i].getId(),p);
			fprintf(p,"\n");
			fputs(stuL[i].getName(),p);
			fprintf(p,"\n");
			fputs(stuL[i].getAge(),p);
			fprintf(p,"\n");
			fputs(stuL[i].getPost(),p);
			fprintf(p,"\n");
			fputs(stuL[i].getCollege(),p);
			fprintf(p,"\n");
		}
	}
	p=fopen(goodStuF,"w");
	if (p)
	{
		for(int i=0;i<goodStuNum;++i)
		{
			fputs(goodStu[i].getId(),p);
			fprintf(p,"\n");
			fputs(goodStu[i].getName(),p);
			fprintf(p,"\n");
			fputs(goodStu[i].getAge(),p);
			fprintf(p,"\n");
		}
	}
	p=fopen(goodStuLF,"w");
	if (p)
	{
		for(int i=0;i<goodStuLNum;++i)
		{
			fputs(goodStuL[i].getId(),p);
			fprintf(p,"\n");
			fputs(goodStuL[i].getName(),p);
			fprintf(p,"\n");
			fputs(goodStuL[i].getAge(),p);
			fprintf(p,"\n");
			fputs(goodStuL[i].getPost(),p);
			fprintf(p,"\n");
			fputs(goodStuL[i].getCollege(),p);
			fprintf(p,"\n");
		}
	}
	fclose(p);
	cout<<"rebuild successfully!"<<endl;
	cout<<"you can look up at file:"<<stuF<<" "<<stuLF<<" "<<goodStuF<<" and "<<goodStuLF<<endl;
}
void file::dele()			//删除
{
	char id[30];
	cout<<"please input ID to delete:";
	cin>>id;
	for(int i=0;i<stuNum;++i)
		if (strcmp(stu[i].getId(),id)==0)
		{
			for(int j=i;j<stuNum-1;++j)
				stu[j]=stu[j+1];
			--stuNum;
		}
	for(int i=0;i<stuLNum;++i)
		if (strcmp(stuL[i].getId(),id)==0)
		{
			for(int j=i;j<stuLNum-1;++j)
				stuL[j]=stuL[j+1];
			--stuLNum;
		}
	for(int i=0;i<goodStuNum;++i)
		if (strcmp(goodStu[i].getId(),id)==0)
		{
			for(int j=i;j<goodStuNum-1;++j)
				goodStu[j]=goodStu[j+1];
			--goodStuNum;
		}
	for(int i=0;i<goodStuLNum;++i)
		if (strcmp(goodStuL[i].getId(),id)==0)
		{
			for(int j=i;j<goodStuLNum-1;++j)
				goodStuL[j]=goodStuL[j+1];
			--goodStuLNum;
		}
	cout<<"delete successfully!"<<endl;
}
void file::inquire()		//查询
{
	char in[30];
	cout<<"input inquire condition:";
	cin>>in;
	for (int i=0;i<stuNum;++i)
		if (strcmp(stu[i].getId(),in)==0||strcmp(stu[i].getName(),in)==0)
			stu[i].display();
	for (int i=0;i<stuLNum;++i)
		if (strcmp(stuL[i].getId(),in)==0||strcmp(stuL[i].getName(),in)==0||strcmp(stuL[i].getPost(),in)==0||strcmp(stuL[i].getCollege(),in)==0)
			stuL[i].display();
	for(int i=0;i<goodStuNum;++i)
		if(strcmp(goodStu[i].getId(),in)==0||strcmp(goodStu[i].getName(),in)==0)
			goodStu[i].display();
	for(int i=0;i<goodStuLNum;++i)
		if(strcmp(goodStuL[i].getId(),in)==0||strcmp(goodStuL[i].getName(),in)==0||strcmp(goodStuL[i].getPost(),in)==0||strcmp(goodStuL[i].getCollege(),in)==0)
			goodStuL[i].display();
}
void file::update()		//更新
{
	cout<<"please input ID:";
	char id[30];
	cin>>id;
	for(int i=0;i<stuNum;++i)
		if(strcmp(stu[i].getId(),id)==0)
		{
			cout<<"please input new ID,NAME and AGE:";
			char ID[30],NAME[30],AGE[5];
			cin>>ID>>NAME>>AGE;
			stu[i].setId(ID);
			stu[i].setName(NAME);
			stu[i].setAge(AGE);
		}
	for (int i=0;i<stuLNum;++i)
		if (strcmp(stuL[i].getId(),id)==0)
		{
			cout<<"please input new ID,NAME,AGE,POST and COLLEGE:";
			char ID[30],NAME[30],AGE[5],POST[30],COLLEGE[30];
			cin>>ID>>NAME>>AGE>>POST>>COLLEGE;
			stuL[i].setId(ID);
			stuL[i].setName(NAME);
			stuL[i].setPost(POST);
			stuL[i].setCollege(COLLEGE);
		}
	for(int i=0;i<goodStuNum;++i)
		if (strcmp(goodStu[i].getId(),id)==0)
		{
			cout<<"please input new ID,NAME and AGE:";
			char ID[30],NAME[30],AGE[5];
			cin>>ID>>NAME>>AGE;
			goodStu[i].setId(ID);
			goodStu[i].setName(NAME);
			goodStu[i].setAge(AGE);
		}
	for (int i=0;i<goodStuLNum;++i)
		if (strcmp(goodStuL[i].getId(),id)==0)
		{
			cout<<"please input new ID,NAME,AGE,POST and COLLEGE:";
			char ID[30],NAME[30],AGE[5],POST[30],COLLEGE[30];
			cin>>ID>>NAME>>AGE>>POST>>COLLEGE;
			goodStuL[i].setId(ID);
			goodStuL[i].setName(NAME);
			goodStuL[i].setPost(POST);
			goodStuL[i].setCollege(COLLEGE);
		}
	cout<<"update successfully!"<<endl;
}
void file::add(int type)	//增加
{
	switch (type)
	{
		case 0:				//stu
			{
				stu=(student*)realloc(stu,(++stuNum)*sizeof(student));
				char ID[30],NAME[30],AGE[5];
				cout<<"input ID,NAME,AGE please!"<<endl;
				cin>>ID>>NAME>>AGE;
				stu[stuNum-1].setId(ID);
				stu[stuNum-1].setName(NAME);
				stu[stuNum-1].setAge(AGE);
				break;
			}
		case 1:				//stuL
			{
				++stuLNum;
				renew(stuL,stuLNum*sizeof(studentLeader));
				char ID[30],NAME[30],AGE[5],POST[30],COLLEGE[30];
				cout<<"input ID,NAME,AGE,POST and COLLEGE please!"<<endl;
				cin>>ID>>NAME>>AGE>>POST>>COLLEGE;
				stuL[stuLNum-1].setId(ID);
				stuL[stuLNum-1].setName(NAME);
				stuL[stuLNum-1].setAge(AGE);
				stuL[stuLNum-1].setPost(POST);
				stuL[stuLNum-1].setCollege(COLLEGE);
				break;
			}
		case 2:				//goodStu
			{
				++goodStuNum;
				renew(goodStu,goodStuNum*sizeof(goodStudent));
				char ID[30],NAME[30],AGE[5];
				cout<<"input ID,NAME,AGE please!"<<endl;
				cin>>ID>>NAME>>AGE;
				goodStu[goodStuNum-1].setId(ID);
				goodStu[goodStuNum-1].setName(NAME);
				goodStu[goodStuNum-1].setAge(AGE);
				break;
			}
		case 3:				//goodStuL
			{
				++goodStuLNum;
				renew(goodStuL,goodStuLNum*sizeof(goodStuLNum));
				cout<<"input ID,NAME,AGE,POST and COLLEGE please!"<<endl;
				char ID[30],NAME[30],AGE[5],POST[30],COLLEGE[30];
				cin>>ID>>NAME>>AGE>>POST>>COLLEGE;
				goodStuL[goodStuLNum-1].setId(ID);
				goodStuL[goodStuLNum-1].setName(NAME);
				goodStuL[goodStuLNum-1].setAge(AGE);
				goodStuL[goodStuLNum-1].setPost(POST);
				goodStuL[goodStuLNum-1].setCollege(COLLEGE);
				break;
			}
		default:cout<<"ERROR INPUT!"<<endl;
	}
	cout<<"add successfully!"<<endl;
}
file::file():stuNum(0),stuLNum(0),goodStuNum(0),goodStuLNum(0)
{
	strcpy(stuF,"studentFile.txt");
	strcpy(stuLF,"studentLeaderFile.txt");
	strcpy(goodStuF,"goodStudentFile.txt");
	strcpy(goodStuLF,"goodStudentLeaderFile.txt");
	FILE *p;
	p=fopen(stuF,"r");
	if(p)
	{
		char s[300][30]={0};
		int i=0;
		while (fgets(s[i],30,p)!=NULL)++i;
		stuNum=i/3;
		stu=(student*)malloc(stuNum*sizeof(student));
		for(int j=0;j<i;j+=3)
		{
			stu[j/3].setId(s[j]);
			stu[j/3].setName(s[j+1]);
			stu[j/3].setAge(s[j+2]);
		}
	}
	p=fopen(goodStuF,"r");
	if(p)
	{
		char s[300][30]={0};
		int i=0;
		while (fgets(s[i],30,p)!=NULL)++i;
		goodStuNum=i/3;
		this->goodStu=new goodStudent[goodStuNum];
		for(int j=0;j<i;j+=3)
		{
			goodStu[j/3].setId(s[j]);
			goodStu[j/3].setName(s[j+1]);
			goodStu[j/3].setAge(s[j+2]);
		}
	}
	p=fopen(stuLF,"r");
	if (p)
	{
		char s[300][30]={0};
		int i=0;
		while (fgets(s[i],30,p)!=NULL)++i;
		stuLNum=i/5;
		this->stuL=new studentLeader[stuLNum];
		for(int j=0;j<i;j+=5)
		{
			stuL[j/5].setId(s[j]);
			stuL[j/5].setName(s[j+1]);
			stuL[j/5].setAge(s[j+2]);
			stuL[j/5].setPost(s[j+3]);
			stuL[j/5].setCollege(s[j+4]);
		}
	}
	p=fopen(goodStuLF,"r");
	if (p)
	{
		char s[300][30]={0};
		int i=0;
		while (fgets(s[i],30,p)!=NULL)++i;
		goodStuLNum=i/5;
		this->goodStuL=new goodStudentLeader[goodStuLNum];
		for(int j=0;j<i;j+=5)
		{
			goodStuL[j/5].setId(s[j]);
			goodStuL[j/5].setName(s[j+1]);
			goodStuL[j/5].setAge(s[j+2]);
			goodStuL[j/5].setPost(s[j+3]);
			goodStuL[j/5].setCollege(s[j+4]);
		}
	}
	fclose(p);
}
int main()
{
	file file;
	while (1)
	{
		cout<<"select please:"<<endl<<"      1,add"<<endl<<"      2,update"<<endl;
		cout<<"      3,inquire"<<endl<<"      4,delete"<<endl<<"      5,rebuild"<<endl;
		cout<<"      6,statistics"<<endl<<"      7,display all"<<endl<<"      8,exit"<<endl<<"input:";
		int i;
		cin>>i;
		if(8==i)break;
		else 
		{
			switch (i)
			{
			case 1:
				{
					int type;
					cout<<"input type please!normal student(0),student leader(1),good student(2),good student leaser(3)"<<endl<<"input:";
					cin>>type;
					file.add(type);
					break;
				}
			case 2:file.update();break;
			case 3:file.inquire();break;
			case 4:file.dele();break;
			case 5:file.rebuild();break;
			case 6:file.statistics();break;
			case 7:
				file.stuDisplay();
				file.stuLDisplay();
				file.goodStuDisplay();
				file.goodStuLDisplay();
				break;
			default:
				cout<<"error input,try again please!"<<endl<<endl;
				break;
			}
		}
	}
	return 0;
}