/**
@brief 倒排文档类
@file inverteddocs.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef INVERTEDDOCS_H
#define INVERTEDDOCS_H

#include "mAVL.h"
#include "CharString.h"
#include "doclink.h"
#include "pageinfo.h"
#include "wordSegmentation.h"
#include "mhash.h"
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
    //根据传入的页面信息容器来初始化
	invertedDocs(vector<pageInfo>& pinfos,wordSegmentation* _dic);
	~invertedDocs();

private:
    //AVL树
	mAVL<CharString,docLink>* mtree;
    //哈希表
    mHash* mhash;
    //分词类
    wordSegmentation* dic;

public:
    //使用AVL树搜索关键词，返回文档链表
	docLink* Search(CharString key);
    //使用哈希表搜索，返回文档链表
	docLink* hashSearch(CharString key);
    //根据传入页面信息，添加入倒排文档
	void addDoc(pageInfo& pinfo);
    //根据传入的查询，给出结果
	vector<pair<int, int> > getResult(vector<CharString> queries, bool useAVL);
    //将结果打印到输出流中
    void printResult(vector<pair<int, int> > &re, ofstream &fout);
    //本地批搜索，传入本地查询文件名以及输出文件名
	void batchSearch(string filename, string outputfilename);
};

#endif // INVERTEDDOCS_H
