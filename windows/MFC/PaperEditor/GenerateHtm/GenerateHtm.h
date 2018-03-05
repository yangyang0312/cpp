#pragma once
#include "../PaperEditor/PaperStruct.h"
#include <map>

class CGenerateHtm
{
public:
	CGenerateHtm();
	~CGenerateHtm();

public:
	//将paper试卷解析生成htm保存到filePath文件 type：教师端预览/学生端考试
	BOOL GeneratePaperToHtm(const stuPaper & paper,const CString & filePath, const ePaperViewType & type);
	//生成答卷信息，教师端阅卷给分
	BOOL GenerateAnswerToHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & filePath,const ePaperViewType & type);
	//生成答卷信息，学生端显示答案
	BOOL GenerateShowAnswerHtm(const stuPaper & paper,const stuPaper & answer,const stuClientInfo & info,const CString & filePath,const ePaperViewType & type);

private:
	//生成htm文件的几个段 type:教师端预览/学生端考试
	VOID GeneratePaperHead(const stuPaper & paper,const ePaperViewType & type);
	VOID GeneratePaperCss(const stuPaper & paper,const ePaperViewType & type);
	VOID GeneratePaperJs(const stuPaper & paper,const ePaperViewType & type);
	VOID GeneratePaperBody(const stuPaper & paper,const ePaperViewType & type);
	//把htm的几个段都写到文件
	BOOL  WriteHtmFile(const CString & filePath,const ePaperViewType & type = ePaperViewTypeView);
	//显示答案的body部分
	VOID GenerateShowAnswerHtmBody(const stuPaper & paper,const stuPaper & answer,const stuClientInfo & info,const ePaperViewType & type);
	//写答卷外边的htm
	BOOL WriteAnswerMainHtm(const CString & dir,const CString & path);
	//写答卷给分JS
	VOID WriteAnswerScoreJs(const ePaperViewType & type,BOOL onLoadRun = FALSE);
	//写答卷给分htm
	BOOL WriteAnswerScoreHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & path);
	//写答卷分数列表htm
	BOOL WriteAnswerScoreTableHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & path,const ePaperViewType & type);

private:
	CString m_head;			//头
	CString m_css;			//css段
	CString m_js;			//js段
	CString m_body;			//body段
};