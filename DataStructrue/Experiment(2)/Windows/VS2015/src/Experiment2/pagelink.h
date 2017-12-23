#ifndef PAGELINK_H
#define PAGELINK_H

#include "CharString.h"
#include <iostream>
using namespace std;

class pageLink
{
public:
	pageLink();
	~pageLink(){}

private:
	int num;
	CharString url;
	CharString texts;
	CharString title;
	int id;

public:
	void setNum(int n);
	void setUrl(CharString &ur);
	void setTexts(CharString &te);
	void setTitle(CharString &ti);
	void setId(int i);

	int getNum();
	CharString getUrl();
	CharString getTexts();
	CharString getTitle();
	int getId();

};

#endif // PAGELINK_H
