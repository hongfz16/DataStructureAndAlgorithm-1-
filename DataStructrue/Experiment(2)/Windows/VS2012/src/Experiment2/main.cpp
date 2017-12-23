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

#include"htmlFetcher.h"
using namespace std;

#define _CRT_SECURE_NO_WARNINGS

void readFromCsvAndOutput(string csvfilename,string outputfilename,vector<pageInfo>& pinfo,wordSegmentation* pdic,bool useCache)
{
	UnicodeToGBK u2g;
	cout<<"Load Complete!"<<endl;
	ifstream fin(csvfilename);
	string temp;
	fin>>temp;
	int count=0;
	while(!fin.eof())
	{
		temp.clear();
		++count;
		fin>>temp;
		if(temp.empty())
			break;
		int size=temp.length();
		int i=0;
		for(;temp[i]!='"';++i);
		string surl=temp.substr(i+1,size-i-2);
		string sinpfile = "./cache/test" + to_string(count) + ".html";
		const char* inpfile = sinpfile.data();
		char* inpurl=(char*)surl.c_str();
		TCHAR* url = new TCHAR[MAXSIZE];
#ifdef UNICODE
		MultiByteToWideChar(CP_ACP, 0, inpurl, -1, url, 100);
#else
		strcpy(url, argv[1]);
#endif
		if (!useCache)
		{
			FILE* file = fopen(inpfile, "w");
			cout << "Downloading html file..." << endl;
			fetchHTML(url, file);
			fclose(file);
		}
		cout<<"Start processing html file..."<<endl;

		
		pageInfo pi;
		CharString csurl(surl);

		string inputfilename="./cache/test"+to_string(count)+".html";
		extractKeyWords(inputfilename,outputfilename,surl,count,*pdic,u2g,pi);

		pi.setId(count);
		pi.setUrl(csurl);
		pinfo.push_back(pi);
	}

}

void buildTree(vector<pageInfo>& pinfo,mAVL<CharString,Link<pageLink> >* st)
{
	bool taller=false;
	bool success=false;
	for(int i=0;i<pinfo.size();++i)
	{
		vector<pair<CharString,int> >& wordCount=pinfo[i].getWordCount();
		CharString texts=pinfo[i].getTexts();
		CharString title=pinfo[i].getTitle();
		CharString url=pinfo[i].getUrl();
		int id=pinfo[i].getId();
		pageLink pl;
		pl.setUrl(url);
		pl.setTexts(texts);
		pl.setTitle(title);
		pl.setId(id);
		for(int j=0;j<wordCount.size();++j)
		{
			CharString k=wordCount[j].first;
			mAVL<CharString,Link<pageLink> > *tn=Insert(st,k,taller,success);
			pl.setNum(wordCount[j].second);
			Link<pageLink>& link=tn->editData();
			Link<pageLink>* p=link.getNext();
			while(p!=&link)
			{
				if(p->getElem().getNum()<pl.getNum())
				{
					break;
				}
				p=p->getNext();
			}
			link.insert(p,pl);
		}
	}
}


int main(int argc, char* argv[])
{
	bool useCache=false;
	string temp;
	bool done = false;
	while (!done)
	{
		cout << "Use cached html file?\n0:Yes\n1:No" << endl;
		cin >> temp;
		if (temp == "0")
		{
			useCache = true;
			done = true;
		}
		else if (temp == "1")
		{
			useCache = false;
			done = true;
		}
	}
	std::locale::global(std::locale("chs"));
	string filename="./input/url.csv";
	string outfilename="./output/result.csv";
	ifstream sample("./config/result_sample.csv");
	string firstline;
	sample>>firstline;
	ofstream fout(outfilename);
	fout<<firstline<<endl;
	fout.close();
	vector<pageInfo> pinfo;
	wordSegmentation dic("./config/dictionary.dic","./config/specific.dic");
	readFromCsvAndOutput(filename,outfilename,pinfo,&dic,useCache);
	
	cout<<"Start building the inverted documents...\n"<<endl;
	invertedDocs idocs(pinfo,&dic);
	cout<<"Finish building the inverted documents!"<<endl;

	cout<<"Start Batch Search...\n"<<endl;
	bool usingAVL=true;
	idocs.batchSearch("query.txt","./output/result.txt",true);
	cout<<endl;
	idocs.batchSearch("query.txt","./output/result.txt",false);
	cout<<"Finish Batch Search!"<<endl;

	system("pause");

	return 0;
}