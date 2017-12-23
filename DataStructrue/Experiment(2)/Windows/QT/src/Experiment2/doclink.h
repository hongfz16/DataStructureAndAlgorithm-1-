/**
@brief 文档链表类
@file doclink.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
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
    //封装自实现链表模板类
	Link<pageLink> link;
    //当前文档链表对应的单词ID
	int wordID;
    //文档数目
	int DF;
    //该单词在文档中出现次数
	int Occur;

public:
    //获取文档链表
	Link<pageLink> *getLink();
    //添加文档链表节点
    void add(pageLink& pl);
    //搜索文章ID对应的节点
    Link<pageLink> *search(int id);
    //修改对应文章ID节点的信息
	void edit(int id,pageLink& pl);
    //删除对应文章
	void remove(int id);
    //设置单词ID
	void setID(int id);
    //获取单词ID
	int getID();
    //获取文档数目
	int getDF();
    //获取单词出现总次数
	int getOccur();
};

#endif // DOCLINK_H
