/**
@brief 中文分词类的声明
@file wordSegmentation.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#ifndef _WORD_SEGMENTATION_
#define _WORD_SEGMENTATION_

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include "CharString.h"
#include "Link.h"
#include "pageinfo.h"

using namespace std;

class wordSegmentation
{
public:
	//初始化词典，第一个参数为普通词典，第二个参数为专业词汇词典
	wordSegmentation(string filename,string super_filename);

	//析构函数，释放空间
	~wordSegmentation();

	//参数为待分词的字符串以及逆向最大匹配法中的最大匹配字符数，返回一个字符串列表
	Link<CharString>* max_back_segment(CharString& incstring,int max);

	//分词接口
	Link<CharString>* divideWords(CharString& incstring,int max);

//private:
	//存储普通词典的词条
	set<CharString> dic;

	//存储专业词汇词典的词条
	set<CharString> super_dic;
};

#endif
