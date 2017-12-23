/**
@brief ��Ҫҵ���߼���
@file woogle.h
@author �鷽��
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

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

    //�����������ҳ��ַ���г�ʼ��������ѡ��ʹ�ñ��ػ����ļ�
	void init(string _csvfilename,string _outputfilename,bool _reloadHtml);
    //����������
	void batchSearch(string inputfilename, string outputfilename);
    //�����������������û�����Ĳ�ѯ���֣����ؽ��
	vector<pageInfo> onlineSearch(QString query,bool useAVL);
    //��ȡҳ����Ϣ
	pageInfo getPageInfo(int id);

signals:
    //���½������ź�
	void updataProBar(int);
    //��ʼ���������ź�
	void initProBar(int,int);
    //���ı�������������ź�
	void appendText(QString);
    //��ʼ������ź�
	void initComplete();

private:
    //�������ӵ���Ϣ
    vector<pageInfo> pinfo;
    //�����ĵ�
	invertedDocs *pidocs;
    //�ִ���
	wordSegmentation *pdic;
    //�����ļ���
	string csvfilename;
    //����ļ���
	string outputfilename;
    //�Ƿ���Ҫ����������ҳ
	bool reloadHtml;

public:
    //Ԥ��������
	void setCsvfilename(string fname) {csvfilename=fname;}
	void setOutputfilename(string fname) {outputfilename=fname;}
	void setReloadHtml(bool reload) {reloadHtml=reload;}
};

#endif // WOOGLE_H
