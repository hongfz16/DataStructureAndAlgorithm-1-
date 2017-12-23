/**
@brief 文档链表类
@file doclink.h
@author 洪方舟
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef DOCLINK_H
#define DOCLINK_H

#include "Link.h"
#include "pagelink.h"
#include "CharString.h"

class docLink
{
public:
	docLink();
	~docLink(){}

private:
	//包装自实现链表模板
	Link<pageLink> link;
	//单词ID
	int wordID;
	//文档数量
	int DF;
	//单词出现数目
	int Occur;

public:
	//获取链表
	Link<pageLink> *getLink();
	//添加节点
	void add(pageLink& pl);
	//搜索ID对应的节点
	Link<pageLink> *search(int id);
	//编辑ID对应的节点
	void edit(int id,pageLink& pl);
	//删除ID对应的节点
	void remove(int id);
	//设置ID
	void setID(int id);
	//获取数据
	int getID();
	int getDF();
	int getOccur();
};

#endif // DOCLINK_H
