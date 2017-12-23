/**
@brief 页面信息类
@file pageinfo.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
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
    //分词结果中单词与出现次数的统计
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
    //根据分词结果进行统计
	void setWordCount(Link<CharString> *link);
    //设置正文
	void setTexts(CharString &te);
    //设置标题
	void setTitle(CharString &ti);
    //设置URL
	void setUrl(CharString &ur);
    //设置ID
	void setId(int i);

    //获取一系列数据
	vector<pair<CharString,int> >& getWordCount();
	CharString getTexts();
	CharString getTitle();
	CharString getUrl();
	int getId();
};

#endif // PAGEINFO_H
