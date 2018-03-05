#include "calc_class.h"
#include <iostream>
#include <vector>
#include <string>

bool SC_CALC::is_cmd()
{
	if (calc_expression == "hst")
	{
		calc_history();
		return true;
	}
	else if (calc_expression == "exit")
	{
		exit(0);
	}
	else if (calc_expression == "hlp")
	{
		calc_help();
		return true;
	}
	else if (calc_expression == "cls")
	{
		system("cls");
		return true;
	}
	else if (calc_expression == "set")
	{
		calc_set();
		return true;
	}
	else
	{
		return false;
	}
}

void SC_CALC::calc_history()
{
	vector<string>::size_type num = calc_history_equ.size();
	cout << "history:" << endl;
	for (vector<string>::size_type i = 0; i < num; ++i)
	{
		cout << calc_history_equ[i] << endl << "\t\t\t\t" <<"=" << calc_history_res[i] << endl;
	}
}

void SC_CALC::calc_help()
{
	cout << "SC Calculator 使用说明：" << endl << endl
		<< "SC_Calclator 可直接输入算式或函数进行计算，另外还有查看历史等命令." << endl << endl
		<< "一、所有支持的命令及函数如下：" << endl << endl
		<< "1.命令：" << endl
		<< "cls\t\t\t清屏" << endl
		<< "hst\t\t\t查看历史" << endl
		<< "hlp\t\t\t显示此帮助" << endl
		<< "exit\t\t\t退出程序" << endl
		<< "set\t\t\tset功能" << endl << endl
		<< "set功能介绍：" << endl<<endl
		<< "set功能的设计是为了节省用户输入频繁使用的算式的工作量，比如设置“const1”为“1,2,9,36,7,15”，在计算时输入“avg[cosnt1]”就相当于输入“avg[1,2,9,36,7,15]”" << endl<<endl
		<< "注意：set功能不区分大小写，即Con和cON带表一个常量" << endl<<endl
		<< "若一个set名是另一个set常量的前缀，则长名字会被屏蔽，如同时存在“con”和“conc”，则“conc”将会失效" << endl<<endl
		<< "不要尝试叠加set，即不要设置con=ca，  ca=1+2，这会导致输入非法"
		<< endl << endl;
	system("pause");
		cout<< "2.运算符：" << endl
		<< "+\t\t\t双目运算符“加”   单目运算符“正”" << endl
		<< "-\t\t\t双目运算符“减”   单目运算符“负”" << endl
		<< "*\t\t\t双目运算符“乘”" << endl
		<< "/\t\t\t双目运算符“除”" << endl
		<< "mod\t\t\t双目运算符“取模”" << endl
		<< "^\t\t\t双目运算符“次方”" << endl
		<< "e\t\t\t科学记数法" << endl << endl;
	system("pause");
	cout << "3.函数：" << endl
		<< "arcsin(x)\t\t\t反三角函数（下同）" << endl
		<< "arcos(x)" << endl
		<< "arctan(x)" << endl
		<< "sin(x)\t\t\t三角函数（下同）" << endl
		<< "cos(x)" << endl
		<< "tan(x)" << endl
		<< "sinh(x)\t\t\t双曲函数（下同）" << endl
		<< "cosh(x)" << endl
		<< "tanh(x)" << endl
		<< "log(x,nBase)\t\t\t以nBase为底，x的对数" << endl
		<< "log10(x)\t\t\t以10为底，x的对数" << endl
		<< "ln(x)\t\t\t以自然对数为底，x的对数" << endl
		<< "pow(x,nPower)\t\t\tx的nPower次方" << endl
		<< "exp(x)\t\t\te的x次方" << endl
		<< "fact(x)\t\t\tx的阶乘（x会被强制转为整数）" << endl
		<< "sqrt(x)\t\t\tx的算术平方根（x为非负数）" << endl
		<< "cuberoot(x)\t\t\tx的三次方根" << endl
		<< "yroot(x)\t\t\tx的y次方根" << endl << endl;
	system("pause");
	cout << "4.统计" << endl
		<< "avg[……]\t\t\t集合的算术平均值（元素用,分隔，下同）\t\t（至少1个参数）" << endl
		<< "sum[……]\t\t\t集合的统计\t\t（至少1个参数）" << endl
		<< "var[……]\t\t\t集合的估计方差\t\t（至少2个参数）" << endl
		<< "varp[……]\t\t\t集合的总体方差\t\t（至少1个参数）" << endl
		<< "stdev[……]\t\t\t集合的估计标准差\t\t（至少2个参数）" << endl
		<< "stdevp[……]\t\t\t集合的总体标准差\t\t（至少1个参数）" << endl << endl;
	system("pause");
	cout << "二、错误信息" << endl << endl
		<< "输入非法\t\t\t原因" << endl
		<< "\t\t\t\t输入函数参数个数不匹配\tsin(2,3)   var[2.3]" << endl
		<< "\t\t\t\t运算符之间的关系非法\t2+*6   5/+7" << endl
		<< "\t\t\t\t函数名错误\tsim(5)   poe(9)" << endl
		<< "运算错误\t\t\t原因" << endl
		<<"\t\t\t\t输入了非法运算\t5/0    sqrt(-3)" << endl << endl;
}

void SC_CALC::calc_set()
{
	cout << "set功能" << endl
		<< "若设置一个已有的set名，将会覆盖此值" << endl;
	cout << "set名:" << flush;
	string name, value;
	getline(cin, name);
	cout << "set值：" << flush;
	getline(cin, value);
	string::size_type len = name.size();
	int c = 'a' - 'A';
	//将大写字母转为小写
	for (string::size_type i = 0; i < len; ++i)
	{
		if (name[i] >= 'A'&&name[i] <= 'Z')
		{
			name[i] += c;
		}
	}
	//消除空格
	for (string::iterator p = name.begin(); p !=name.end(); ++p)
	{
		if (*p == ' ' || *p == '\t')
		{
			p = --name.erase(p);
		}
	}
	len = value.size();
	for (string::size_type i = 0; i < len; ++i)
	{
		if (value[i] >= 'A'&&value[i] <= 'Z')
		{
			value[i] += c;
		}
	}
	//消除空格
	for (string::iterator p = value.begin(); p != value.end(); ++p)
	{
		if (*p == ' ' || *p == '\t')
		{
			p = --value.erase(p);
		}
	}
	calc_const[name] = value;
	cout << "设置/修改成功！" <<endl<< endl;
}