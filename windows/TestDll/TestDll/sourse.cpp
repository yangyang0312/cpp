#include "stdafx.h"
#include "head.h"

 void MsgBox(const wchar_t*title, const wchar_t*content)
{
	MessageBox(NULL, title, content, MB_OK);
}

 void testClass::outputMessage(const wchar_t*msg)
 {
	 OutputDebugString(msg);
 }