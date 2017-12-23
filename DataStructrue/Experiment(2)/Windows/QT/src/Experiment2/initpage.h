/**
@brief GUI初始化页面类
@file initpage.h
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef INITPAGE_H
#define INITPAGE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <QProgressBar>
#include <QGridLayout>
#include <QTextCursor>

#include "woogle.h"

class initPage : public QWidget
{
	Q_OBJECT
public:
	explicit initPage(QWidget *parent = nullptr);
    //设置woogle指针，并且连接信号与槽
    void setWoogle(woogle* _wo);

signals:
    //与mainwindow槽相连接，显示对应页面
	void display(int);

public slots:
    //重新下载按钮点击
	void reloadButtonClicked();
    //直接初始化按钮点击
	void initButtonClicked();
    //取消按钮点击
	void cancelButtonClicked();
    //下一步按钮点击
    void nextButtonClicked();
    //向QTextBrowser添加文字
    void addinfo(QString info);
    //初始化进度条
	void initProBar(int min,int max);
    //更新进度条
    void updataProBar(int curr);
    //初始化完成
    void initComplete();

private:
	QLabel* label;
	QPushButton* reloadButton;
	QPushButton* initButton;
	QPushButton* next;
	QPushButton* cancel;
	QProgressBar* proBar;
	QTextBrowser* textBrowser;
	QGridLayout* layout;
	woogle* wo;
};

#endif // INITPAGE_H
