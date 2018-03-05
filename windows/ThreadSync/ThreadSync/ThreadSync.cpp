// ThreadSync.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

typedef void (*OPFunc)();

CRITICAL_SECTION		g_cs;
SRWLOCK					g_SRWlock;
volatile LONG			gv_num = 0;
LONG					g_num = 0;
HANDLE					g_hMutex;
const static ULONG		gcs_count = 1000000;

void FuncVolatileRead()
{
	auto iRead = gv_num;
}

void FuncVolatileWrite()
{
	gv_num = 1;
}

void FuncInterlock()
{
	InterlockedAdd(&g_num, 2); 
}

void FuncCriticalSection()
{
	EnterCriticalSection(&g_cs);
	++g_num;
	LeaveCriticalSection(&g_cs);
}

void FuncSRWLockRead()
{
    AcquireSRWLockShared(&g_SRWlock);
	auto iRead = g_num;
    ReleaseSRWLockShared(&g_SRWlock);
}

void FuncSRWLockWrite()
{
	AcquireSRWLockExclusive(&g_SRWlock);
	g_num = 1;
	ReleaseSRWLockExclusive(&g_SRWlock);
}

void FuncMutex()
{
	WaitForSingleObject(g_hMutex, INFINITE);
	g_num = 0;
	ReleaseMutex(g_hMutex);
}

DWORD WINAPI LoopFunc(PVOID param)
{
    auto opFunc = (OPFunc)param;
	for (int i = 0; i < gcs_count; ++i)
		opFunc();
    return 0;
}

void WaitFuncComplete(const int threadNum , OPFunc opFunc)
{
    std::cout << "threadNum: " << threadNum << " time: ";
	HANDLE * phThread = new HANDLE[threadNum];
    for(int i = 0;i < threadNum;++i)
    {
        phThread[i] = CreateThread(NULL,0,LoopFunc,opFunc,0,NULL);
    }

    LARGE_INTEGER freq,start,end;   //计时
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    WaitForMultipleObjects(threadNum,phThread,TRUE,INFINITE);
    QueryPerformanceCounter(&end);
    LONGLONG time = ((end.QuadPart - start.QuadPart) * 1000) / freq.QuadPart;
    std::cout << std::setw(6) << time << "ms" << std::endl;

    for(int i = 0;i < threadNum;++i)
        CloseHandle(phThread[i]);
    delete phThread;
    phThread = NULL;
}

int main()
{
    InitializeCriticalSectionAndSpinCount(&g_cs,4000);
    InitializeSRWLock(&g_SRWlock);
    g_hMutex = CreateMutex(NULL,FALSE,NULL);
	for (int i = 1; i < 17; i *= 2)
    {
        std::cout << std::left << std::setw(16) << "Volatile Read ";
        WaitFuncComplete(i,FuncVolatileRead);
        std::cout << std::setw(16) << "Volatile Write ";
        WaitFuncComplete(i,FuncVolatileWrite);
        std::cout << std::setw(16) << "Interlock ";
        WaitFuncComplete(i,FuncInterlock);
        std::cout << std::setw(16) << "CriticalSection ";
        WaitFuncComplete(i,FuncCriticalSection);
        std::cout << std::setw(16) << "SRWLock Read ";
        WaitFuncComplete(i,FuncSRWLockRead);
        std::cout << std::setw(16) << "SRWLock Write ";
        WaitFuncComplete(i,FuncSRWLockWrite);
        std::cout << std::setw(16) << "Mutex ";
        WaitFuncComplete(i,FuncMutex);
        std::cout << std::endl;
	}
    DeleteCriticalSection(&g_cs);
    CloseHandle(g_hMutex);
    getchar();
    return 0;
}