#include "stdafx.h"
#include "AnalyzeHtm.h"

CAnalyzeHtm::CAnalyzeHtm()
{
}

CAnalyzeHtm::~CAnalyzeHtm()
{
}

//获取试卷答案
VOID CAnalyzeHtm::GetPaperAnswer(stuPaper & answer,const stuPaper & paper,CDHtmlDialog * dlg)
{
	answer.m_timeStamp = paper.m_timeStamp;
	answer.m_paperTitle = paper.m_paperTitle;
	GetInputElementText(answer.m_stuName,"edit_student_name",dlg);
	GetInputElementText(answer.m_stuID,"edit_student_id",dlg);
	for(size_t i = 0;i < paper.m_vecTopic.size();++i)
	{
		CString topicNum;
		topicNum.Format("%d",i + 1);
		answer.m_vecTopic.push_back(stuTopic());
		answer.m_vecTopic[i].m_type = paper.m_vecTopic[i].m_type;
		answer.m_vecTopic[i].m_score = 0;
		if(answer.m_vecTopic[i].m_type == eTopicTypeSelect)		//选择题
		{
			answer.m_vecTopic[i].m_selectNum = paper.m_vecTopic[i].m_selectNum;
			answer.m_vecTopic[i].m_checkA = GetCheckElementState(CString("check_qus_") + topicNum + "_A",dlg) ? BST_CHECKED : BST_UNCHECKED;
			answer.m_vecTopic[i].m_checkB = GetCheckElementState(CString("check_qus_") + topicNum + "_B",dlg) ? BST_CHECKED : BST_UNCHECKED;
			if(answer.m_vecTopic[i].m_selectNum > 2)
				answer.m_vecTopic[i].m_checkC = GetCheckElementState(CString("check_qus_") + topicNum + "_C",dlg) ? BST_CHECKED : BST_UNCHECKED;
			if(answer.m_vecTopic[i].m_selectNum > 3)
				answer.m_vecTopic[i].m_checkD = GetCheckElementState(CString("check_qus_") + topicNum + "_D",dlg) ? BST_CHECKED : BST_UNCHECKED;
			if(answer.m_vecTopic[i].m_selectNum > 4)
				answer.m_vecTopic[i].m_checkE = GetCheckElementState(CString("check_qus_") + topicNum + "_E",dlg) ? BST_CHECKED : BST_UNCHECKED;
		}
		else                 //其他题
			GetElementText(answer.m_vecTopic[i].m_ans,CString("edit_qus_") + topicNum + "_ans",dlg);
	}
}
//获取指定ID的 Input 控件的值，如输入框
BOOL CAnalyzeHtm::GetInputElementText(CString & str,const CString & id,CDHtmlDialog * dlg)
{
	CComPtr<IHTMLInputElement> input = NULL;
	if(dlg->GetElementInterface(id,&input) == S_OK && input)
	{
		CComBSTR temp;
		if(input->get_value(&temp) == S_OK)
		{
			str = temp;
			OutputDebugString(id + "   " + str);//注释
			return TRUE;
		}
	}
	str.Empty();
	return FALSE;
}
//获取指定ID的 checkbox 控件的 check 状态 返回 TRUE：checked FALSE:unchecked
BOOL CAnalyzeHtm::GetCheckElementState(const CString & id,CDHtmlDialog * dlg)
{
	CComPtr<IHTMLInputElement> input = NULL;
	if(dlg->GetElementInterface(id,&input) == S_OK && input)
	{
		VARIANT_BOOL value;
		if(input->get_checked(&value) == S_OK)
			//return value == VARIANT_TRUE;
		{
			if(value == VARIANT_TRUE)	//注释
			{
				OutputDebugString(id + "   checked");
				return TRUE;
			}
		}
	}
	return FALSE;
}
//获取指定ID的text，<p><h><textArea>标签等
BOOL CAnalyzeHtm::GetElementText(CString & str,const CString & id,CDHtmlDialog * dlg)
{
	CComPtr<IHTMLElement> sp = NULL;
	if(dlg->GetElementInterface(id,&sp) == S_OK)		//获取element
	{
		CComPtr<IHTMLDocument2> htmld = NULL;
		if(sp && dlg->GetDHtmlDocument(&htmld) == S_OK)	//获取document
		{
			CComBSTR temp;
			if(sp->get_innerText(&temp) == S_OK)
			{
				str = temp;								//BSTR转CString
				OutputDebugString(id + "   " + str);//注释
				return TRUE;
			}
		}
	}
	str.Empty();
	return FALSE;
}