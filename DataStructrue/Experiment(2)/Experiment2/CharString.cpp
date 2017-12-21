/**
@brief CharString字符串类成员函数定义
@file CharString.cpp
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#include <iostream>
#include "CharString.h"

int CharString::init_size=1000;

int CharString::delta_size=10;

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

CharString::CharString(const CharString& cs)
{
	int _num=cs.getSize();
	base=new char[_num];
	num=_num;
	size=_num;
	for(int i=0;i<num;++i)
	{
		base[i]=cs.getIndex(i);
	}
}

CharString::~CharString()
{
	if(base!=NULL)
	{
		delete[] base;
		base=NULL;
	}
}

int CharString::indexOf(CharString& targetString,int pos)
{
	if(pos<0 || pos>=num)
	{
		std::cerr<<"Out of range!"<<std::endl;
		throw;
	}
	//get next[]
	int targetSize=targetString.getSize();
	int* next=new int[targetSize+1];
	next[0]=-1;
	int j=0,k=-1;
	while(j<targetSize)
	{
		if(k==-1 || targetString.getIndex(j)==targetString.getIndex(k))
		{
			++j;
			++k;
			next[j]=k;
		}
		else
			k=next[k];
	}
	j=1;
	while(j<targetSize)
	{
		k=next[j];
		if(targetString.getIndex(j)==targetString.getIndex(k))
		{
			next[j]=next[k];
		}
		++j;
	}
	int i=pos;
	j=0;
	while(i<num && j<targetSize)
	{
		if(j==-1 || getIndex(i)==targetString.getIndex(j))
		{
			++i;
			++j;
		}
		else
		{
			j=next[j];
		}
	}
	delete[] next;
	if(j>=targetSize)
		return i-targetSize;
	else
		return -1;
}

CharString CharString::subString(int pos,int len)
{
	if(pos+len>num || pos<0 || len<0)
	{
		std::cerr<<"Out of range"<<std::endl;
		throw;
	}
	CharString reString;
	for(int i=0;i<len;++i)
	{
		reString.append(base[pos+i]);
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
	return reString;
}

void CharString::assign(CharString& targetString)
{
	if(size<targetString.getSize())
	{
		delete[] base;
		size=targetString.getSize();
		base=new char[size];
		num=0;
	}
	for(int i=0;i<targetString.getSize();++i)
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
		delete[] base;
		base=newChar;
		size=size+delta_size;
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
		delete[] base;
		base=newChar;
		size=num+count+delta_size;
	}
	for(int i=num;i<num+count;++i)
	{
		base[i]=c[i-num];
	}
	num+=count;
}

void CharString::append(string& c)
{
	int count=static_cast<int>(c.length());
	if(num+count>size)
	{
		char* newChar=new char[num+count+delta_size];
		for(int i=0;i<num;++i)
		{
			newChar[i]=base[i];
		}
		delete[] base;
		base=newChar;
		size=num+count+delta_size;
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
		delete[] base;
		base=newChar;
		size=num+count+delta_size;
	}
	for(int i=num;i<num+count;++i)
	{
		base[i]=cs.getIndex(i-num);
	}
	num+=count;
}

char CharString::getIndex(int index) const
{
	if(index>=num || index<0)
	{
		std::cerr<<"Out of range"<<std::endl;
		throw;
	}
	return base[index];
}

int CharString::getSize() const
{
	return num;
}

int CharString::getCapability() const
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

bool CharString::is_equal(CharString target) const
{
	if(num!=target.getSize())
		return false;
	for(int i=0;i<num;++i)
	{
		if(base[i]!=target.getIndex(i))
			return false;
	}
	return true;
}

bool CharString::is_equal(string target)
{
	if(num!=target.length())
		return false;
	for(int i=0;i<num;++i)
	{
		if(base[i]!=target[i])
			return false;
	}
	return true;
}

CharString &CharString::operator=(const CharString &other) { 
	if(this==&other)
		return *this;
	if(base!=NULL)
	{
		delete[] base;
	}
	int m_size=other.getSize();
	base=new char[m_size];
	size=m_size;
	num=m_size;
	for(int i=0;i<size;++i)
	{
		base[i]=other.getIndex(i);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out,CharString& obj)
{
	for(int i=0;i<obj.getSize();++i)
	{
		if(obj.base[i]==(char)0)
			continue;
		out<<obj.base[i];
	}
	return out;
}

bool CharString::operator == (const CharString& other) const
{
	if(is_equal(other))
		return true;
	else
		return false;
}

bool CharString::operator < (const CharString& other) const
{
	int i_min=num;
	if(other.num<i_min)
		i_min=other.num;
	for(int i=0;i<i_min;++i)
		if(base[i]<other.base[i]) return true;
		else if(base[i]>other.base[i]) return false;
	return num<other.num;
}

bool CharString::operator >(const CharString &other) const
{
	if(other < *this)
		return true;
	else
		return false;
}

void CharString::print_CharString(std::ostream& os)
{
	os<<(*this);
}
