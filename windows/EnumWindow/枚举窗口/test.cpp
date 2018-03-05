#include <windows.h>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

//子窗口回调函数
BOOL CALLBACK EnumChildWindowsProc(HWND hwnd,LPARAM lParam)
{
	char title[100] = { 0 };
	GetWindowTextA(hwnd, title, 100);
	if (strlen(title)>0)
		cout <<hex<<"句柄："<<hwnd<<"  标题："<<title << endl;
	return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char title[100] = { 0 };
	GetWindowTextA(hwnd, title, 100);
	if (strlen(title) > 0)
		cout << hex << "句柄：" << hwnd << "  标题：" << title << endl;
	EnumChildWindows(hwnd, EnumChildWindowsProc, NULL);
	return true;
}

BOOL myEnumWindow(HWND hwnd)
{
	char title[100] = { 0 };
	HWND after = NULL;
	while (after = ::FindWindowEx(hwnd, after, NULL, NULL))
	{
		GetWindowTextA(after, title, 100);
		if(strlen(title)>0)
			cout <<"句柄："<<hex<< after<<"  标题：" << title <<endl;
		myEnumWindow(after);
	}
	return true;
}

int main()
{
	HWND handle = NULL;
	FindWindow(NULL, "任务管理器");//查找特定窗口的窗口句柄
	RECT rect;
	int width, height;
	if (handle)
	{
		GetWindowRect(handle, &rect);//获取窗口信息
		width = rect.right - rect.left, height = rect.bottom - rect.top;
		cout << "宽: " << width << endl << "高: " << height << endl;
		cout << MoveWindow(handle, 100, 100, width, height, true) << endl;
	}
	//获取所有顶层可见窗口及他们的子窗口
	EnumWindows(EnumWindowsProc, NULL);

	cout << endl << endl << "第二种方法：" << endl;
	myEnumWindow(NULL);//使用FindWindowEx枚举窗口

	getchar();
	getchar();
	return 0;
}