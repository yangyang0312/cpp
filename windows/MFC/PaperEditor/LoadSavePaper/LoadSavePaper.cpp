#include "stdafx.h"
#include "LoadSavePaper.h"

CLoadSavePaper::CLoadSavePaper()
{
	m_separator = 0;
}

CLoadSavePaper::~CLoadSavePaper()
{
}
//写入str和分隔符
VOID CLoadSavePaper::WriteSection(CStdioFile & file, const CString & str)
{
	file.WriteString(str);
	file.Write(&m_separator,sizeof(TCHAR));
}
//保存paper到path文件，根据type确定保存试卷还是答案，试卷保存所有信息，答案只保存答案部分
BOOL CLoadSavePaper::SavePaper(const stuPaper & paper, const ePaperType & type, const CString & path)
{
	CStdioFile file;
	CString str;
	if (file.Open(path, CFile::modeCreate | CFile::modeWrite))
	{
		file.SetLength(0);
		file.SeekToBegin();
		str.Format("%08d", paper.m_timeStamp);	  //固定长度8位
		WriteSection(file,str);
		if (type == ePaperTypeAnswer)				//答案写入学生学号姓名
		{
			WriteSection(file,paper.m_stuName);
			WriteSection(file,paper.m_stuID);
		}
		WriteSection(file,paper.m_paperTitle);
		str.Format("%d",paper.m_paperFiles.size());				//附件数量
		WriteSection(file,str);
		for(size_t i = 0; i < paper.m_paperFiles.size(); ++i)		//试卷附加文件
			WriteSection(file,paper.m_paperFiles[i]);
		str.Format("%d",paper.m_scoreSet.m_type);					//分数配置 类型
		WriteSection(file,str);
		if (paper.m_scoreSet.m_type == eScoreTypeAverage)			//平均设置
		{
			str.Format("%.2lf", paper.m_scoreSet.m_total);
			WriteSection(file, str);
		}
		else if (paper.m_scoreSet.m_type == eScoreTypeBatch)		//批量设置
		{
			for (int i = 0;i < 4;++i)								//类型分数
			{
				str.Format("%.2lf", paper.m_scoreSet.m_batch[i]);
				WriteSection(file, str);
			}
		}
		else if (paper.m_scoreSet.m_type == eScoreTypeSingle)		//单个设置
		{
			str.Format("%d", paper.m_scoreSet.m_vecSigle.size());	//数量
			WriteSection(file, str);
			for (size_t i = 0;i < paper.m_scoreSet.m_vecSigle.size();++i)	//分数
			{
				str.Format("%.2lf", paper.m_scoreSet.m_vecSigle[i]);
				WriteSection(file, str);
			}
		}
		for (size_t i = 0; i < paper.m_vecTopic.size(); ++i)		//试卷题目
		{
			str.Format("%d", paper.m_vecTopic[i].m_type);			//类型
			WriteSection(file, str);
			WriteSection(file, paper.m_vecTopic[i].m_title);		//题目
			str.Format("%.2lf", paper.m_vecTopic[i].m_score);		//分数
			WriteSection(file, str);
			if (paper.m_vecTopic[i].m_type == eTopicTypeSelect)		//选择
			{
				str.Format("%d", paper.m_vecTopic[i].m_selectNum);	//选项数量
				WriteSection(file, str);
				str.Format("%d", paper.m_vecTopic[i].m_checkA);		//A选项
				WriteSection(file, str);
				WriteSection(file, paper.m_vecTopic[i].m_ansA);
				str.Format("%d", paper.m_vecTopic[i].m_checkB);
				WriteSection(file, str);
				WriteSection(file, paper.m_vecTopic[i].m_ansB);
				if (paper.m_vecTopic[i].m_selectNum > 2)
				{
					str.Format("%d", paper.m_vecTopic[i].m_checkC);
					WriteSection(file, str);
					WriteSection(file, paper.m_vecTopic[i].m_ansC);
				}
				if (paper.m_vecTopic[i].m_selectNum > 3)
				{
					str.Format("%d", paper.m_vecTopic[i].m_checkD);
					WriteSection(file, str);
					WriteSection(file, paper.m_vecTopic[i].m_ansD);
				}
				if (paper.m_vecTopic[i].m_selectNum > 4)
				{
					str.Format("%d", paper.m_vecTopic[i].m_checkE);
					WriteSection(file, str);
					WriteSection(file, paper.m_vecTopic[i].m_ansE);
				}
			}
			else                                                    //问答和填空的答案
				WriteSection(file, paper.m_vecTopic[i].m_ans);
			str.Format("%d", paper.m_vecTopic[i].m_files.size());				//题目附件数量
			WriteSection(file, str);
			for (size_t j = 0; j < paper.m_vecTopic[i].m_files.size(); ++j)		//题目附加文件
				WriteSection(file, paper.m_vecTopic[i].m_files[j]);
		}
		file.Close();
		return TRUE;
	}
	return FALSE;
}
//加载path文件到paper，根据type确定保存试卷还是答案，试卷加载所有信息，答案只加载答案部分
BOOL CLoadSavePaper::LoadPaper(stuPaper & paper, const ePaperType & type, const CString & path)
{
	std::vector<CString> vec;
	if (!ReadPaperFile(path, vec))								//读取、截取子串
		return FALSE;
	if (vec.size() > 0)
		paper.m_timeStamp = atoi(vec[0]);						//时间
	size_t pos = 1;												//vec位置
	if (type == ePaperTypeAnswer)								//答卷
	{
		if (vec.size() > 1)										//学号姓名
			paper.m_stuName = vec[1];
		if (vec.size() > 2)
			paper.m_stuID = vec[2];
		pos = 3;
	}
	if (vec.size() > pos)										//试卷名
		paper.m_paperTitle = vec[pos];
	++pos;
	int fileNum = 0;											//试卷附件数量
	if (vec.size() > pos)
		fileNum = atoi(vec[pos]);
	++pos;
	for (int i = 0;i < fileNum && pos + i < vec.size();++i, ++pos)//试卷附件
		paper.m_paperFiles.push_back(vec[pos]);
	if (vec.size() > pos)										//试卷分数配置
		paper.m_scoreSet.m_type = (eScoreType)atoi(vec[pos]);
	++pos;
	if (paper.m_scoreSet.m_type == eScoreTypeAverage)			//平均设置
	{
		if (vec.size() > pos)
			paper.m_scoreSet.m_total = atof(vec[pos]);
		++pos;
	}
	else if (paper.m_scoreSet.m_type == eScoreTypeBatch)		//批量设置
	{
		for (size_t i = 0;i < 4 && pos < vec.size();++pos, ++i)
			paper.m_scoreSet.m_batch[i] = atof(vec[pos]);
	}
	else if (paper.m_scoreSet.m_type == eScoreTypeSingle)		//单个设置
	{
		int num = 0;											//单个题目的数量
		if (vec.size() > pos)									
			num = atoi(vec[pos]);
		++pos;
		for (int i = 0;i < num && pos + i < vec.size();++i, ++pos)//每个题目对应的分数设置
			paper.m_scoreSet.m_vecSigle.push_back(atof(vec[pos]));
	}
	for (;pos < vec.size();++pos)
	{
		paper.m_vecTopic.push_back(stuTopic());
		paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_type = (eTopicType)atoi(vec[pos]);//类型
		++pos;
		if (pos < vec.size())
			paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_title = vec[pos];			  //题目
		++pos;
		if (pos < vec.size())
			paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_score =atof(vec[pos]);		  //分数
		++pos;
		if (paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_type == eTopicTypeSelect)	  //选择
		{
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_selectNum = atoi(vec[pos]);	//选项
			++pos;
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkA = atoi(vec[pos]);
			++pos;
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansA = vec[pos];
			++pos;
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkB = atoi(vec[pos]);
			++pos;
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansB = vec[pos];
			if (paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_selectNum > 2)			//选项大于2
			{
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkC = atoi(vec[pos]);
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansC = vec[pos];
			}
			if (paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_selectNum > 3)			//选项大于3
			{
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkD = atoi(vec[pos]);
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansD = vec[pos];
			}
			if (paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_selectNum > 4)			////选项大于4
			{
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkE = atoi(vec[pos]);
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansE = vec[pos];
			}
		}
		else                              //填空、问答 答案
		{
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ans = vec[pos];
		}
		++pos;
		if (pos < vec.size())		       //题目附件数量
			fileNum = atoi(vec[pos]);
		++pos;
		for (int j = 0;j < fileNum && pos + j < vec.size();++j, ++pos)	//题目附件
			paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_files.push_back(vec[pos]);
		--pos;
	}
	return TRUE;
}
//读文件切分为子串，保存到vector中
BOOL CLoadSavePaper::ReadPaperFile(const CString & path, std::vector<CString> & vec)
{
	CFileFind finder;
	if (!finder.FindFile(path))										//确定文件存在
		return FALSE;
	finder.Close();
	CFile file;
	if (file.Open(path, CFile::modeRead))
	{
		file.SeekToBegin();
		char buf[MAX_READ_BUFFER] = { 0 };		//40kb
		CString str;
		UINT readLen = 0;
		while ((readLen = file.Read(buf, MAX_READ_BUFFER)) > 0)    //逐个读取，解析buffer里的子串，并保存
		{
			UINT posStart = 0;
			for (UINT i = 0;i < readLen;++i)
			{
				if (m_separator == buf[i])								//遍历寻找标记
				{
					str.Format("%s", buf + posStart);				//格式化，放入子串
					vec.push_back(str);
					posStart = i + 1;									//更新起始位置记录
				}
			}
			file.Seek(file.GetPosition() - readLen + posStart, 0);	//重新从上一个标记后读取
			ZeroMemory(buf, MAX_READ_BUFFER);						//清空缓冲
		}
		file.Close();
		return TRUE;
	}
	return FALSE;
}