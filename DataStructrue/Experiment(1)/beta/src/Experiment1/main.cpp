#include "UnicodeToGBK.h"
#include"htmlFetcher.h"
#include "extractKeyWords.h"
#include "wordSegmentation.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void readFromCsvAndOutput(string csvfilename,string outputfilename)
{
	wordSegmentation dic("dictionary.dic","specific.txt");
	UnicodeToGBK u2g;
	cout<<"Load Complete!"<<endl;
	char* inpfile = "test.html";
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
		//cout<<temp<<endl;
		int size=temp.length();
		int i=0;
		for(;temp[i]!='"';++i);
		string surl=temp.substr(i+1,size-i-2);
		char* inpurl=(char*)surl.c_str();
		TCHAR* url = new TCHAR[MAXSIZE];
		FILE* file = fopen(inpfile, "w");
#ifdef UNICODE
		MultiByteToWideChar(CP_ACP, 0, inpurl, -1, url, 100);
#else
		strcpy(url, argv[1]);
#endif
		fetchHTML(url,file);
		fclose(file);

		//do something
		extractKeyWords(string(inpfile),outputfilename,surl,count,dic,u2g);
	}

}

int main(int argc, char* argv[])
{
	std::locale::global(std::locale("chs"));
	string filename="url.csv";
	string outfilename="out.csv";
	ifstream sample("result_sample.csv");
	string firstline;
	sample>>firstline;
	ofstream fout(outfilename);
	fout<<firstline<<endl;
	fout.close();
	readFromCsvAndOutput(filename,outfilename);
	return 0;
}