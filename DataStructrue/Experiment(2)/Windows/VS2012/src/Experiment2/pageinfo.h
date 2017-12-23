/**
@brief 帖子信息类
@file pageinfo.h
@author 洪方舟
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef PAGEINFO_H
#define PAGEINFO_H

#include <vector>
#include <iostream>
#include "CharString.h"
#include "Link.h"

using namespace std;

class pageInfo
{
public:
	pageInfo();
	~pageInfo(){}

private:
	//根据分词结果的词频统计
	vector<pair<CharString,int> > wordCount;
	//正文
	CharString texts;
	//标题
	CharString title;
	//URL
	CharString url;
	//文章ID
	int id;

public:
	//根据分词结果统计词频
	void setWordCount(Link<CharString> *link);
	//设置数据
	void setTexts(CharString &te);
	void setTitle(CharString &ti);
	void setUrl(CharString &ur);
	void setId(int i);

	//获取数据
	vector<pair<CharString,int> >& getWordCount();
	CharString getTexts();
	CharString getTitle();
	CharString getUrl();
	int getId();
};

#endif // PAGEINFO_H
