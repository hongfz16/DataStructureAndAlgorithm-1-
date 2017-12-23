/**
@brief 主要业务逻辑类
@file woogle.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef WOOGLE_H
#define WOOGLE_H

#include <QString>
#include <QTextCodec>
#include <QTextBrowser>
#include <QProgressBar>
#include <QThread>
#include <QMutex>
#include <QObject>

#include "gethtmlfile.h"
#include "UnicodeToGBK.h"
#include "extractKeyWords.h"
#include "wordSegmentation.h"
#include "CharString.h"
#include "Link.h"
#include "pageinfo.h"
#include "mAVL.h"
#include "pagelink.h"
#include "inverteddocs.h"
#include "doclink.h"

#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <locale.h>
using namespace std;

class woogle : public QThread
{
	Q_OBJECT
public:
	//woogle();
	explicit woogle(QObject *parent = 0, bool b = false);
	~woogle();

	void run();

	bool Stop;

    //根据输入的网页地址进行初始化，可以选择使用本地缓存文件
	void init(string _csvfilename,string _outputfilename,bool _reloadHtml);
    //本地批搜索
	void batchSearch(string inputfilename, string outputfilename);
    //在线搜索，即接受用户输入的查询文字，返回结果
	vector<pageInfo> onlineSearch(QString query,bool useAVL);
    //获取页面信息
	pageInfo getPageInfo(int id);

signals:
    //更新进度条信号
	void updataProBar(int);
    //初始化进度条信号
	void initProBar(int,int);
    //在文本框中添加文字信号
	void appendText(QString);
    //初始化完成信号
	void initComplete();

private:
    //所有帖子的信息
    vector<pageInfo> pinfo;
    //倒排文档
	invertedDocs *pidocs;
    //分词类
	wordSegmentation *pdic;
    //输入文件名
	string csvfilename;
    //输出文件名
	string outputfilename;
    //是否需要重新下载网页
	bool reloadHtml;

public:
    //预设置数据
	void setCsvfilename(string fname) {csvfilename=fname;}
	void setOutputfilename(string fname) {outputfilename=fname;}
	void setReloadHtml(bool reload) {reloadHtml=reload;}
};

#endif // WOOGLE_H
