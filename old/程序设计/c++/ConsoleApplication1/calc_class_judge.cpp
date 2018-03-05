#include "calc_class.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//构造函数
SC_CALC::SC_CALC()
{
	calc_db_op_list.push_back('+');
	calc_db_op_list.push_back('-');
	calc_db_op_list.push_back('*');
	calc_db_op_list.push_back('/');
	calc_db_op_list.push_back('^');
	calc_db_op_list.push_back('r');
	calc_db_op_list.push_back('%');
	calc_db_op_list.push_back('(');
	calc_db_op_list.push_back(')');
	calc_db_op_list.push_back('#');
	//初始化双目运算符优先级
	calc_db_op_table.insert(make_pair(make_pair('+', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('+', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('+', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('+', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('+', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('+', '%'), '<'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('-', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('-', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('-', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('-', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('-', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('-', '%'), '<'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('*', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '/'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('*', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('*', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('*', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('*', '%'), '>'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('/', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '/'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('/', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('/', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('/', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('/', '%'), '>'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('(', '+'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '-'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', ')'), '='));
//	calc_db_op_table.insert(make_pair(make_pair('(', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('(', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('(', '%'), '<'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair(')', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '/'), '>'));
//	calc_db_op_table.insert(make_pair(make_pair(')', '('), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', 'r'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '^'), '>'));
	calc_db_op_table.insert(make_pair(make_pair(')', '%'), '>'));
	//////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('r', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '/'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('r', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', 'r'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '^'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('r', '%'), '>'));
	/////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('^', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '*'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '/'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('^', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', 'r'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '^'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('^', '%'), '>'));
	/////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('#', '+'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '-'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '('), '<'));
//	calc_db_op_table.insert(make_pair(make_pair('#', ')'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '#'), '='));
	calc_db_op_table.insert(make_pair(make_pair('#', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('#', '%'), '<'));
	///////////////////////////////////////////////////////////////////////
	calc_db_op_table.insert(make_pair(make_pair('%', '+'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('%', '-'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('%', '*'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', '/'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', '('), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', ')'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('%', '#'), '>'));
	calc_db_op_table.insert(make_pair(make_pair('%', 'r'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', '^'), '<'));
	calc_db_op_table.insert(make_pair(make_pair('%', '%'), '>'));
	//初始化单目运算符列表（统计运算归为单目运算，开方运算归为双目运算），顺序按运算符长度排列
	calc_sg_op_list.push_back("arcsin(");
	calc_sg_op_list.push_back("arctan(");
	calc_sg_op_list.push_back("stdevp[");
	calc_sg_op_list.push_back("arcos(");
	calc_sg_op_list.push_back("log10(");
	calc_sg_op_list.push_back("stdev[");
	calc_sg_op_list.push_back("varp[");
	calc_sg_op_list.push_back("sinh(");
	calc_sg_op_list.push_back("cosh(");
	calc_sg_op_list.push_back("tanh(");
	calc_sg_op_list.push_back("fact(");
	calc_sg_op_list.push_back("sin(");
	calc_sg_op_list.push_back("cos(");
	calc_sg_op_list.push_back("tan(");
	calc_sg_op_list.push_back("log(");
	calc_sg_op_list.push_back("pow(");
	calc_sg_op_list.push_back("exp(");
	calc_sg_op_list.push_back("avg[");
	calc_sg_op_list.push_back("sum[");
	calc_sg_op_list.push_back("var[");
	calc_sg_op_list.push_back("ln(");
	//初始化单目运算符参数个数,负数a表示至少应有（-a）个参数
	min_argu.insert(make_pair("cuberoot(", 1));
	min_argu.insert(make_pair("arcsin(", 1));
	min_argu.insert(make_pair("arctan(", 1));
	min_argu.insert(make_pair("stdevp[", -1));
	min_argu.insert(make_pair("arcos(", 1));
	min_argu.insert(make_pair("log10(", 1));
	min_argu.insert(make_pair("stdev[", -2));
	min_argu.insert(make_pair("varp[", -1));
	min_argu.insert(make_pair("sinh(", 1));
	min_argu.insert(make_pair("cosh(", 1));
	min_argu.insert(make_pair("tanh(", 1));
	min_argu.insert(make_pair("fact(", 1));
	min_argu.insert(make_pair("sqrt(", 1));
	min_argu.insert(make_pair("sin(", 1));
	min_argu.insert(make_pair("cos(", 1));
	min_argu.insert(make_pair("tan(", 1));
	min_argu.insert(make_pair("log(", 2));
	min_argu.insert(make_pair("pow(", 2));
	min_argu.insert(make_pair("exp(", 1));
	min_argu.insert(make_pair("arg[", -1));
	min_argu.insert(make_pair("sum[", -1));
	min_argu.insert(make_pair("var[", -2));
	min_argu.insert(make_pair("ln(", 1));
}


//输入函数
void SC_CALC::calc_input()
{
	cout << ">>" << flush;
	getline(cin, calc_expression);
}
void SC_CALC::calc_input(string str)
{
	calc_expression = str;
}

void SC_CALC::calc_replace()
{
	string::size_type start_loc;
	while ((start_loc = calc_expression.find("ans")) != string::npos)
	{
		if (calc_history_res.empty() || calc_history_res.back() == "运行错误")
		{
			calc_expression.replace(start_loc, ((string)"ans").size(), "(0)");
		}
		else
		{

			calc_expression.replace(start_loc, ((string)"ans").size(), "(" + calc_history_res.back() + ")");
		}
	}

	for (map<string, string>::iterator p = calc_const.begin(); p != calc_const.end();++p)
	{
		while ((start_loc = calc_expression.find(p->first)) != string::npos)
		{
			calc_expression.replace(start_loc, (p->first).size(), p->second);
		}
	}
}

//输出函数
void SC_CALC::calc_output()
{
	string ops = calc_calc(calc_expression);
	for (string::iterator p = ops.begin(); p != ops.end(); ++p)
	{
		//非数字
		if ((*p<'0' || *p>'9') &&*p != '-'&&*p != 'e'&&*p!='.'&&*p!='('&&*p!=')')
		{
			ops= "运算错误";
			break;
		}
	}
	//去掉头尾括号
	if (ops.back() == ')')
	{
		ops.erase(ops.begin());
		ops.pop_back();
		//转为习惯阅读的格式（首尾添0）
		if (ops.front() == '.')
		{
			ops = "0" + ops;
		}
		if (ops.back() == '.')
		{
			ops += "0";
		}
	}
	//将格式化的结果存入历史结果
	calc_history_res.push_back(ops);
	cout <<"=" <<ops << endl<<endl;
}


void SC_CALC::calc_format()
{
	string::size_type len = calc_expression.size();
	int c = 'a' - 'A';
	//将大写字母转为小写
	for (string::size_type i = 0; i < len;++i)
	{
		if (calc_expression[i]>='A'&&calc_expression[i]<='Z')
		{
			calc_expression[i] += c;
		}
	}
	//消除空格
	for (string::iterator p = calc_expression.begin(); p != calc_expression.end();++p)
	{
		if (*p==' '||*p=='\t')
		{
			p=--calc_expression.erase(p);
		}
	}
	calc_replace();
	//将格式化的算式存入历史记录
	calc_history_equ.push_back(calc_expression);
	//将开方运算及模运算转为二元运算
	string::size_type start_loc;
	while ((start_loc = calc_expression.find("cuberoot")) != string::npos)
	{
		calc_expression.replace(start_loc, ((string)"cuberoot").size(), "3r");
	}
	while ((start_loc = calc_expression.find("sqrt")) != string::npos)
	{
		calc_expression.replace(start_loc, ((string)"sqrt").size(), "2r");
	}
	while ((start_loc = calc_expression.find("root")) != string::npos)
	{
		calc_expression.replace(start_loc, ((string)"root").size(), "r");
	}
	while ((start_loc = calc_expression.find("mod")) != string::npos)
	{
		calc_expression.replace(start_loc, ((string)"mod").size(), "%");
	}
#ifndef NDEBUG
	cout << "mult_format----calc_expression:" << calc_expression << endl;
#endif
}

//判断输入是否合法
bool SC_CALC::calc_judge()
{
	//格式化
	calc_format();
	//括号不匹配
	if (!bracket_match(calc_expression))return false;
	//除运算符和数字有其他字符
	if (!excess_sym(calc_expression))return false;
	//运算符间的关系不合法
	if (!op_pass(calc_expression))return false;
	//运算符参数个数不合法
	if (!argu_num(calc_expression))return false;
	return true;
}

//括号匹配判断函数
bool SC_CALC::bracket_match(string str)
{
	vector<char> inn;
	for (string::iterator p = str.begin(); p != str.end(); ++p)
	{
		//遇到左括号，压入栈中
		if (*p=='['||*p=='(')
		{
			inn.push_back(*p);
		}
		else
		{
			switch (*p)
			{
				//遇到右括号，与栈顶比较，匹配则退栈，否则返回false
			case ']':
				if (!inn.empty()&& inn.back() == '[')inn.pop_back();
				else return false;
				break;
			case ')':
				if (!inn.empty() && inn.back() == '(')inn.pop_back();
				else return false;
				break;
			default:break;
			}
		}
	}
	//栈空则匹配
	return inn.empty();
}

//多余符号检测函数
bool SC_CALC::excess_sym(string str)
{
	string::size_type start_loc;
	//删除函数
	for (vector<string>::iterator p = calc_sg_op_list.begin(); p != calc_sg_op_list.end();++p)
	{
		while ((start_loc = str.find(*p)) != string::npos)
		{
			str.erase(start_loc,(*p).size());
		}
	}
	//删除运算符
	for (vector<char>::iterator p = calc_db_op_list.begin(); p != calc_db_op_list.end();++p)
	{
		while ((start_loc = str.find(*p)) != string::npos)
		{
			str.erase(start_loc,  1);
		}
	}
	//删除逗号，
	while ((start_loc = str.find(",")) != string::npos)
	{
		str.erase(start_loc, 1);
	}
	//删除]
	while ((start_loc = str.find("]")) != string::npos)
	{
		str.erase(start_loc, 1);
	}
	//删除)
	while ((start_loc=str.find(")"))!=string::npos)
	{
		str.erase(start_loc, 1);
	}
	//删除e
	while ((start_loc = str.find("e")) != string::npos)
	{
		str.erase(start_loc, 1);
	}
	//删除.
	while ((start_loc = str.find(".")) != string::npos)
	{
		str.erase(start_loc, 1);
	}
#ifndef NDEBUG
	cout << "excess_sym----str:" << str << endl;
#endif
	for (string::iterator p = str.begin(); p != str.end();++p)
	{
		//除数字外还有其它字符则不合法
		if (*p<'0' || *p>'9')return false;
	}
	return true;
}

//运算符关系判断
bool SC_CALC::op_pass(string str)
{
	//前后加开始、结束标记
	str += "#";
	str = "#" + str;
	map<int, string> loc_sym;
	string::size_type start_loc;
	//记录函数位置
	//从后向前搜索，确保长函数名不会被截断
	long sg_num = calc_sg_op_list.size();
	for (long i = sg_num - 1; i >= 0;--i)
	{
		start_loc = -1;
		while ((start_loc = str.find(calc_sg_op_list[i],start_loc+1)) != string::npos)
		{
			loc_sym[start_loc] = calc_sg_op_list[i];
		}
	}
	vector<int> func;
	string last_sym("num");
	string::size_type sym_num=str.size();
	/*************************************************************************/
	/*num:数字	#：# db：运算符  sg：函数 （：（  ）：） ]：]					 */
	/*************************************************************************/
	for (string::size_type i = 0; i < sym_num;++i)
	{
		if (str[i] >= '0'&&str[i] <= '9')
		{
			//数字前不能有右括号
			if (last_sym == ")" || last_sym == "]")
			{
				return false;
			}
			//置状态为数字
			else
			{
				last_sym = "num";
			}
		}
		else
		{
			switch (str[i])
			{
			case '+':
			case '-':
				//‘+’，‘-’前不能有运算符
				if (last_sym == "db" || last_sym == ".")
				{
					return false;
				}
				else
				{
					last_sym = "db";
				}
				break;
			case '*':
			case '/':
			case 'r':
			case '%':
			case '^':
				//运算符前不能有‘#’，运算符，‘.’，函数，‘，’
				if (last_sym == "#" || last_sym == "db" || last_sym == "." || last_sym == "sg" || last_sym == ",")
				{
					return false;
				}
				else
				{
					last_sym = "db";
				}
				break;
			case '#':
				if (last_sym == "#" || last_sym == "db" || last_sym == "." || last_sym == "sg" || last_sym == ",")
				{
					return false;
				}
				else
				{
					last_sym = "#";
				}
				break;
			case '(':
				if (last_sym == "num" || last_sym == "." || last_sym == ")"||last_sym=="]")
				{
					return false;
				}
				else
				{
					last_sym = "(";
					if (!func.empty())
					{
						func.push_back(0);
					}
				}
				break;
			case ')':
				if (last_sym == "db" || last_sym == "#" || last_sym == "sg" || last_sym == "." || last_sym == ",")
				{
					return false;
				}
				else
				{
					if (!func.empty()&&func.back()!=2)
					{
						func.pop_back();
					}
					else
					{
						if (!func.empty())
						{
							return false;
						}
					}
					last_sym = ")";
				}
				break;
			case '.':
				if (last_sym==")"||last_sym=="."||last_sym=="]")
				{
					return false;
				}
				else
				{
					last_sym = ".";
				}
				break;
			case ',':
				if (last_sym == "db" || last_sym == "sg" || last_sym == "." || last_sym == "#" || last_sym == ",")
				{
					return false;
				}
				else
				{
					if (func.empty()||func.back()==0)
					{
						return false;
					}
					else
					{
						last_sym = ",";
					}
				}
				break;
			case ']':
				if (last_sym == "(" || last_sym == "db" || last_sym == "sg" || last_sym == "." || last_sym == "#" || last_sym == ",")
				{
					return false;
				}
				else
				{
					if (func.empty()||func.back()!=2)
					{
						return false;
					}
					else
					{
						last_sym = "]";
						func.pop_back();
					}
				}
				break;
				//对e特殊处理
			case 'e':
				if (loc_sym[i]=="")
				{
					loc_sym.erase(i);
					if (last_sym == ")" || last_sym == "]"||last_sym=="#"||last_sym=="db"||last_sym=="sg"||last_sym==",")
					{
						return false;
					}
					else
					{
						last_sym = "num";
					}
					break;
				}
			default:
				if (last_sym == "." || last_sym == ")" || last_sym == "]")
				{
					return false;
				}
				else
				{
					if (loc_sym[i][loc_sym[i].size() - 1] == '(')
					{
						func.push_back(1);
					}
					else
					{
						func.push_back(2);
					}
					i += loc_sym[i].size()-1;
					last_sym = "sg";
				}
				break;
			}
		}
	}
#ifndef NDEBUG
	cout << "op_pass----str:" << str << endl;
#endif
	return func.empty();
}

//参数个数判断
bool SC_CALC::argu_num(string str)
{
	map<int, string> loc_sym;
	string::size_type start_loc;
	//从后向前搜索，确保长符号不会被截断
	long sg_num = calc_sg_op_list.size();
	for (long i = sg_num - 1; i >= 0; --i)
	{
		start_loc = -1;
		while ((start_loc = str.find(calc_sg_op_list[i], start_loc + 1)) != string::npos)
		{
			loc_sym[start_loc] = calc_sg_op_list[i];
		}
	}
	int bracket_num;
	int argu;
	for (map<int, string>::iterator p = loc_sym.begin(); p != loc_sym.end(); ++p)
	{
		bracket_num = 1;
		argu = 0;
		for (int j = p->first+p->second.size() + 1; j < str.size(); ++j)
		{
			switch (str[j])
			{
			case '[':
			case '(':
				++bracket_num;
				break;
			case ']':
			case ')':
				--bracket_num;
				break;
			case ',':
				if (bracket_num==1)
				{
					++argu;
				}
				break;
			}
			if (bracket_num == 0)
			{
				++argu;
				if (min_argu[p->second]>0)
				{
					if (min_argu[p->second]!=argu)
					{
						return false;
					}
					break;
				}
				else
				{
					if (0-min_argu[p->second]>argu)
					{
						return false;
					}
					break;
				}
			}
		}
	}
	return true;
}