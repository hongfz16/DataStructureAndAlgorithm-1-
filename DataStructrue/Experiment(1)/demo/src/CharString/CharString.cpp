#include <iostream>
#include "CharString.h"

CharString::init_size=1000;

CharString::delta_size=10;

CharString::CharString()
{
	base=new char[init_size];
	num=0;
	size=init_size;
}

CharString::CharString(char init)
{
	base=new char[init_size];
	num=1;
	base[0]=init;
	size=init_size;
}

CharString::CharString(char init,int _num)
{
	base=new char[_num];
	num=_num;
	size=_num;
	for(int i=0;i<num;++i)
	{
		base[i]=init;
	}
}

CharString::CharString(string& init)
{
	int _num=init.length();
	base=new char[_num];
	num=_num;
	size=_num;
	for(int i=0;i<num;++i)
	{
		base[i]=init[i];
	}
}

CharString::CharString(char* init)
{
	int count=0;
	for(;init[count]!='\0';++count);
	base=new char[count];
	num=count;
	size=count;
	for(int i=0;i<count;++i)
	{
		base[i]=init[i];
	}
}

CharString::~CharString()
{
	delete base;
}

int CharString::indexOf(CharString& targetString,int pos)
{
	//TODO
}

CharString* CharString::subString(int pos,int len)
{
	if(pos+len>num || pos<0 || len<0)
	{
		std::cerr<<"Out of range"<<std::endl;
		throw;
	}
	CharString* reString=new CharString();
	for(int i=0;i<len;++i)
	{
		reString->append(base[pos+i]);
	}
	return reString;
}

CharString* CharString::concat(CharString& targetString)
{
	CharString* reString=new CharString();
	for(int i=0;i<num;++i)
	{
		reString->append(base[i]);
	}
	reString->append(targetString);
}

void CharString::assign(CharString& targetString)
{
	if(size<targetString.getSize())
	{
		delete base;
		size=targetString.getSize();
		base=new char[size];
		num=size;
	}
	for(int i=0;i<num;++i)
	{
		append(targetString.getIndex(i));
	}
}

void CharString::append(char c)
{
	if(size==num)
	{
		char* newChar=new char[size+delta_size];
		for(int i=0;i<num;++i)
		{
			newChar[i]=base[i];
		}
		delete base;
		base=newChar;
	}
	base[num]=c;
	++num;
}

void CharString::append(char* c)
{
	int count=0;
	for(;c[count]!='\0';++count);
	if(num+count>size)
	{
		char* newChar=new char[num+count+delta_size];
		for(int i=0;i<num;++i)
		{
			newChar[i]=base[i];
		}
		delete base;
		base=newChar;
	}
	for(int i=num;i<num+count;++i)
	{
		base[i]=c[i-num];
	}
	num+=count;
}

void CharString::append(string& c)
{
	int count=c.length();
	if(num+count>size)
	{
		char* newChar=new char[num+count+delta_size];
		for(int i=0;i<num;++i)
		{
			newChar[i]=base[i];
		}
		delete base;
		base=newChar;
	}
	for(int i=num;i<num+count;++i)
	{
		base[i]=c[i-num];
	}
	num+=count;
}

void CharString::append(CharString& cs)
{
	int count=cs.getSize();
	if(num+count>size)
	{
		char* newChar=new char[num+count+delta_size];
		for(int i=0;i<num;++i)
		{
			newChar[i]=base[i];
		}
		delete base;
		base=newChar;
	}
	for(int i=num;i<num+count;++i)
	{
		base[i]=cs.getIndex(i-num);
	}
	num+=count;
}

char CharString::getIndex(int index)
{
	if(index>=num || index<0)
	{
		std::cerr<<"Out of range"<<std::endl;
		throw;
	}
	return base[index];
}

int CharString::getSize()
{
	return num;
}

int CharString::getCapability()
{
	return size;
}

void CharString::print(std::ostream& os)
{
	for(int i=0;i<num;++i)
	{
		os<<base[i];
	}
	os<<std::endl;
}

bool CharString::empty()
{
	if(num==0)
		return true;
	else
		return false;
}

void CharString::clear()
{
	num=0;
}