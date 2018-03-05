#include "calc_class.h"
#include <iostream>

using namespace std;

void start_calc(SC_CALC&);

int main(int argc,char **argv)
{
	system("title SC_Calculator For GrapeCity");
	SC_CALC living;
	if (argc==1)
	{
		cout << "键入hlp查看帮助。" << endl << endl;
		while (true)
		{
			start_calc(living);
		}
	}
	else
	{
		string argu=argv[1];
		for (int i = 2; i < argc;++i)
		{
			argu += argv[i];
		}
		living.calc_input(argu);
		if (!living.is_cmd())
		{
			if (living.calc_judge())
			{
				living.calc_output();
			}
			else
			{
				living.calc_history_equ.pop_back();
				cout << "输入非法"<<endl << endl;
			}
		}
	}
	return 0;
}

void start_calc(SC_CALC &living)
{
	living.calc_input();
	if (!living.is_cmd())
	{
		if (living.calc_judge())
		{
			living.calc_output();
		}
		else
		{
			living.calc_history_equ.pop_back();
			cout << "输入非法"<<endl << endl;
		}
	}
}
