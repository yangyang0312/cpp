#pragma once
#include "../PaperEditor/PaperStruct.h"

//解析htm，生成试卷答案
class CAnalyzeHtm
{
public:
	CAnalyzeHtm();
	~CAnalyzeHtm();

public:
	//获取试卷答案
	VOID GetPaperAnswer(stuPaper & answer,const stuPaper & paper,CDHtmlDialog * dlg);

private:
	//获取指定ID的 html 或者 text，<p><h><textArea>标签等
	BOOL GetElementText(CString & str,const CString & id,CDHtmlDialog * dlg);
	//获取指定ID的 Input 控件的值，如输入框
	BOOL GetInputElementText(CString & str,const CString & id,CDHtmlDialog * dlg);
	//获取指定ID的 checkbox 控件的 check 状态 返回 TRUE：checked FALSE:unchecked
	BOOL GetCheckElementState(const CString & id,CDHtmlDialog * dlg);
};

