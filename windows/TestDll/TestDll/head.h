#pragma once
#define _DLL_EXPORTS

#ifdef _DLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

MYDLL_API void MsgBox(const wchar_t*title, const wchar_t*content);

class MYDLL_API testClass
{
public:
	void outputMessage(const wchar_t*msg);
};