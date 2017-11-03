#ifndef _EXTRACT_KEY_WORDS_
#define _EXTRACK_KEY_WORDS_

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include "UnicodeToGBK.h"
#include "wordSegmentation.h"
#include "Stack.h"
#include "CharString.h"
#include "Link.h"
using namespace std;

class label;
label get_label_info(CharString& html,int pos);
CharString get_close_info(CharString& html,int pos);
int find_basic_info(Stack<label>& m_stack,CharString& html,int pos,CharString* info);
int find_content(Stack<label>& m_stack,CharString& html,int pos,CharString* info);
int find_author(Stack<label>& m_stack,CharString& html,int pos,CharString* info);
int find_date(Stack<label>& m_stack,CharString& html,int pos,CharString* info);
int find_type(Stack<label>& m_stack,CharString& html,int pos,CharString* info);
void traverse_html(Stack<label>& m_stack,CharString& html,CharString* info);
bool WStringToString(const std::wstring &wstr,std::string &str);
void print_info(CharString* info,int _size,ofstream& os,wordSegmentation& dic,UnicodeToGBK& u2g);
void extractInfo(CharString* info,string filename);
void extractKeyWords(string inputfilename,string outputfilename,string url,int count,wordSegmentation& dic,UnicodeToGBK& u2g);




#endif //_EXTRACK_KEY_WORDS_