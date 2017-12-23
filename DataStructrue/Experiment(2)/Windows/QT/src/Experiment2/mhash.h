/**
@brief 哈希表类
@file mhash.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
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
	mHash(vector<pageInfo>& pinfo);
	~mHash();

private:
    //冲突处理使用vector
	vector<pair<CharString,docLink*> >* dl;
    //大素数
    long magicNum;
    //哈希函数
    long hashFunc(CharString& cs);

public:
    //插入新纪录
	void insert(pageInfo& pi);
    //搜索关键字，返回文档链表
    docLink* search(CharString& cs);

};

#endif
