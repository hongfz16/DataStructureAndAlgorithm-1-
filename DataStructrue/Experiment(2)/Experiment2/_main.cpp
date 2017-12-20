/**
@brief 程序主入口
@file main.cpp
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#include "UnicodeToGBK.h"
#include"htmlFetcher.h"
#include "extractKeyWords.h"
#include "wordSegmentation.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS

void readFromCsvAndOutput(string csvfilename,string outputfilename)
{
	wordSegmentation dic("./config/dictionary.dic","./config/specific.txt");
	UnicodeToGBK u2g;
	cout<<"Load Complete!"<<endl;
	char* inpfile = "./cache/test.html";
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
		char* inpurl=(char*)surl.c_str();
		TCHAR* url = new TCHAR[MAXSIZE];
		FILE* file = fopen(inpfile, "w");
#ifdef UNICODE
		MultiByteToWideChar(CP_ACP, 0, inpurl, -1, url, 100);
#else
		strcpy(url, argv[1]);
#endif
		cout<<"Downloading html file..."<<endl;
		fetchHTML(url,file);
		fclose(file);
		cout<<"Start processing html file..."<<endl;
		extractKeyWords(string(inpfile),outputfilename,surl,count,dic,u2g);
	}

}

int main(int argc, char* argv[])
{
	std::locale::global(std::locale("chs"));
	string filename="./input/url.csv";
	string outfilename="./output/result.csv";
	ifstream sample("./config/result_sample.csv");
	string firstline;
	sample>>firstline;
	ofstream fout(outfilename);
	fout<<firstline<<endl;
	fout.close();
	readFromCsvAndOutput(filename,outfilename);
	return 0;
}