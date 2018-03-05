// TestApp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../../TestDll/TestDll/head.h"
#pragma comment(lib,"../Debug/TestDll.lib")


int main()
{
	MsgBox(_T("title"), _T("content"));
	testClass A;
	A.outputMessage(_T("aaaaaaaa"));
    return 0;
}

