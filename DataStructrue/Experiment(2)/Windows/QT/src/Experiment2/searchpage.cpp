/**
@brief GUI����ҳ���ඨ��
@file searchpage.cpp
@author �鷽��
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/
#include "searchpage.h"

searchPage::searchPage(QWidget *parent) : QWidget(parent)
{
	wo=nullptr;
	layout=new QGridLayout();
	lineedit=new QLineEdit();
	list=new QListWidget();
    avlsearch=new QPushButton(QString::fromLocal8Bit("AVL������"));
    hashsearch=new QPushButton(QString::fromLocal8Bit("��ϣ������"));
	info=new QLabel();

	layout->addWidget(lineedit,0,0,1,2);
	layout->addWidget(avlsearch,0,2,1,1);
	layout->addWidget(hashsearch,0,3,1,1);
	layout->addWidget(list,1,0,1,4);
	layout->addWidget(info,2,3,1,1);

	this->setLayout(layout);

	connect(avlsearch,SIGNAL(clicked()),this,SLOT(AVLSearchButtonClicked()));
	connect(hashsearch,SIGNAL(clicked()),this,SLOT(HashSearchButtonClicked()));
	connect(list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(pageItemDoubleClicked(QListWidgetItem*)));
}

void searchPage::setWoogle(woogle *_wo)
{
	wo=_wo;
}

void searchPage::searchButtonClicked(bool useAVL)
{
	clock_t start,end;
	query=lineedit->text();
	list->clear();
	if(query.isEmpty())
		return;
	if(wo!=nullptr)
	{
		start=clock();
		result=wo->onlineSearch(query,useAVL);
		end=clock();
	}
	else
		return;
	QTextCodec* code=QTextCodec::codecForName("gb18030");
	QTextDecoder* decoder=code->makeDecoder();
	for(int i=result.size()-1;i>=0;--i)
	{
		string stdtitle=result[i].getTitle().csToStdString();
		QByteArray ba(stdtitle.c_str(), stdtitle.length());
		QString qstitle;
		qstitle=decoder->toUnicode(ba);
		QListWidgetItem* qlwi=new QListWidgetItem();
		qlwi->setText(qstitle);
		qlwi->setData(1,result[i].getId());
		list->addItem(qlwi);
	}
    info->setText(QString::fromLocal8Bit("�����ܺ�ʱ")+QString::number(end-start)+QString::fromLocal8Bit("����; ")+QString::fromLocal8Bit("�������õ�")+QString::number(result.size())+QString::fromLocal8Bit("�����;"));
}

void searchPage::pageItemDoubleClicked(QListWidgetItem *item)
{
	cout<<"double clicked"<<endl;
	int id=item->data(1).toInt();
	emit passInfoToDetailPage(id);
	emit display(2);
}

void searchPage::AVLSearchButtonClicked()
{
	searchButtonClicked(true);
}

void searchPage::HashSearchButtonClicked()
{
	searchButtonClicked(false);
}
