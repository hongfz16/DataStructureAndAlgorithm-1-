/**
@brief 倒排文档类
@file inverteddocs.h
@author 洪方舟
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef INVERTEDDOCS_H
#define INVERTEDDOCS_H

#include "mAVL.h"
#include "CharString.h"
#include "doclink.h"
#include "pageinfo.h"
#include "wordSegmentation.h"
#include "mHash.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class invertedDocs
{
public:
	invertedDocs();
	//根据帖子信息构造倒排文档
	invertedDocs(vector<pageInfo>& pinfos,wordSegmentation* _dic);
	~invertedDocs();

private:
	//AVL树
	mAVL<CharString,docLink>* mtree;
	//哈希表
	mHash* mhash;
	//分词器
	wordSegmentation* dic;

public:
	//使用AVL搜索key对应的帖子
	docLink* Search(CharString key);
	//使用Hash搜索key对应的帖子
	docLink* hashSearch(CharString key);
	//添加文档
	void addDoc(pageInfo& pinfo);
	//获取查询信息
	vector<pair<int, int> > getResult(vector<CharString> queries,bool choose);
	//打印查询信息到输出流
	void printResult(vector<pair<int, int> > &re, ofstream &fout);
	//本地批查询，传入查询文件名和结果存放地址
	void batchSearch(string filename, string outputfilename,bool choose);
};

#endif // INVERTEDDOCS_H
