/**
@brief ����html��ҳ��
@file gethtmlfile.h
@author �鷽��
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef GETHTMLFILE_H
#define GETHTMLFILE_H
#include <QString>

class getHtmlFile
{
public:
	getHtmlFile();
	~getHtmlFile(){}

    //��ȡ��Ӧurl��html�ļ������Ҵ洢��filename��λ��
	void getUrl(QString _url, QString filename);
};

#endif // GETHTMLFILE_H
