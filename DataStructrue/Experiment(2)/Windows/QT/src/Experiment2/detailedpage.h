/**
@brief GUI页面详情页
@file detailedpage.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef DETAILEDPAGE_H
#define DETAILEDPAGE_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QWebEngineView>
#include "woogle.h"
#include "pageinfo.h"
#include "CharString.h"
#include <QString>
#include <QUrl>
#include <string>
#include <QTextCodec>
#include <QTextDecoder>
using namespace std;

class detailedPage : public QWidget
{
	Q_OBJECT
public:
	explicit detailedPage(QWidget *parent = nullptr);

    //设置woogle指针
	void setWoogle(woogle* _wo) {wo=_wo;}

signals:
    //点击返回按钮触发，由mainwindow的SLOT相应，返回搜索页
	void display(int);

public slots:
    //相应搜索页双击信号，设置本页面文字与网页浏览窗口
	void setId(int _id);
    //相应返回按钮信号，触发display(1)信号
	void backButtonClicked();

private:
    //布局类
	QGridLayout* layout;
    //显示页面基本信息
    QTextBrowser* textb;
    //返回按钮
	QPushButton* back;
    //网页浏览界面
	QWebEngineView* webView;
    //woogle指针
	woogle* wo;
    //当前显示页面ID
	int id;
    //解码相关类
	QTextCodec* code;
	QTextDecoder* decoder;
};

#endif // DETAILEDPAGE_H
