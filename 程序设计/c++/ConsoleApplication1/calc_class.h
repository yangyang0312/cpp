#ifndef _CALC_DATASTRUCT_H_
#define _CALC_DATASTRUCT_H_ 1
#include <vector>
#include <string>
#include <map>
using namespace std;
class SC_CALC
{
public:
	//构造函数
	SC_CALC();
	//输入
	void calc_input();
	void calc_input(string);
	//判断输入合法性
	bool calc_judge();
	//输出
	void calc_output();
	//其他命令
	bool is_cmd();
	//历史算式
	vector<string> calc_history_equ;
	//历史结果
	vector<string> calc_history_res;
private:
	//单目运算符列表
	vector<string> calc_sg_op_list;
	//双目运算符列表
	vector<char> calc_db_op_list;
	//多目运算符优先级列表
	map<pair<char,char>, char> calc_db_op_table;
	//表达式字符串
	string calc_expression;
	//格式化表达式字符串函数
	void calc_format();
	//括号匹配判断函数
	bool bracket_match(string);
	//多余符号判断函数
	bool excess_sym(string);
	//运算符关系合法判断函数
	bool op_pass(string);
	//运算符参数个数合法判断
	bool argu_num(string);
	//计算主算法
	string calc_calc(string);
	//只含有双目运算符的计算
	string easy_calc(string);
	//含有单目运算符的计算
	string mult_calc(string,string);
	//参数个数
	map<string, int> min_argu;
	//显示历史
	void calc_history();
	//显示帮助
	void calc_help();
	//改进的乘方函数
	double calc_pow(double,double);
	//小数转分数
	void dectosc(double, int&, int&);
	//替换
	void calc_replace();
	//常量式
	map<string, string> calc_const;
	//set功能
	void calc_set();
};
#endif