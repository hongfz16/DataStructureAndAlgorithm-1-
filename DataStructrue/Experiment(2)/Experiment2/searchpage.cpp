#include "searchpage.h"

searchPage::searchPage(QWidget *parent) : QWidget(parent)
{
	wo=nullptr;
	layout=new QGridLayout();
	lineedit=new QLineEdit();
	list=new QListWidget();
	search=new QPushButton("搜索");

	layout->addWidget(lineedit,0,0,1,3);
	layout->addWidget(search,0,3,1,1);
	layout->addWidget(list,1,0,1,4);

	this->setLayout(layout);

	connect(search,SIGNAL(clicked()),this,SLOT(searchButtonClicked()));
	connect(list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(pageItemDoubleClicked(QListWidgetItem*)));
}

void searchPage::setWoogle(woogle *_wo)
{
	wo=_wo;
}

void searchPage::searchButtonClicked()
{
	query=lineedit->text();
	list->clear();
	if(query.isEmpty())
		return;
	if(wo!=nullptr)
		result=wo->onlineSearch(query);
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
}

void searchPage::pageItemDoubleClicked(QListWidgetItem *item)
{
	cout<<"double clicked"<<endl;
	int id=item->data(1).toInt();
	emit passInfoToDetailPage(id);
	emit display(2);
}
