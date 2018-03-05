#include "calc_class.h"
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <sstream>


using namespace std;


string SC_CALC::calc_calc(string str)
{
	string::size_type start_loc;
	string temp_result;
	//从后向前搜索，确保长符号不会被截断
	long sg_num = calc_sg_op_list.size();
	int bracket_num;
	//计算所有的函数
	for (long i = 0; i <sg_num; ++i)
	{
		while ((start_loc = str.find(calc_sg_op_list[i])) != string::npos)
		{
			bracket_num=1;
				for (int j = start_loc + calc_sg_op_list[i].size() + 1; j < str.size();++j)
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
					}
				if (bracket_num==0)
				{
					temp_result.assign(str.begin() + start_loc, str.begin() + j + 1);
					temp_result = mult_calc(temp_result,calc_sg_op_list[i]);
					if (temp_result!="计算错误")
					{
						str.replace(start_loc, j - start_loc+1, temp_result);
						break;
					}
					else
					{
						return temp_result;
					}
				}
			}
		}
	}
	return easy_calc(str);
}

string SC_CALC::mult_calc(string str,string func)
{
#ifndef NDEBUG
	cout<<"mult_calc----str:" << str << endl;
#endif
	string::size_type func_len = func.size();
	string argu(str.begin()+func_len,str.end()-1);
	vector<string> argu_part;
	string argu_temp;
	int sta(0);
	//获取参数
	for (string::iterator p = argu.begin(); p != argu.end();++p)
	{
		switch (*p)
		{
		case '(':
		case '[':
			++sta;
			argu_temp.push_back(*p);
			break;
		case ')':
		case ']':
			--sta;
			argu_temp.push_back(*p);
			break;
		case ',':
			if (sta==0)
			{
#ifndef NDEBUG
				cout << "mult_calc----argu_temp:" << argu_temp << endl;
#endif
				argu_part.push_back(argu_temp);
				argu_temp.clear();
				break;
			}
		default:
			argu_temp.push_back(*p);
			break;
		}
	}
#ifndef NDEBUG
	cout << "mult_calc----argu_temp:" << argu_temp << endl;
#endif
	//最后一个参数
	argu_part.push_back(argu_temp);
	//递归计算，得到最简多项式
	for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end();++p)
	{
		*p = calc_calc(*p);
		if (*p=="运算错误")
		{
			return *p;
		}
		else
		{
			p->erase(p->begin());
			p->pop_back();
		}
	}
	//各种函数的计算
	if (func=="sin(")
	{
#ifndef NDEBUG
		cout << "mult_calc----sin_src:" << argu_part[0] << endl;
#endif
		double s = atof(argu_part[0].c_str());
#ifndef NDEBUG
		cout << "mult_calc----sin_argu:" << s << endl;
#endif
		char result[40];
		if (_gcvt_s(result, 40, sin(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
#ifndef NDEBUG
			cout << "mult_calc----sin_result:" << result << endl;
#endif
			return "(" + (string)result + ")";
		}
	}
	else if (func == "cos(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, cos(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "tan(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, tan(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "arcsin(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, asin(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "arcos(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, acos(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "arctan(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, atan(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "sinh(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, sinh(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "cosh(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, cosh(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "tanh(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, tanh(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "log10(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, log10(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "ln(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, log(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "exp(")
	{
		double s = atof(argu_part[0].c_str());
		char result[40];
		if (_gcvt_s(result, 40, exp(s), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "fact(")
	{
		long s = atol(argu_part[0].c_str());
		double factorial(1.0);
		for (long i = s; i > 1;--i)
		{
			factorial *= i;
		}
		char result[40];
		if (_gcvt_s(result, 40,factorial, 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "log(")
	{
		double a = atof(argu_part[0].c_str());
		double b = atof(argu_part[1].c_str());
		char result[40];
		if (_gcvt_s(result, 40, log(a) / log(b), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "pow(")
	{
		double a = atof(argu_part[0].c_str());
		double b = atof(argu_part[1].c_str());
		char result[40];
		if (_gcvt_s(result, 40, calc_pow(a, b), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "avg[")
	{
		double avg(0);
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end();++p)
		{
			avg += atof(p->c_str());
		}
		avg /= argu_part.size();
		char result[40];
		if (_gcvt_s(result, 40, avg, 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "sum[")
	{
		double sum(0);
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			sum =sum+ atof(p->c_str());
		}
		char result[40];
		if (_gcvt_s(result, 40, sum, 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "varp[")
	{
		double avg(0);
		int n = argu_part.size();
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			avg += atof(p->c_str());
		}
		avg /= n;
		double variance(0);
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			variance += (avg - atof(p->c_str()))*(avg - atof(p->c_str()));
		}
		char result[40];
		if (_gcvt_s(result, 40, variance / n, 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "var[")
	{
		double avg(0);
		int n = argu_part.size();
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			avg += atof(p->c_str());
		}
		avg /= n;
		double variance(0);
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			variance += (avg - atof(p->c_str()))*(avg - atof(p->c_str()));
		}
		char result[40];
		if (_gcvt_s(result, 40, variance / (n-1), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "stdevp[")
	{
		double avg(0);
		int n = argu_part.size();
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			avg += atof(p->c_str());
		}
		avg /= n;
		double variance(0);
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			variance += (avg - atof(p->c_str()));
		}
		char result[40];
		if (_gcvt_s(result, 40, sqrt(variance / n), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else if (func == "stdev[")
	{
		double avg(0);
		int n = argu_part.size();
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			avg += atof(p->c_str());
		}
		avg /= n;
		double variance(0);
		for (vector<string>::iterator p = argu_part.begin(); p != argu_part.end(); ++p)
		{
			variance += (avg - atof(p->c_str()))*(avg - atof(p->c_str()));
		}
		char result[40];
		if (_gcvt_s(result, 40,sqrt( variance / (n-1)), 30) != 0)
		{
			return "运算错误";
		}
		else
		{
			return "(" + (string)result + ")";
		}
	}
	else
	{
		return "运算错误";
	}
}

string SC_CALC::easy_calc(string str)
{
	//检测是否为非数
	for (string::iterator p = str.begin(); p != str.end();++p)
	{
		if ((*p<'0' || *p>'9') && *p != '('&&*p != ')'&&*p != '+'&&*p != '-'&&*p != '*'&&*p != '/'&&*p != 'r'&&*p != '^'&&*p != 'e'&&*p != '%'&&*p!='.')
		{
			return "运算错误";
		}
	}
	//加结束标记
	str += "#";
	istringstream si(str);
	vector<char> op;
	op.push_back('#');
	vector<double> num;
	string temp_num;
	double a, b;
	char op_run;
	char c;
	bool is_num(false);
	bool e_n(false);
	while (si >> c)
	{
		//数字或点
		if (c>='0'&&c<='9'||c=='.')
		{
			temp_num.push_back(c);
			is_num = true;
			e_n = false;
		}
		//e
		else if (c=='e')
		{
			e_n = true;
			temp_num.push_back(c);
			is_num = true;
		}
		else
		{
			//e后的‘+’，‘-’号
			if ((c == '-'||c=='+')&&e_n == true)
			{
				temp_num.push_back(c);
				is_num = true;
				e_n = false;
				continue;
			}
			else
			{
				if (is_num)
				{
					num.push_back(atof(temp_num.c_str()));
					temp_num.clear();
				}
				else
				{
					if (op.back() == '(')
					{
						num.push_back(0.0);
					}
				}
			}
			is_num = false;
			e_n = false;
			switch (calc_db_op_table[make_pair(op.back(),c)])
			{
				//前一个运算符优先级低，不计算
			case '<':
				op.push_back(c);
				break;
				//优先级别相同，括号或结束标志，退栈
			case '=':
				op.pop_back();
				break;
			case '>':
				//优先级高，循环计算
				while (true)
				{
					if (calc_db_op_table[make_pair(op.back(),c)]=='<')
					{
						op.push_back(c);
						break;
					}
					else if (calc_db_op_table[make_pair(op.back(), c)] == '=')
					{
						op.pop_back();
						break;
					}
					else if (calc_db_op_table[make_pair(op.back(), c)] == '>')
						//在数字栈头部加0，避免第一个字符是‘+’或‘-’
						num.insert(num.begin(), 0);
					//取运算数字
						b = num.back();
						num.pop_back();
						a = num.back();
						num.pop_back();
						op_run = op.back();
						op.pop_back();
						switch (op_run)
						{
						case '+':
							num.push_back(a + b);
							break;
						case '-':
							num.push_back(a-b);
							break;
						case '*':
							num.push_back(a * b);
							break;
						case '/':
							if (b!=0)
							{
								num.push_back(a / b);
							}
							else return "运算错误";
							break;
						case '%':
							if (b != 0)
							{
								num.push_back((long)a %(long) b);
							}
							else return "运算错误";
							break;
						case '^':
							//改进后的pow函数，支持负数开小数次方
							num.push_back(calc_pow(a,b));
							break;
						case 'r':
							if (a == 0 && a == 0)
							{
								return "运算错误";
							}
							else
							{
								if (a==0)
								{
									num.push_back(1.0);
								}
								else
								{
									num.push_back(calc_pow(b,1.0/a));
								}
							}
							break;
						default:break;
						}
				}
			default: break;
			}
		}
	}
	char result[40];
	if (_gcvt_s(result, 40, num.back(), 30) != 0)
	{
		return "运算错误";
	}
	else
	{
		return "(" + (string)result + ")";
	}
}

//改进的pow(double,double);
double SC_CALC::calc_pow(double a, double b)
{
	if ((double)(int)b==b)
	{
		return pow(a, (int)b);
	}
	else
	{
		if (a>=0.0)
		{
			return pow(a, (int)b);
		}
		else
		{
			int c, d;
			double temp;
			//将小数b表示为分数形式，c为分子，d为分母
			dectosc(b, c, d);
			temp = pow(a, c);
			
			if (c%2==1)
			{
				if (d%2==0)
				{
					return pow(temp, 1.0 / d);
				}
				else
				{
					return -pow((-temp), 1.0/d);
				}
			}
			else
			{
				return pow(temp,1.0/d);
			}

		}
	}
}

//小数转分数
void SC_CALC::dectosc(double d, int &z, int &m)
{
	//精度
	const double PRECISION = 0.0001;
	for (m = 1;;++m)
	{
		z = d*m;
		if (fabs((double)z/(double)m-d)<PRECISION)
		{
			break;
		}
	}
}