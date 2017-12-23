/**
@brief ���ķִ��������
@file wordSegmentation.h
@author �鷽��
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
	//��ʼ���ʵ䣬��һ������Ϊ��ͨ�ʵ䣬�ڶ�������Ϊרҵ�ʻ�ʵ�
	wordSegmentation(string filename,string super_filename);

	//�����������ͷſռ�
	~wordSegmentation();

	//����Ϊ���ִʵ��ַ����Լ��������ƥ�䷨�е����ƥ���ַ���������һ���ַ����б�
	Link<CharString>* max_back_segment(CharString& incstring,int max);

	//�ִʽӿ�
	Link<CharString>* divideWords(CharString& incstring,int max);

//private:
	//�洢��ͨ�ʵ�Ĵ���
	set<CharString> dic;

	//�洢רҵ�ʻ�ʵ�Ĵ���
	set<CharString> super_dic;
};

#endif
