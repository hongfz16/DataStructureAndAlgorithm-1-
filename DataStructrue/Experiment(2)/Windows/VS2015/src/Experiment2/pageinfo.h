#ifndef PAGEINFO_H
#define PAGEINFO_H

#include <vector>
#include <iostream>
#include "CharString.h"
#include "Link.h"

using namespace std;

class pageInfo
{
public:
	pageInfo();
	~pageInfo(){}

private:
	vector<pair<CharString,int> > wordCount;
	CharString texts;
	CharString title;
	CharString url;
	int id;

public:
	void setWordCount(Link<CharString> *link);
	void setTexts(CharString &te);
	void setTitle(CharString &ti);
	void setUrl(CharString &ur);
	void setId(int i);

	vector<pair<CharString,int> >& getWordCount();
	CharString getTexts();
	CharString getTitle();
	CharString getUrl();
	int getId();
};

#endif // PAGEINFO_H
