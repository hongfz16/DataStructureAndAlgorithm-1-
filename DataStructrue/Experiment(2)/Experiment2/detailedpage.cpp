#include "detailedpage.h"

detailedPage::detailedPage(QWidget *parent) : QWidget(parent)
{
	layout=new QGridLayout();
	textb=new QTextBrowser();
	back=new QPushButton("返回");
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
	textb->insertPlainText(QString("帖子ID: ")+QString::number(id)+QString("\n"));
	textb->insertPlainText(QString("帖子标题: ")+qtitle+QString("\n"));
	textb->insertPlainText(QString("帖子正文: ")+qtext+QString("\n"));
	textb->insertPlainText(QString("帖子网址: ")+qurl+QString("\n"));
	webView->load(QUrl(qurl));
	webView->show();
}

void detailedPage::backButtonClicked()
{
	emit display(1);
}
