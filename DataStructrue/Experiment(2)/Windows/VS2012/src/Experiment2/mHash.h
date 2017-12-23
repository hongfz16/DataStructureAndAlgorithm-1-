/**
@brief 哈希表类
@file mHash.h
@author 洪方舟
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef _MHASH_H_
#define _MHASH_H_

#include <iostream>
#include <string>
#include <vector>
#include "CharString.h"
#include "doclink.h"
#include "pageinfo.h"
#include "wordSegmentation.h"

class mHash
{
public:
	//根据传入帖子的信息构造哈希表
	mHash(vector<pageInfo>& pinfo);
	~mHash();

private:
	//处理冲突使用vector
	vector<pair<CharString,docLink*> >* dl;
	//大素数
	long magicNum;
	//哈希函数
	long hashFunc(CharString& cs);

public:
	//插入节点
	void insert(pageInfo& pi);
	//搜索文档
	docLink* search(CharString& cs);

};

#endif