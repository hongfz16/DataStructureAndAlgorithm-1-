#include "woogle.h"

woogle::woogle(QObject *parent, bool b) :
	QThread(parent),Stop(b)
{
	csvfilename="./input/url.csv";
	outputfilename="./output/result.csv";
	pdic=nullptr;
	pidocs=nullptr;
}

woogle::~woogle()
{
	delete pidocs;
	delete pdic;
}

void woogle::run()
{
	init(csvfilename,outputfilename,reloadHtml);
}

void woogle::init(string csvfilename, string outputfilename, bool reloadHtml)
{
	//QMutex mutex;
	//mutex.lock();

	//proBar->setRange(0,2003);
	emit initProBar(0,2003);

	if(pdic==nullptr)
		pdic=new wordSegmentation("./config/dictionary.dic","./config/specific.dic");
	getHtmlFile gethtml;
	UnicodeToGBK u2g;
	cout<<"Load Complete!"<<endl;

	//textBrowser->insertPlainText("Load Dictinary Complete!");
	emit appendText(QString("Load Dictinary Complete!\n"));
	//proBar->setValue(1);
	emit updataProBar(1);

	ifstream fin(csvfilename);
	string temp;
	fin>>temp;
	int count=0;
	while(!fin.eof())
	{
		if(this->Stop)
			return;
		//mutex.unlock();

		temp.clear();
		++count;
		fin>>temp;
		if(temp.empty())
			break;
		int size=temp.length();
		int i=0;
		for(;temp[i]!='"';++i);
		string surl=temp.substr(i+1,size-i-2);
		string inpfile="./cache/test"+to_string(count)+".html";
		QString qurl=QString::fromStdString(surl);

		if(reloadHtml)
		{
			QString qinpfile=QString::fromStdString(inpfile);

			cout<<"Downloading "<<count<<"th html file..."<<endl;

			QString disstr=QString("Downloading ")+QString::number(count)+QString("th html file: ")+qurl+QString("\n");
			//textBrowser->insertPlainText(disstr);
			emit appendText(disstr);

			gethtml.getUrl(qurl,qinpfile);
		}

		cout<<"Start processing "<<count<<"th file..."<<endl;


		QString disstr=QString("Processing ")+QString::number(count)+QString("th html file: ")+qurl+QString("\n");
		//textBrowser->insertPlainText(disstr);
		emit appendText(disstr);

		pageInfo pi;
		CharString csurl(surl);
		extractKeyWords(inpfile,outputfilename,surl,count,*pdic,u2g,pi);
		pi.setId(count);
		pi.setUrl(csurl);
		pinfo.push_back(pi);

		//proBar->setValue(count+1);
		emit updataProBar(count+1);


	}

	//textBrowser->insertPlainText("Building the inverted document...");
	emit appendText(QString("Building the inverted document...\n"));

	cout<<"Start building the inverted document..."<<endl;
	if(pidocs==nullptr)
		pidocs=new invertedDocs(pinfo,pdic);
	else
	{
		delete pidocs;
		pidocs=new invertedDocs(pinfo,pdic);
	}
	cout<<"Finish building the inverted document"<<endl;
	emit appendText(QString("Finish initialization!\n"));

	//proBar->setValue(2003);
	emit updataProBar(2003);
	emit initComplete();
}

void woogle::batchSearch(string inputfilename, string outputfilename)
{
	pidocs->batchSearch(inputfilename,outputfilename);
}

vector<pageInfo> woogle::onlineSearch(QString query)
{
	vector<pageInfo> repi;
	//QByteArray qba=query.toUtf8();
	QTextCodec* codec=QTextCodec::codecForName("gb18030");
	//QTextDecoder* decoder=code->makeDecoder();
	//qs=decoder->toUnicode(qba);
	QByteArray encodedString=codec->fromUnicode(query);
	string gbstdstr(encodedString.constData(),encodedString.length());
	vector<CharString> queries;
	for(int i=0;i<gbstdstr.length();++i)
	{
		string word;
		int j=0;
		for(j=i;j<gbstdstr.length();++j)
		{
			if(j!=' ')
				word+=gbstdstr[j];
			else
				break;
		}
		i=j;
		CharString cs(word);
		queries.push_back(cs);
	}
	vector<pair<int,int> > rawre=pidocs->getResult(queries);
	for(int i=0;i<rawre.size();++i)
	{
		repi.push_back(pinfo[rawre[i].first-1]);
	}
	return repi;
}
