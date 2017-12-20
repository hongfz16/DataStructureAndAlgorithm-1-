/**
@brief 栈结构网页解析函数声明
@file extractKeyWords.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#ifndef _EXTRACT_KEY_WORDS_
#define _EXTRACT_KEY_WORDS_

#include <iostream>
#include <fstream>
#include <string>

#include "UnicodeToGBK.h"
#include "wordSegmentation.h"
#include "Stack.h"
#include "CharString.h"
#include "Link.h"
using namespace std;

//自定义结构用于存放html标签信息
class label;

//传入整个文本的引用与当前位置，返回标签信息
label get_label_info(CharString& html,int pos);

//传入整个文本的引用与当前位置，返回闭合标签信息
CharString get_close_info(CharString& html,int pos);

//提取发帖大类，发帖小类，发帖标题，返回值为查找结束后所在位置
int find_basic_info(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//提取发帖内容，返回值为查找结束后所在位置
int find_content(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//提取发帖人，返回值为查找结束后所在位置
int find_author(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//提取发帖日期，返回值为查找结束后所在位置
int find_date(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//提取发帖类型，返回值为查找结束后所在位置
int find_type(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//栈结构遍历html文本内容总函数，负责调用上面的各个函数
void traverse_html(Stack<label>& m_stack,CharString& html,CharString* info);

//提取信息结束后将info内的信息以csv格式输出，并实现部分网页内容的转码，以及将分词结果输出
void print_info(CharString* info, int _size, ofstream& os, wordSegmentation& dic, UnicodeToGBK& u2g, pageInfo pinfo);

//初始化html文本内容，调用traverse_html函数
void extractInfo(CharString* info,string filename);

//传入html文件名，输出文件名，开始解析网页内容
void extractKeyWords(string inputfilename, string outputfilename, string url, int count, wordSegmentation& dic, UnicodeToGBK& u2g, pageInfo &pinfo);




#endif //_EXTRACK_KEY_WORDS_
