/**
@brief ������Ϣ��
@file pageinfo.h
@author �鷽��
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef PAGEINFO_H
#define PAGEINFO_H

#include <vector>
#include <iostream>
#include "CharString.h"
#include "Link.h"

using namespace std;

class pageInfo
{
public:
	pageInfo();
	~pageInfo(){}

private:
	//���ݷִʽ���Ĵ�Ƶͳ��
	vector<pair<CharString,int> > wordCount;
	//����
	CharString texts;
	//����
	CharString title;
	//URL
	CharString url;
	//����ID
	int id;

public:
	//���ݷִʽ��ͳ�ƴ�Ƶ
	void setWordCount(Link<CharString> *link);
	//��������
	void setTexts(CharString &te);
	void setTitle(CharString &ti);
	void setUrl(CharString &ur);
	void setId(int i);

	//��ȡ����
	vector<pair<CharString,int> >& getWordCount();
	CharString getTexts();
	CharString getTitle();
	CharString getUrl();
	int getId();
};

#endif // PAGEINFO_H
