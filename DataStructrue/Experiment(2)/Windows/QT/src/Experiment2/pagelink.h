/**
@brief 文档链表节点类
@file pagelink.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef PAGELINK_H
#define PAGELINK_H

#include "CharString.h"
#include <iostream>
using namespace std;

class pageLink
{
public:
	pageLink();
	~pageLink(){}

private:
    //单词出现次数
	int num;
    //文章URL
	CharString url;
    //文章正文
	CharString texts;
    //文章标题
	CharString title;
    //文章ID
	int id;

public:
    //设置数据
	void setNum(int n);
	void setUrl(CharString &ur);
	void setTexts(CharString &te);
	void setTitle(CharString &ti);
	void setId(int i);

    //获取数据
	int getNum();
	CharString getUrl();
	CharString getTexts();
	CharString getTitle();
	int getId();

};

#endif // PAGELINK_H
