/**
@brief GUI详情页定义
@file detailedpage.cpp
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/
#include "detailedpage.h"

detailedPage::detailedPage(QWidget *parent) : QWidget(parent)
{
	layout=new QGridLayout();
	textb=new QTextBrowser();
    back=new QPushButton(QString::fromLocal8Bit("返回"));
	webView=new QWebEngineView();
	layout->addWidget(textb,0,0,2,1);
	layout->addWidget(back,2,0,1,1);
	layout->addWidget(webView,0,1,3,1);
	layout->setColumnStretch(1, 1);
	this->setLayout(layout);
	code=QTextCodec::codecForName("gb18030");
	decoder=code->makeDecoder();

	connect(back,SIGNAL(clicked()),this,SLOT(backButtonClicked()));

}

void detailedPage::setId(int _id)
{
	id=_id;
	textb->clear();
	pageInfo pi=wo->getPageInfo(id);
	string stdtitle=pi.getTitle().csToStdString();
	string stdtext=pi.getTexts().csToStdString();
	string stdurl=pi.getUrl().csToStdString();
	QByteArray titleBa(stdtitle.c_str(),stdtitle.length());
	QByteArray textBa(stdtext.c_str(),stdtext.length());
	QByteArray urlBa(stdurl.c_str(),stdurl.length());
	QString qtitle=decoder->toUnicode(titleBa);
	QString qtext=decoder->toUnicode(textBa);
	QString qurl=decoder->toUnicode(urlBa);
    textb->insertPlainText(QString::fromLocal8Bit("帖子ID: ")+QString::number(id)+QString::fromLocal8Bit("\n\n"));
    textb->insertPlainText(QString::fromLocal8Bit("帖子标题: ")+qtitle+QString::fromLocal8Bit("\n\n"));
    textb->insertPlainText(QString::fromLocal8Bit("帖子正文: ")+qtext+QString::fromLocal8Bit("\n\n"));
    textb->insertPlainText(QString::fromLocal8Bit("帖子网址: ")+qurl+QString::fromLocal8Bit("\n\n"));
	webView->load(QUrl(qurl));
	webView->show();
}

void detailedPage::backButtonClicked()
{
	emit display(1);
}
