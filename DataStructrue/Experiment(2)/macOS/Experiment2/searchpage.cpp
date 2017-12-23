#include "searchpage.h"

searchPage::searchPage(QWidget *parent) : QWidget(parent)
{
	wo=nullptr;
	layout=new QGridLayout();
	lineedit=new QLineEdit();
	list=new QListWidget();
	avlsearch=new QPushButton("AVL树搜索");
	hashsearch=new QPushButton("哈希表搜索");
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
	info->setText(QString("搜索总耗时")+QString::number(end-start)+QString("毫秒; ")+QString("共搜索得到")+QString::number(result.size())+QString("条结果;"));
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
