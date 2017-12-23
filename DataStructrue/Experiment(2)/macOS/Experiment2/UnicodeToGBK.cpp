/**
@brief 将Unicode转化为GBK编码的类的定义
@file UnicodeToGBK.cpp
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#include "UnicodeToGBK.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

UnicodeToGBK::UnicodeToGBK()
{
	ifstream fin("./config/UnicodeToGBK.csv");
	string line;
	while(!fin.eof())
	{
		line.clear();
		fin>>line;
		string uni(line.begin(),line.begin()+4);
		string gbk(line.begin()+5,line.end());
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
		uni2gbk[uni_int]=gbk_int;
	}
	fin.close();
}

UnicodeToGBK::~UnicodeToGBK(){}

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