/**
@brief ҳ����Ϣ��
@file pageinfo.h
@author �鷽��
@email hongfz16@163.com
@version 2.0
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
    //�ִʽ���е�������ִ�����ͳ��
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
    //���ݷִʽ������ͳ��
	void setWordCount(Link<CharString> *link);
    //��������
	void setTexts(CharString &te);
    //���ñ���
	void setTitle(CharString &ti);
    //����URL
	void setUrl(CharString &ur);
    //����ID
	void setId(int i);

    //��ȡһϵ������
	vector<pair<CharString,int> >& getWordCount();
	CharString getTexts();
	CharString getTitle();
	CharString getUrl();
	int getId();
};

#endif // PAGEINFO_H
