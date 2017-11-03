#include "UnicodeToGBK.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

UnicodeToGBK::UnicodeToGBK()
{
	ifstream fin("UnicodeToGBK.csv");
	//if(fin.is_open())
	//	cout<<"opened"<<endl;
	string line;
	while(!fin.eof())
	{
		line.clear();
		fin>>line;
		string uni(line.begin(),line.begin()+4);
		//cout<<uni<<",";
		string gbk(line.begin()+5,line.end());
		//cout<<gbk<<endl;
		uni="0x"+uni;
		gbk="0x"+gbk;
		int uni_int;
		char cuni[7];
		char cgbk[7];
		for(int i=0;i<6;++i)
		{
			cuni[i]=uni[i];
			cgbk[i]=gbk[i];
		}
		cuni[6]='\0';
		cgbk[6]='\0';
		sscanf(cuni,"%X",&uni_int);
		int gbk_int;
		sscanf(cgbk,"%X",&gbk_int);
		//cout<<uni_int<<","<<gbk_int<<endl;
		uni2gbk[uni_int]=gbk_int;
	}
	fin.close();
}

UnicodeToGBK::~UnicodeToGBK(){}

wchar_t* UnicodeToGBK::convert(char* content,int length)
{
	if(length%8!=0)
		return nullptr;
	int size=length/8;
	wchar_t* re=new wchar_t[size];
	for(int i=0;i<length;++i)
	{
		i+=2;
		int sum=0;
		for(int count=0;count<5;++count,++i)
		{
			sum=sum*10+content[i]-'0';
		}
		//cout<<sum<<endl;
		//if(uni2gbk.find(sum)!=uni2gbk.end())
		//	cout<<"Found"<<endl;
		int gbk=uni2gbk[sum];
		re[i/8]=(gbk);
	}
	return re;
}

int* UnicodeToGBK::convert_int(char* content,int length)
{
	if(length%8!=0)
		return nullptr;
	int size=length/8;
	int* re=new int[size];
	for(int i=0;i<length;++i)
	{
		i+=2;
		int sum=0;
		for(int count=0;count<5;++count,++i)
		{
			sum=sum*10+content[i]-'0';
		}
		//cout<<sum<<endl;
		//if(uni2gbk.find(sum)!=uni2gbk.end())
		//	cout<<"Found"<<endl;
		int gbk=uni2gbk[sum];
		re[i/8]=(gbk);
	}
	return re;
}

int* UnicodeToGBK::convert_single(int uni)
{
	int gbk=uni2gbk[uni];
	int* re=new int[2];
	int temp=gbk;
	temp=temp>>8;
	temp&=((1<<8)-1);
	re[0]=temp;
	temp=gbk;
	temp&=((1<<8)-1);
	re[1]=temp;
	return re;
}