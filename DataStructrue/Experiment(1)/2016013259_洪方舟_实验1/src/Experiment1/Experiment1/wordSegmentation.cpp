/**
@brief 中文分词类函数定义
@file wordSegmentation.cpp
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#include "wordSegmentation.h"

wordSegmentation::wordSegmentation(string filename,string super_filename)
{
	ifstream fin(filename);
	string temp;
	int count=0;
	while(!fin.eof())
	{
		count++;
		temp.clear();
		fin>>temp;
		CharString cs(temp); 
		dic.insert(cs);
	}
	fin.close();
	ifstream sfin(super_filename);
	count=0;
	while(!sfin.eof())
	{
		count++;
		temp.clear();
		sfin>>temp;
		CharString cs(temp);
		super_dic.insert(cs);
	}
	sfin.close();
}

wordSegmentation::~wordSegmentation(){}

Link<CharString>* wordSegmentation::max_back_segment(CharString& incstring,int max)
{
	Link<CharString>* relink=new Link<CharString>();
	int pos=incstring.getSize()-1;
	for(int i=pos;i>=0;--i)
	{
		if(incstring.getIndex(i)==' ')
		{
			continue;
		}
		if(incstring.getIndex(i)==0)
		{
			CharString recs;
			--i;
			while(i>=0 && incstring.getIndex(i)!=0)
			{
				recs.append(incstring.getIndex(i));
				--i;
			}
			CharString reverse;
			for(int ii=recs.getSize()-1;ii>=0;--ii)
			{
				reverse.append(recs.getIndex(ii));
			}
			if(relink->empty())
				relink->add(reverse);
			else
				relink->insert(relink->getNode(0),reverse);
			continue;
		}
		int length=0;
		if(i-max*2+1>=0)
			length=max;
		else
			length=(i-1)/2+1;
		for(;length>=1;--length)
		{
			CharString sub=incstring.subString(i-length*2+1,length*2);
			if(super_dic.find(sub)!=super_dic.end())
			{
				if(relink->empty())
					relink->add(sub);
				else
					relink->insert(relink->getNode(0),sub);
				i=i-length*2+1;
				break;
			}
			if(length==1 || dic.find(sub)!=dic.end())
			{
				if(relink->empty())
					relink->add(sub);
				else
					relink->insert(relink->getNode(0),sub);
				i=i-length*2+1;
				break;
			}
		}
	}
	return relink;
}

Link<CharString>* wordSegmentation::divideWords(CharString& incstring,int max)
{
	return max_back_segment(incstring,max);
}
