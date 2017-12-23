/**
@brief ջ�ṹ��ҳ������������
@file extractKeyWords.h
@author �鷽��
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

//�Զ���ṹ���ڴ��html��ǩ��Ϣ
class label;

//���������ı��������뵱ǰλ�ã����ر�ǩ��Ϣ
label get_label_info(CharString& html,int pos);

//���������ı��������뵱ǰλ�ã����رպϱ�ǩ��Ϣ
CharString get_close_info(CharString& html,int pos);

//��ȡ�������࣬����С�࣬�������⣬����ֵΪ���ҽ���������λ��
int find_basic_info(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//��ȡ�������ݣ�����ֵΪ���ҽ���������λ��
int find_content(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//��ȡ�����ˣ�����ֵΪ���ҽ���������λ��
int find_author(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//��ȡ�������ڣ�����ֵΪ���ҽ���������λ��
int find_date(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//��ȡ�������ͣ�����ֵΪ���ҽ���������λ��
int find_type(Stack<label>& m_stack,CharString& html,int pos,CharString* info);

//ջ�ṹ����html�ı������ܺ����������������ĸ�������
void traverse_html(Stack<label>& m_stack,CharString& html,CharString* info);

//��ȡ��Ϣ������info�ڵ���Ϣ��csv��ʽ�������ʵ�ֲ�����ҳ���ݵ�ת�룬�Լ����ִʽ�����
void print_info(CharString* info, int _size, ofstream& os, wordSegmentation& dic, UnicodeToGBK& u2g, pageInfo &pinfo);

//��ʼ��html�ı����ݣ�����traverse_html����
void extractInfo(CharString* info,string filename);

//����html�ļ���������ļ�������ʼ������ҳ����
void extractKeyWords(string inputfilename, string outputfilename, string url, int count, wordSegmentation& dic, UnicodeToGBK& u2g, pageInfo &pinfo);




#endif //_EXTRACK_KEY_WORDS_
