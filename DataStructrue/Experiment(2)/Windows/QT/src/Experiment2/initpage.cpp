/**
@brief GUI初始化界面定义
@file initpage.cpp
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/
#include "initpage.h"

initPage::initPage(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(QString::fromLocal8Bit("<h1>检索初始化</h1>"));
    reloadButton = new QPushButton(QString::fromLocal8Bit("重新下载网页"));
    initButton = new QPushButton(QString::fromLocal8Bit("使用本地缓存"));
    next = new QPushButton(QString::fromLocal8Bit("下一步"));
	next->setEnabled(false);
    cancel = new QPushButton(QString::fromLocal8Bit("取消"));
	proBar = new QProgressBar();
	textBrowser = new QTextBrowser();
	layout = new QGridLayout();

	layout->addWidget(label,0,0,1,2);
	layout->addWidget(reloadButton,1,0,1,1);
	layout->addWidget(initButton,1,1,1,1);
	layout->addWidget(proBar,2,0,1,2);
	layout->addWidget(textBrowser,3,0,2,2);
	layout->addWidget(next,5,1,1,1);
	layout->addWidget(cancel,5,0,1,1);

	this->setLayout(layout);

	connect(reloadButton,SIGNAL(clicked()),this,SLOT(reloadButtonClicked()));
	connect(initButton,SIGNAL(clicked()),this,SLOT(initButtonClicked()));
	connect(cancel,SIGNAL(clicked()),this,SLOT(cancelButtonClicked()));
    connect(next,SIGNAL(clicked()),this,SLOT(nextButtonClicked()));
}

void initPage::setWoogle(woogle *_wo)
{
    wo=_wo;
    connect(wo,SIGNAL(updataProBar(int)),this,SLOT(updataProBar(int)));
    connect(wo,SIGNAL(initProBar(int,int)),this,SLOT(initProBar(int,int)));
    connect(wo,SIGNAL(appendText(QString)),this,SLOT(addinfo(QString)));
    connect(wo,SIGNAL(initComplete()),this,SLOT(initComplete()));
}

void initPage::reloadButtonClicked()
{
	textBrowser->setPlainText("");
	reloadButton->setEnabled(false);
	initButton->setEnabled(false);
	wo->Stop=false;
	wo->setReloadHtml(true);
	wo->start();
}

void initPage::initButtonClicked()
{
	textBrowser->setPlainText("");
	reloadButton->setEnabled(false);
	initButton->setEnabled(false);
	wo->Stop=false;
	wo->setReloadHtml(false);
	wo->start();
}

void initPage::cancelButtonClicked()
{
	wo->Stop=true;
	reloadButton->setEnabled(true);
	initButton->setEnabled(true);
	textBrowser->insertPlainText(QString("Canceled!\n"));
	textBrowser->moveCursor(QTextCursor::End);
}

void initPage::nextButtonClicked()
{
	//cout<<"nextButtonClicked"<<endl;
	emit display(1);
}

void initPage::addinfo(QString info)
{
	textBrowser->insertPlainText(info);
	textBrowser->moveCursor(QTextCursor::End);
}

void initPage::initProBar(int min, int max)
{
	proBar->setRange(min,max);
}

void initPage::updataProBar(int curr)
{
	proBar->setValue(curr);
}

void initPage::initComplete()
{
	next->setEnabled(true);
	cancel->setEnabled(false);
}


