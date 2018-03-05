#pragma once
#include <vector>

enum ePaperType				  //试卷保存类型
{
	ePaperTypePaper = 0,	  //试卷
	ePaperTypeAnswer		  //答案
};

enum eTopicType				  //题目类型
{
	eTopicTypeSelect = 0,	  //选择题
	eTopicTypeBlank,		  //填空题
	eTopicTypeQA,			  //问答题
	eTopicTypeNone			  //无
};

enum ePaperViewType			  //试卷生成类型
{
	ePaperViewTypeView = 0,	  //教师端预览
	ePaperViewTypePrint,	  //教师端打印
	ePaperViewTypeExam,		  //学生端考试
	ePaperViewTypeScore,	  //教师端给分
	ePaperViewTypeShowAns,    //学生端显示答案
	ePaperViewTypeExcel		  //教师端保存为excel
};

enum eScoreType				  //分数配置类型
{
	eScoreTypeAverage = 0,	  //平均
	eScoreTypeSingle,		  //单个题目设置
	eScoreTypeBatch			  //根据类型批量设置
};

struct stuTopic		  //问题结构
{
	stuTopic()
	{
		m_type = eTopicTypeSelect;
		m_selectNum = 4;	  //四选
		m_score = 100;
		m_checkA = m_checkB = m_checkC = m_checkD = m_checkE = BST_UNCHECKED;
		m_title = m_ans = m_ansA = m_ansB = m_ansC = m_ansD = m_ansE = CString();
	}
	eTopicType  m_type;       //问题类型
	double      m_score;      //分数
	int			m_selectNum;  //选择题选项数量
	int			m_checkA;	  //A选项 BST_CHECKED BST_UNCHECKED
	int			m_checkB;	  //
	int			m_checkC;	  //
	int			m_checkD;	  //
	int			m_checkE;	  //
	CString		m_title;	  //题目内容
	CString		m_ans;		  //答案
	CString		m_ansA;		  //选择题答案
	CString		m_ansB;		  //
	CString		m_ansC;		  //
	CString		m_ansD;		  //
	CString		m_ansE;		  //
	std::vector<CString> m_files;//文件	
	bool operator == (const stuTopic& other) const//重载比较运算符
	{
		return ((m_type == other.m_type) && (m_selectNum == other.m_selectNum) && (m_score == other.m_score) && (m_checkA == other.m_checkA) && (m_checkB == other.m_checkB) && (m_checkC == other.m_checkC) && (m_checkD == other.m_checkD) && (m_checkE == other.m_checkE) && (m_title == other.m_title) && (m_ans == other.m_ans) && (m_ansA == other.m_ansA) && (m_ansB == other.m_ansB) && (m_ansC == other.m_ansC) && (m_ansD == other.m_ansD) && (m_ansE == other.m_ansE) && (m_files == other.m_files));
	}
	//判断当前题目是不是单选题
	BOOL IsSingleChoice()
	{
		if (m_type == eTopicTypeSelect)
		{
			std::vector<int> vec;
			vec.push_back(m_checkA);		//加入选项
			vec.push_back(m_checkB);
			if (m_selectNum > 2)
				vec.push_back(m_checkC);
			if (m_selectNum > 3)
				vec.push_back(m_checkD);
			if (m_selectNum > 4)
				vec.push_back(m_checkE);
			int count = 0;
			for (size_t i = 0;i < vec.size();++i)
				if (vec[i] == BST_CHECKED)
					++count;
			if (count == 1)					//只选中一个
				return TRUE;
		}
		return FALSE;
	}
};

struct stuScoreSet                        //分数设置结构
{
	stuScoreSet()
	{
		m_type = eScoreTypeAverage;
		m_total = 100;
		m_batch[0] = m_batch[1] = m_batch[2] = m_batch[3] = 0;
	}
	eScoreType			m_type;			//配置类型
	double				m_total;		//平均分配的总分
	double				m_batch[4];		//单选、多选、填空、问答 总分
	std::vector<double> m_vecSigle;		//对每个题单独设置分数
};

struct stuPaper				//试卷结构
{
	stuPaper()
	{
		m_timeStamp = 0;
		m_stuName = m_stuID = m_paperTitle = CString();
	}
	int					  m_timeStamp;		  //时间戳，标示一场考试
	CString				  m_stuName;		  //学生姓名
	CString				  m_stuID;            //学生学号
	CString				  m_paperTitle;	      //试卷名
	std::vector<CString>  m_paperFiles;	      //试卷附加文件
	std::vector<stuTopic> m_vecTopic;		  //试卷题目
	stuScoreSet           m_scoreSet;		  //分数配置
	bool operator == (const stuPaper& other) const //重载比较运算符，用于比较两套试卷是否相同
	{
		return ((m_paperTitle == other.m_paperTitle) && (m_paperFiles == other.m_paperFiles) && (m_vecTopic == other.m_vecTopic));
	}
	double GetTotalScore()
	{
		double score = 0.0;
		for (size_t i = 0;i < m_vecTopic.size();++i)
			score += m_vecTopic[i].m_score;
		return score;
	}
};

struct stuClientInfo		//学生端信息
{
	stuClientInfo()
	{
		m_ip = m_mac = m_pcName = CString();
	}
	stuClientInfo(const CString & ip,const CString & mac,const CString & name)
	{
		m_ip = ip;
		m_mac = mac;
		m_pcName = name;
	}
	CString m_ip;			//ip
	CString m_mac;			//mac
	CString m_pcName;		//计算机名
};