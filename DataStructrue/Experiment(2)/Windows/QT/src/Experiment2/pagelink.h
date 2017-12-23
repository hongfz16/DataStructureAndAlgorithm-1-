/**
@brief �ĵ�����ڵ���
@file pagelink.h
@author �鷽��
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef PAGELINK_H
#define PAGELINK_H

#include "CharString.h"
#include <iostream>
using namespace std;

class pageLink
{
public:
	pageLink();
	~pageLink(){}

private:
    //���ʳ��ִ���
	int num;
    //����URL
	CharString url;
    //��������
	CharString texts;
    //���±���
	CharString title;
    //����ID
	int id;

public:
    //��������
	void setNum(int n);
	void setUrl(CharString &ur);
	void setTexts(CharString &te);
	void setTitle(CharString &ti);
	void setId(int i);

    //��ȡ����
	int getNum();
	CharString getUrl();
	CharString getTexts();
	CharString getTitle();
	int getId();

};

#endif // PAGELINK_H
