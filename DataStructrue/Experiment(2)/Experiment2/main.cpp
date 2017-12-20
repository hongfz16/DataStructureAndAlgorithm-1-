#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

#include "gethtmlfile.h"
#include "UnicodeToGBK.h"
#include "extractKeyWords.h"
#include "wordSegmentation.h"
#include "CharString.h"
#include "Link.h"
#include "pageinfo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <locale.h>

using namespace std;

void readFromCsvAndOutput(string csvfilename,string outputfilename)
{
	getHtmlFile gethtml;
	wordSegmentation dic("./config/dictionary.dic","./config/specific.dic");
	UnicodeToGBK u2g;
	qDebug()<<"Load Complete!";
	ifstream fin(csvfilename);
	string temp;
	fin>>temp;
	int count=0;
	while(!fin.eof())
	{
		temp.clear();
		++count;
		string inpfile="./cache/test"+to_string(count)+".html";
		QString qinpfile=QString::fromStdString(inpfile);
		fin>>temp;
		if(temp.empty())
			break;
		int size=temp.length();
		int i=0;
		for(;temp[i]!='"';++i);
		string surl=temp.substr(i+1,size-i-2);
		qDebug()<<"Downloading html file...";
		QString qurl=QString::fromStdString(surl);
		gethtml.getUrl(qurl,qinpfile);
		qDebug()<<"Start processing file...";
		extractKeyWords(inpfile,outputfilename,surl,count,dic,u2g);
	}
}

void mydebug()
{
	wordSegmentation dic("./config/dictionary.dic","./config/specific_test.dic");
	qDebug()<<"Load Complete!";
	ifstream fin("./debug/input");
	string temp;
	fin>>temp;
	CharString cs(temp);
	if(dic.super_dic.find(cs) != dic.super_dic.end())
	{
		cout<<"found"<<endl;
	}
	cout<<cs.getSize()<<endl;
	Link<CharString> *relink=dic.max_back_segment(cs,7);
	ofstream fout("./debug/log");
	relink->printLink(fout);
	fout<<endl;
	fout<<cs<<endl;
	//fout<<endl;//<<"after print"<<endl;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	std::locale::global(std::locale("zh_CN.GB18030"));
	MainWindow w;
	w.show();

	string filename="./input/url.csv";
	string outfilename="./output/result.csv";
	ifstream sample("./config/result_sample.csv");
	string firstline;
	sample>>firstline;
	ofstream fout(outfilename);
	fout<<firstline<<endl;
	fout.close();
	readFromCsvAndOutput(filename,outfilename);

	//mydebug();

	return a.exec();
}
