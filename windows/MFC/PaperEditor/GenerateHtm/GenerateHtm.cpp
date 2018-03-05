#include "stdafx.h"
#include "GenerateHtm.h"

CGenerateHtm::CGenerateHtm()
{
}

CGenerateHtm::~CGenerateHtm()
{
}

//将paper试卷解析生成htm保存到filePath文件
BOOL CGenerateHtm::GeneratePaperToHtm(const stuPaper & paper,const CString & filePath,const ePaperViewType & type)
{
	GeneratePaperHead(paper,type);
	GeneratePaperCss(paper,type);
	GeneratePaperJs(paper,type);
	GeneratePaperBody(paper,type);
	return WriteHtmFile(filePath);
}
//生成htm文件的几个段
VOID CGenerateHtm::GeneratePaperHead(const stuPaper & paper,const ePaperViewType & type)
{
	m_head = "<html>\r\n<head>\r\n<meta http-equiv=\"content-type\" content=\"text/html; charset=gbk\"/>\r\n<title></title>";
}
VOID CGenerateHtm::GeneratePaperCss(const stuPaper & paper,const ePaperViewType & type)
{
	m_css = "<style type=\"text/css\">\r\n";
	m_css += "body\r\n{\r\n\toverflow:auto\r\n}\r\n";	//自动滚动条
	m_css += ".papertitle\r\n{\r\nfont-size:30px;\r\ncolor:#111;\r\nmargin-top:50px;\r\nmargin-bottom:30px;\r\n}\r\n";
	m_css += "#countdown\r\n{\r\nfont-size:28px;\r\ncolor:#555;\r\n}\r\n";
	m_css += ".bodytext\r\n{\r\nfont-family:微软雅黑;\r\n}\r\n";
	if (type == ePaperViewTypeExam)
	{
		m_css += "#grayline\r\n{\r\nwidth:100%;\r\nheight:2px;\r\ncolor:#ccc;\r\nborder-bottom:1px solid gray;\r\nmargin-top:20px;\r\n}\r\n";
		m_css += ".name\r\n{\r\ndisplay:inline-block;\r\nfont-weight:lighter;\r\nfont-size:15px;\r\nmargin-left:10%;\r\nmargin-right:2%;\r\nmargin-top:2%;\r\n}\r\n";
		m_css += ".number\r\n{\r\ndisplay:inline-block;\r\nfont-weight:lighter;\r\nfont-size:15px;\r\nmargin-right:30%;\r\nmargin-top:2%;\r\n}\r\n";
		m_css += ".image\r\n{\r\nposition:fixed;\r\nwidth:30px;\r\nheight:30px;\r\nmargin-top:1.4%;\r\n}\r\n";
		m_css += ".countdown\r\n{\r\nposition:fixed;\r\nfont-weight:lighter;\r\nfont-size:15px;\r\nmargin-top:2%;\r\nmargin-left:2.4%\r\n}\r\n";
		m_css += "#graylinedown\r\n{\r\nwidth:80%;\r\nheight:1px;\r\ncolor:#ebebeb;\r\nborder-bottom:1px solid lightgray;\r\nmargin-bottom:4%;\r\nmargin-top:10px;\r\n}\r\n";
	}
	m_css += ".topic\r\n{\r\nwidth:80%;\r\nfont-size:15px;\r\ncolor:#333;\r\nmargin-bottom:10px;\r\nmargin-left:10%;\r\n}\r\n";
	m_css += ".options\r\n{\r\nmargin-bottom:10px;\r\nmargin-left:10px;\r\n}\r\n";
	m_css += ".checkboxs\r\n{\r\nheight:15px;\r\nwidth:15px;\r\ncolor:#999;\r\n}\r\n";
	m_css = m_css + ".textblank\r\n{\r\nwidth:" + (type == ePaperViewTypeShowAns || type == ePaperViewTypeScore ? "100%" : "80%" ) + ";\r\nheight:40px;\r\nmargin-left:" + (type == ePaperViewTypeShowAns || type == ePaperViewTypeScore ? "1%" : "10%") + ";\r\n}\r\n";
	m_css += ".mentionmsg\r\n{\r\ncolor:#e80000;\r\nfont-size:12px;\r\nmargin-left:14px;\r\n}\r\n";
	m_css = m_css + ".textquestion\r\n{\r\n\r\nwidth:" + (type == ePaperViewTypeShowAns || type == ePaperViewTypeScore ? "100%" : "80%") + ";\r\nheight:120px;\r\nmargin-bottom:40px;\r\nmargin-left:" + (type == ePaperViewTypeShowAns || type == ePaperViewTypeScore ? "1%" : "10%") + ";\r\n}\r\n";
	m_css += ".btnsubmit\r\n{\r\nwidth:120px;\r\nheight:30px;\r\nfont-family:微软雅黑;\r\nfont-size:15px;\r\ncolor:white;\r\nbackground-color:#007bda;\r\n}\r\n";
	m_css += ".btnclose\r\n{\r\nwidth:120px;\r\nheight:30px;\r\nfont-family:微软雅黑;\r\nfont-size:15px;\r\ncolor:white;\r\nbackground-color:#007bda;\r\nmargin-left:80%;\r\n}\r\n";
}
VOID CGenerateHtm::GeneratePaperJs(const stuPaper & paper,const ePaperViewType & type)
{
	m_js = "<script type=\"text/javascript\">\r\n";
	if (type == ePaperViewTypeExam)
	{
		int nExamTimeSecond = 90;
		CString strExamTime = _T("");
		strExamTime.Format("%d",nExamTimeSecond);
		m_js += "var countdownf=function()\r\n{\r\nvar sec=90;";
		//m_js += strExamTime;
		m_js += "\r\nvar i=parseInt(sec/60);\r\nvar j=sec%60;\r\ncountdownmin.innerHTML=i;\r\ncountdownsec.innerHTML=j;\r\n";
		m_js += "var timer = setInterval(\r\nfunction()\r\n{\r\ncountdownmin.innerHTML = i;\r\ncountdownsec.innerHTML = j;\r\n";
		m_js += "if(j == 0 && i == 0)\r\n{\r\nclearInterval(timer);\r\n}\r\nelse\r\n{\r\nif(j == 0)\r\n{\r\n--i;\r\nj=60;\r\n}\r\n--j;\r\n}\r\n}\r\n,1000);\r\n}\r\n";
		m_js += "window.onload=countdownf;\r\n";
	}
}
VOID CGenerateHtm::GeneratePaperBody(const stuPaper & paper,const ePaperViewType & type)
{
	m_body = "<body class=bodytext>\r\n";
	m_body += "<center><h1 class=papertitle id=id_title>" + paper.m_paperTitle + "<h1>\r\n</center>\r\n";
	if (type == ePaperViewTypeView)		//关闭页面 按钮
	{
		m_body = m_body + "<button class=btnclose id=btn_close> 关闭 </button>\r\n";
	}
	else if (type == ePaperViewTypePrint)//打印按钮，隐藏
	{
		m_body = m_body + "<button id=btn_print onclick=\"window.print();window.external.close_window();\" style=\"visibility:hidden;\" value=\"print\">打印</button>\r\n";
	}
	if (type == ePaperViewTypeExam)		//姓名学号
	{
		m_body += "<center>\r\n<div id=grayline></div>\r\n</center>\r\n";
		m_body += "<a class=name>姓名:<input type=text id=edit_student_name size=15% maxlength=16></input></a>\r\n";
		m_body += "<a class=number>学号:<input type=text id=edit_student_id size=15% maxlength=16></input></a>\r\n";
	}
	m_body += "<link type=\"text/css\" rel=\"stylesheet\" href=\"res:/PNG/#101\" />\r\n";
	if (type == ePaperViewTypeExam)
	{
		m_body += "<img class=image src= res:/PNG/#101>\r\n";
		m_body += "<a class=countdown><span id=countdownmin></span><span>:</span><span id=countdownsec></span></a>\r\n";
		m_body += "<center>\r\n<div id=graylinedown></div>\r\n</center>\r\n";
	}
	for(size_t i = 0;i < paper.m_vecTopic.size();++i)
	{
		CString topicScore;
		topicScore.Format("(%.2f分)",paper.m_vecTopic[i].m_score);
		CString topicNum;
		topicNum.Format("%d",i + 1);
		m_body += "<div class=topic>\r\n";
		m_body += CString("<p>") + topicNum + ". " + paper.m_vecTopic[i].m_title + topicScore + "</p>\r\n";
		m_body += "</div>\r\n";
		if (paper.m_vecTopic[i].m_type == eTopicTypeSelect)
		{
			m_body += "<div class=topic>\r\n";
			m_body += "<div>\r\n";
			m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + "_A " + (type == ePaperViewTypeView && paper.m_vecTopic[i].m_checkA == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>A." + paper.m_vecTopic[i].m_ansA + "</a>\r\n</div>\r\n";
			m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + +"_B " + (type == ePaperViewTypeView && paper.m_vecTopic[i].m_checkB == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>B." + paper.m_vecTopic[i].m_ansB + "</a>\r\n</div>\r\n";
			if (paper.m_vecTopic[i].m_selectNum > 2)
				m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + +"_C " + (type == ePaperViewTypeView && paper.m_vecTopic[i].m_checkC == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>C." + paper.m_vecTopic[i].m_ansC + "</a>\r\n</div>\r\n";
			if (paper.m_vecTopic[i].m_selectNum > 3)
				m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + +"_D " + (type == ePaperViewTypeView && paper.m_vecTopic[i].m_checkD == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>D." + paper.m_vecTopic[i].m_ansD + "</a>\r\n</div>\r\n";
			if (paper.m_vecTopic[i].m_selectNum > 4)
				m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + +"_E " + (type == ePaperViewTypeView && paper.m_vecTopic[i].m_checkE == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>E." + paper.m_vecTopic[i].m_ansE + "</a>\r\n</div>\r\n";
			m_body += "</div>\r\n";
			m_body += "</div>\r\n";
		}
		else if(paper.m_vecTopic[i].m_type == eTopicTypeBlank)
		{
			m_body += CString("<textarea id=edit_qus_") + topicNum + "_ans class=textblank maxlength=4096>" + (type == ePaperViewTypeView ? paper.m_vecTopic[i].m_ans : "") + "</textarea>\r\n";	//编辑框
			m_body += "<div class=topic>\r\n";
			m_body += CString("<p class=mentionmsg>(注意：如果有多个答案需要填写，答案用@分隔开，如：Answer1@Answer2)</p>\r\n");
			m_body += "</div>\r\n";
		}
		else
		{
			m_body += CString("<textarea id=edit_qus_") + topicNum + "_ans class=textquestion maxlength=4096>" + (type == ePaperViewTypeView ? paper.m_vecTopic[i].m_ans : "") + "</textarea>\r\n";	//编辑框
		}
		m_body += "<br>\r\n";
	}
	if(type == ePaperViewTypeExam)
		m_body += "<center>\r\n<div>\r\n<button class=btnsubmit id=btn_submit>提交答卷</button>\r\n</div>\r\n</center>\r\n</div>\r\n";
}
//把htm的几个段都写到文件
BOOL CGenerateHtm::WriteHtmFile(const CString & filePath,const ePaperViewType & type)
{
	CFile file;
	if(file.Open(filePath,CFile::modeCreate | CFile::modeReadWrite))
	{
		CString s;
		file.SeekToBegin();
		file.Write(m_head,m_head.GetLength());
		s = "\r\n";
		file.Write(s,s.GetLength());
		file.Write(m_css,m_css.GetLength());
		s = "</style>\r\n";
		file.Write(s,s.GetLength());
		file.Write(m_js,m_js.GetLength());
		s = "</script>\r\n";
		file.Write(s,s.GetLength());
		s = "</head>\r\n";
		file.Write(s,s.GetLength());
		file.Write(m_body,m_body.GetLength());
		s = "";
		if(type != ePaperViewTypeScore)			//frame不能有body
			s = "</body>";
		s += "\r\n</html>";
		file.Write(s,s.GetLength());
		file.Close();
	}
	else
		return FALSE;//Open failed
	return TRUE;
}
//显示答案的body部分
VOID CGenerateHtm::GenerateShowAnswerHtmBody(const stuPaper & paper,const stuPaper & answer,const stuClientInfo & info,const ePaperViewType & type)
{
	m_body = "<body class=bodytext>\r\n";
	m_body += "<center><h1 class=papertitle id=id_title>" + paper.m_paperTitle + "<h1>\r\n</center>\r\n";
	if(type == ePaperViewTypeShowAns)
		m_body = m_body + "<button class=btnclose id=btn_close>关闭</button>\r\n";
	else if(type == ePaperViewTypeScore)
	{
		m_body += "<center>\r\n<table width=\"45%\">\r\n";
		m_body += "<tr>\r\n<td width=\"35%\">学号:</td>\r\n<td>" + (answer.m_stuID.IsEmpty() ? CString("未填写") : answer.m_stuID) + "</td>\r\n</tr>\r\n";
		m_body += "<tr>\r\n<td width=\"35%\">姓名:</td>\r\n<td>" + (answer.m_stuName.IsEmpty() ? CString("未填写") : answer.m_stuName) + "</td>\r\n</tr>\r\n";
		m_body += "<tr>\r\n<td width=\"35%\">IP地址:</td>\r\n<td>" + info.m_ip + "</td>\r\n</tr>\r\n";
		m_body += "<tr>\r\n<td width=\"35%\">计算机名:</td>\r\n<td>" + info.m_pcName + "</td>\r\n</tr>\r\n";
		m_body += "<tr>\r\n<td width=\"35%\">MAC地址:</td>\r\n<td>" + info.m_mac + "</td>\r\n</tr>\r\n";
		m_body += "</table>\r\n</center><br>\r\n";
	}
	if(paper.m_vecTopic.size() != answer.m_vecTopic.size())
		return;
	for(size_t i = 0;i < paper.m_vecTopic.size();++i)
	{
		CString topicScore;
		topicScore.Format("(%.2lf分)",paper.m_vecTopic[i].m_score,answer.m_vecTopic[i].m_score);
		CString topicNum;
		topicNum.Format("%d",i + 1);
		m_body += "<div class=topic id=qus_" + topicNum + ">\r\n";
		m_body += CString("<p>") + topicNum + ". " + paper.m_vecTopic[i].m_title + topicScore + "</p>\r\n";
		m_body += "</div>\r\n";
		if(paper.m_vecTopic[i].m_type == eTopicTypeSelect)
		{
			m_body += "<div class=topic>\r\n";
			m_body += "<div>\r\n";
			m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + "_A " + (paper.m_vecTopic[i].m_checkA == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>A." + paper.m_vecTopic[i].m_ansA + "</a>\r\n</div>\r\n";
			m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + "_B " + (paper.m_vecTopic[i].m_checkB == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>B." + paper.m_vecTopic[i].m_ansB + "</a>\r\n</div>\r\n";
			if(paper.m_vecTopic[i].m_selectNum > 2)
				m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + +"_C " + (paper.m_vecTopic[i].m_checkC == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>C." + paper.m_vecTopic[i].m_ansC + "</a>\r\n</div>\r\n";
			if(paper.m_vecTopic[i].m_selectNum > 3)																																					
				m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + +"_D " + (paper.m_vecTopic[i].m_checkD == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>D." + paper.m_vecTopic[i].m_ansD + "</a>\r\n</div>\r\n";
			if(paper.m_vecTopic[i].m_selectNum > 4)																																					 
				m_body += CString("<div class=options>\r\n<input type=checkbox class=checkboxs id=check_qus_") + topicNum + +"_E " + (paper.m_vecTopic[i].m_checkE == BST_CHECKED ? " CHECKED " : " ") + ">\r\n<a>E." + paper.m_vecTopic[i].m_ansE + "</a>\r\n</div>\r\n";
			m_body += "<br>\r\n<font color=\"red\">你的答案是：";
			if(answer.m_vecTopic[i].m_checkA == BST_CHECKED)
				m_body += "A ";
			if(answer.m_vecTopic[i].m_checkB == BST_CHECKED)
				m_body += "B ";
			if(answer.m_vecTopic[i].m_selectNum > 2 && answer.m_vecTopic[i].m_checkC == BST_CHECKED)
				m_body += "C ";
			if(answer.m_vecTopic[i].m_selectNum > 3 && answer.m_vecTopic[i].m_checkD == BST_CHECKED)
				m_body += "D ";
			if(answer.m_vecTopic[i].m_selectNum > 4 && answer.m_vecTopic[i].m_checkE == BST_CHECKED)
				m_body += "E ";
			m_body += "</font>\r\n";
			m_body += "<br>\r\n<font color=\"blue\">正确答案是：";
			if(paper.m_vecTopic[i].m_checkA == BST_CHECKED)
				m_body += "A ";
			if(paper.m_vecTopic[i].m_checkB == BST_CHECKED)
				m_body += "B ";
			if(paper.m_vecTopic[i].m_selectNum > 2 && paper.m_vecTopic[i].m_checkC == BST_CHECKED)
				m_body += "C ";
			if(paper.m_vecTopic[i].m_selectNum > 3 && paper.m_vecTopic[i].m_checkD == BST_CHECKED)
				m_body += "D ";
			if(paper.m_vecTopic[i].m_selectNum > 4 && paper.m_vecTopic[i].m_checkE == BST_CHECKED)
				m_body += "E ";
			m_body += "</font>\r\n</div>\r\n</div>\r\n";
		}
		else if(paper.m_vecTopic[i].m_type == eTopicTypeBlank)
		{
			m_body += "<div class=topic>\r\n<table width=\"100%\">\r\n";
			m_body += CString("<font color=\"blue\">") + (type == ePaperViewTypeScore ? "学生" : "你的") + "答案是：</font>\r\n<br>\r\n";
			m_body += CString("<textarea class=textblank maxlength=4096>") + answer.m_vecTopic[i].m_ans + "</textarea>\r\n<br>";	//编辑框
			m_body += "<font color=\"blue\">正确答案是：</font>\r\n<br>\r\n";
			m_body += CString("<textarea id=edit_qus_") + topicNum + "_ans class=textblank maxlength=4096>" + paper.m_vecTopic[i].m_ans + "</textarea>\r\n";	//编辑框
			m_body += "</table>\r\n</div>\r\n";
		}
		else
		{
			m_body += "<div class=topic>\r\n<table width=\"100%\">\r\n";
			m_body += "<font color=\"blue\">你的答案是：</font>\r\n<br>\r\n";
			m_body += CString("<textarea class=textquestion maxlength=4096>") + answer.m_vecTopic[i].m_ans + "</textarea>\r\n<br>";	//编辑框
			m_body += "<font color=\"blue\">正确答案是：</font>\r\n<br>\r\n";
			m_body += CString("<textarea id=edit_qus_") + topicNum + "_ans class=textquestion maxlength=4096>" + paper.m_vecTopic[i].m_ans + "</textarea>\r\n";	//编辑框
			m_body += "</table>\r\n</div>\r\n";
		}
		//if(type == ePaperViewTypeScore)			//得分
		//{
		//	CString s;
		//	s.Format("得分: %.2lf",answer.m_vecTopic[i].m_score);
		//	m_body += "<div class=topic id=qus_" + topicNum + "_score>\r\n";
		//	m_body += CString("<p>") + s + "</p>\r\n";
		//	m_body += "</div>\r\n";
		//}
		m_body += "<br>\r\n";
	}
}
//生成答卷信息，学生端显示答案
BOOL CGenerateHtm::GenerateShowAnswerHtm(const stuPaper & paper,const stuPaper & answer,const stuClientInfo & info,const CString & filePath,const ePaperViewType & type)
{
	GeneratePaperHead(paper,type);
	GeneratePaperCss(paper,type);
	GeneratePaperJs(paper,type);
	GenerateShowAnswerHtmBody(paper,answer,info,type);
	return WriteHtmFile(filePath);
}
//写答卷外边的htm
BOOL CGenerateHtm::WriteAnswerMainHtm(const CString & dir,const CString & path)
{
	m_head = "<html>\r\n<head>\r\n<meta http-equiv=\"content-type\" content=\"text/html; charset=gbk\"/>\r\n<title></title>";
	m_css = "<style type=\"text/css\">\r\n";
	m_js = "<script type=\"text/javascript\">\r\n";
	m_body = "<frameset cols=\"20%,80%\">\r\n";
	m_body += "<frame src=\"" + dir + "score.htm\" name=score target=answer>\r\n";		//给分
	m_body += "<frameset rows=\"25%,75%\">\r\n";
	m_body += "<frame src=\"" + dir + "answer_table.htm\" name=answer_table>\r\n";		//得分表
	m_body += "<frame src=\"" + dir + "answer_1.htm\" name=answer>\r\n";				//答卷
	m_body += "</frameset>\r\n</frameset>\r\n";
	return WriteHtmFile(path,ePaperViewTypeScore);
}
//写答卷给分htm
BOOL CGenerateHtm::WriteAnswerScoreHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & path)
{
	m_head = "<html>\r\n<head>\r\n<meta http-equiv=\"content-type\" content=\"text/html; charset=gbk\"/>\r\n<title></title>";
	m_css = "<style type=\"text/css\">\r\n";
	m_css += "body\r\n{\r\n\toverflow:auto\r\n}\r\n";	//自动滚动条
	WriteAnswerScoreJs(ePaperViewTypeScore);
	m_body = "<body>\r\n<br><br><br>\r\n";
	int htmCount = 0;
	for(std::map<CString,stuClientInfo>::const_iterator it = info.begin();it != info.end();++it)
	{
		std::map<CString,stuPaper>::const_iterator it_ans = answer.find(it->first);
		if(it_ans != answer.end() && paper.m_vecTopic.size() == it_ans->second.m_vecTopic.size())			//找到
		{
			++htmCount;
			CString strHtmCount;
			strHtmCount.Format("%d",htmCount);
			m_body += "<center>\r\n<table id=score_stu>\r\n<tr>\r\n<table id=score_stu_" + strHtmCount + " width=\"80%\" cellspacing=0 cellpadding=0>\r\n";
			m_body += "<tr>\r\n<td width=\"40%\">\r\n<a href=\"answer_" + strHtmCount + ".htm\" target=\"answer\"><b>学生" + strHtmCount + ":</b></a>\r\n</td>\r\n";		//学生
			m_body += "\r\n<td width=\"60%\">" + ((it_ans->second.m_stuName.IsEmpty() || it_ans->second.m_stuID.IsEmpty()) ? it->second.m_ip + "_" + it->second.m_pcName : it_ans->second.m_stuID + "_" + it_ans->second.m_stuName) + "\r\n</td>\r\n</tr>\r\n";
			for(size_t i = 0;i < paper.m_vecTopic.size();++i)
			{
				if(paper.m_vecTopic[i].m_type != eTopicTypeSelect)			//非选择题
				{
					CString topicNum;
					topicNum.Format("%d",i + 1);
					m_body += "<tr>\r\n<td width=\"40%\">\r\n<a href=\"answer_" + strHtmCount + ".htm#qus_" + topicNum + "\" target=\"answer\">问题" + topicNum + ":</a>\r\n</td>\r\n";
					m_body += "\r\n<td width=\"60%\">\r\n<input type=text width=\"100%\" size=10 value=\"0\" id=answer_" + strHtmCount + "_qus_" + topicNum + ">\r\n</td>\r\n</tr>\r\n";
				}
			}
			m_body += "</table>\r\n</tr>\r\n</table>\r\n</center>\r\n<br>\r\n";
		}
	}
	m_body += "<br>\r\n<center>\r\n<table width=\"60%\" cellspacing=0 cellpadding=0>\r\n<input type=button style=\"width:60%;height:30px;\" value=\"给分\" onClick=\"GiveScore(1)\">\r\n";
	m_body += "<br><br>\r\n<input type=button style=\"width:60%;height:30px;\" value=\"清除给分\" onClick=\"GiveScore(0)\">\r\n";
	m_body += "<br><br>\r\n<input type=button id=btn_excel style=\"width:60%;height:30px;\" onclick=\"parent.frames[1].document.all.save_excel.onclick();\" value=\"导出为excel\">\r\n";
	m_body += "<br><br>\r\n<input type=button style=\"width:60%;height:30px;\" onclick=\"QuitScore();\" value=\"退出\">\r\n";
	m_body += "</table>\r\n</center>\r\n";
	return WriteHtmFile(path);
}
//写答卷给分JS
VOID CGenerateHtm::WriteAnswerScoreJs(const ePaperViewType & type,BOOL onLoadRun)
{
	m_js = "<script type=\"text/javascript\">\r\n";
	if(type == ePaperViewTypeScore)
	{
		m_js += "var isChanged=0;\r\nfunction GiveScore(isgive)\r\n{\r\n\tisChanged=1;\r\n\tvar answer_table=parent.frames[1].document.all.score_table;\r\n\t";
		m_js += "var stuCount=document.getElementById(\"score_stu\").rows.length;\r\n\tfor(var i=1;i<=stuCount;++i)\r\n\t{\r\n\t\tvar stu=document.getElementById(\"score_stu_\"+i);\r\n\t\tfor(var j=1;j<stu.rows.length;++j)\r\n\t\t{\r\n\t\t\tvar str=stu.rows[j].cells[0].innerText;\r\n\t\t\t";
		m_js += "str=str.substr(2,str.length-4);\r\n\t\t\tif(isgive==0)\r\n\t\t\t{\r\n\t\t\t\tanswer_table.rows[i].cells[str].innerText=\"0.00\";\r\n\t\t\t\tdocument.getElementById(\"answer_\"+i+\"_qus_\"+str).value=0;\r\n\t\t\t\tcontinue;\r\n\t\t\t}\r\n\t\t\t";
		m_js += "answer_table.rows[i].cells[parseInt(str)].innerText=document.getElementById(\"answer_\"+i+\"_qus_\"+str).value;\r\n\t\t}\r\n\t}\r\n}\r\n";
		m_js += "function QuitScore()\r\n{\r\n\tif(isChanged==1&&confirm(\"学生分数已修改，是否保存?\"))\r\n\t{\r\n\t\tvar answer_table=parent.frames[1].document.all.score_table;\r\n\t\tfor(var i=1;i<answer_table.rows.length;++i)\r\n\t\t\tfor (var j = 1;j < answer_table.rows[i].cells.length;++j)\r\n\t\t\t\twindow.external.set_answer_score(i,j,answer_table.rows[i].cells[j].innerText);\r\n\t}\r\n\twindow.external.close_window();\r\n}\r\n";
	}
	else if(type == ePaperViewTypeExcel)
	{
		m_js += CString(onLoadRun ? "window.onload=" : "") + "function SaveAsExcel()\r\n{\r\n\tvar objTab=document.getElementById(\"score_table\");\r\n\ttry\r\n\t{\r\n\t\tvar xls = new ActiveXObject(\"Excel.Application\");\r\n\t}\r\n\tcatch(e)\r\n\t{\r\n\t\talert(\"要保存为excel，您必须安装Excel电子表格软件，同时浏览器须使用“ActiveX控件”\");\r\n\t\t" + CString(onLoadRun ? "window.external.close_window();\r\n\t\t" : "") +"return;\r\n\t}\r\n\t";
		m_js += "xls.visible=false;\r\n\tvar xlBook=xls.Workbooks.Add;\r\n\tvar xlsheet=xlBook.Worksheets(1);\r\n\tvar x=1;\r\n\tvar y=1;\r\n\tfor(var i=0; i<objTab.rows.length; i++)\r\n\t{\r\n\t\ty=1;\r\n\t\tfor(var j=0; j<objTab.rows[i].cells.length; j++)\r\n\t\t";
		m_js += "{\r\n\t\t\txlsheet.Cells(x,y).Value=objTab.rows[i].cells[j].innerText;\r\n\t\t\txlsheet.Cells(x,y).Borders.LineStyle=1;\r\n\t\t\ty++;\r\n\t\t}\r\n\t\tx++;\r\n\t}\r\n\txlsheet.Columns.AutoFit; //自动适应大小\r\n\t";
		m_js += "try\r\n\t{\r\n\t\tvar fileSave = new ActiveXObject(\"MSComDlg.CommonDialog\");\r\n\t\tfileSave.Filter=\".xls\";\r\n\t\tfileSave.FilterIndex=2;\r\n\t\tfileSave.MaxFileSize=128;\r\n\t\tfileSave.ShowSave();\r\n\t\tvar savepath=fileSave.FileName+'.xls';\r\n\t\txlsheet.SaveAs(savepath);\r\n\t\twindow.status=\"Saving as excel to \"+savepath+\" Success!!!\";\r\n\t";
		m_js += "}\r\n\tcatch(e)\r\n\t{\r\n\t\twindow.status=\"call save file dialog failed.\";\r\n\t}\r\n\txlsheet.Application.Quit();\r\n\t" + CString(onLoadRun ? "window.external.close_window();\r\n\t" : "") +"return;\r\n}\r\n";
	}
}
//写答卷分数列表htm
BOOL CGenerateHtm::WriteAnswerScoreTableHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & path,const ePaperViewType & type)
{
	m_head = "<html>\r\n<head>\r\n<meta http-equiv=\"content-type\" content=\"text/html; charset=gbk\"/>\r\n<title></title>";
	m_css = "<style type=\"text/css\">\r\n";
	m_css += "body\r\n{\r\n\toverflow:auto\r\n}\r\n";	//自动滚动条
	WriteAnswerScoreJs(ePaperViewTypeExcel,type == ePaperViewTypeExcel ? TRUE : FALSE);
	m_body = "<body>\r\n<br>\r\n<center>\r\n<table id=score_table border=\"1px\">\r\n<tr>\r\n<td>学生\\题目</td>\r\n";
	for(size_t i = 0;i < paper.m_vecTopic.size();++i)
	{
		CString s;
		s.Format("第%d题",i + 1);
		m_body = m_body + "<td>" + s + "</td>\r\n";			//表头
	}
	m_body += "</tr>\r\n";
	int htmCount = 0;
	for(std::map<CString,stuClientInfo>::const_iterator it = info.begin();it != info.end();++it)
	{
		std::map<CString,stuPaper>::const_iterator it_ans = answer.find(it->first);
		if(it_ans != answer.end() && paper.m_vecTopic.size() == it_ans->second.m_vecTopic.size())			//找到
		{
			++htmCount;
			CString strHtmCount;
			strHtmCount.Format("%d",htmCount);
			m_body += "<tr>\r\n<td><a href=\"answer_" + strHtmCount + ".htm\" target=\"answer\"><b>学生" + strHtmCount + ":</b></a></td>\r\n";	//学生
			for(size_t i = 0;i < paper.m_vecTopic.size();++i)
			{
				CString score;
				score.Format("%.2lf",it_ans->second.m_vecTopic[i].m_score);			//分数
				OutputDebugString(score + " write score");
				m_body += "<td>" + score + "</td>\r\n";
			}
			m_body += "</tr>\r\n";
		}
	}
	m_body += "</table>\r\n</center><input type=button style=\"visibility:hidden;\" id=save_excel onclick=\"SaveAsExcel();\"\r\n";
	return WriteHtmFile(path);
}
//生成答卷信息，教师端阅卷给分
BOOL CGenerateHtm::GenerateAnswerToHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & filePath,const ePaperViewType & type)
{
	CString frameDir = filePath.Right(filePath.GetLength() - filePath.ReverseFind('\\') - 1);
	frameDir = frameDir.Left(frameDir.GetLength() - 3) + "files\\";					//相对路径
	CString framePath = filePath.Left(filePath.GetLength() - 3) + "files\\";		//绝对路径
	if(!WriteAnswerMainHtm(frameDir,filePath))			//frame
		return FALSE;
	CFileFind finder;
	if(!finder.FindFile(framePath))					//目录创建
		CreateDirectory(framePath,NULL);
	if(!WriteAnswerScoreHtm(paper,answer,info,framePath + "score.htm"))
		return FALSE;
	if(!WriteAnswerScoreTableHtm(paper,answer,info,framePath + "answer_table.htm",type))
		return FALSE;
	int htmCount = 0;
	for(std::map<CString,stuClientInfo>::const_iterator it = info.begin();it != info.end();++it)
	{
		OutputDebugString(it->first + " info");
		std::map<CString,stuPaper>::const_iterator it_ans = answer.find(it->first);
		if(it_ans != answer.end() && paper.m_vecTopic.size() == it_ans->second.m_vecTopic.size())			//找到
		{
			OutputDebugString(it_ans->first + " answer");
			++htmCount;
			CString strHtmCount;
			strHtmCount.Format("answer_%d.htm",htmCount);
			if(!GenerateShowAnswerHtm(paper,it_ans->second,it->second,framePath + strHtmCount,ePaperViewTypeScore))
			{
				OutputDebugString(CString("生成：") + strHtmCount + "失败");
				return FALSE;
			}
		}
	}
	return TRUE;
}