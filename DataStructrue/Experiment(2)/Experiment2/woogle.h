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

	void init(string _csvfilename,string _outputfilename,bool _reloadHtml);
	void batchSearch(string inputfilename, string outputfilename);
	vector<pageInfo> onlineSearch(QString query);
	pageInfo getPageInfo(int id);

signals:
	void updataProBar(int);
	void initProBar(int,int);
	void appendText(QString);
	void initComplete();

private:
	vector<pageInfo> pinfo;
	invertedDocs *pidocs;
	wordSegmentation *pdic;
	string csvfilename;
	string outputfilename;
	bool reloadHtml;

public:
	void setCsvfilename(string fname) {csvfilename=fname;}
	void setOutputfilename(string fname) {outputfilename=fname;}
	void setReloadHtml(bool reload) {reloadHtml=reload;}
};

#endif // WOOGLE_H
