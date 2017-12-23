/**
@brief 下载html网页类
@file gethtmlfile.h
@author 洪方舟
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

    //获取对应url的html文件，并且存储到filename的位置
	void getUrl(QString _url, QString filename);
};

#endif // GETHTMLFILE_H
