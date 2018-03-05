#pragma once
#include "../PaperEditor/PaperStruct.h"
#include <vector>

#define MAX_READ_BUFFER 40960

class CLoadSavePaper
{
public:
	CLoadSavePaper();
	~CLoadSavePaper();

public:
	//保存paper到path文件，根据type确定保存试卷还是答案，试卷保存所有信息，答案只保存答案部分
	BOOL SavePaper(const stuPaper & paper, const ePaperType & type, const CString & path);
	//加载path文件到paper，根据type确定保存试卷还是答案，试卷加载所有信息，答案只加载答案部分
	BOOL LoadPaper(stuPaper & paper, const ePaperType & type, const CString & path);

private:
	//写入str和分隔符
	VOID WriteSection(CStdioFile & file,const CString & str);
	//读文件切分为子串，保存到vector中
	BOOL ReadPaperFile(const CString & path, std::vector<CString> & vec);

private:
	//分隔符
	TCHAR m_separator;
};

