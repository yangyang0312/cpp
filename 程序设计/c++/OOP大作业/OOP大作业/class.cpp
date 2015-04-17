/*#include <iostream>
#include <cstring>
using namespace std;
class student	//学生类
{
protected:
	char id[30],name[30],age[5];
	int type;//0,normal 1,sleader 2,gstu 3,gleader
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
	virtual void display()const{cout<<"TYPE:normal  "<<"ID:"<<id<<"  "<<"NAME:"<<name<<"  "<<"AGE:"<<age<<endl;}
};
class studentLeader:virtual public student//学生干部
{
protected:
	int type;
	char post[30],college[30];//职务，学院
public:
	studentLeader():type(1),student(){strcpy(post,"");strcpy(college,"");}
	studentLeader(const char*id,const char*name,const char*age,const char*post,const char*college):student(id,name,age),type(1){strcpy(this->post,post);strcpy(this->college,college);}
	const char*getPost()const{return post;}
	const char*getCollege()const{return college;}
	int getType()const{return type;}
	void setPost(const char*post){strcpy(this->post,post);}
	void setCollege(const char*college){strcpy(this->college,college);}
	virtual void display()const{cout<<"TYPE:studentLeader  "<<"ID:"<<id<<"  "<<"NAME:"<<name<<"  "<<"AGE:"<<age<<"  "<<"POST:"<<post<<"  "<<"COLLEGE:"<<college<<endl;}
};
class goodStudent:virtual public student  //优秀学生类
{
protected:
	int type;
public:
	goodStudent():type(2),student(){}
	goodStudent(const char*id,const char*name,const char*age):type(2),student(id,name,age){}
	int getType()const{return type;}
	virtual void display()const{cout<<"TYPE:goodStudent  "<<"ID:"<<id<<"  "<<"NAME:"<<name<<" "<<"AGE:"<<age<<endl;}
};

class goodStudentLeader:public goodStudent,public studentLeader	//优秀学生干部类
{
protected:
	int type;
public:
	goodStudentLeader():type(3),studentLeader(){}
	goodStudentLeader(const char*id,const char*name,const char*age,const char*post,const char*college):type(3),student(id,name,age),studentLeader(id,name,age,post,college){}
	int getType()const{return type;}
	virtual void display()const{cout<<"TYPE:goodStudentLeader  "<<"ID:"<<id<<"  "<<"NAME:"<<name<<"  "<<"AGE:"<<age<<"  "<<"POST:"<<post<<"  "<<"COLLEGE:"<<college<<endl;}
};*/