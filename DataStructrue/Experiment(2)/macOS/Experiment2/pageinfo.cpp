#include "pageinfo.h"

pageInfo::pageInfo()
{}

void pageInfo::setWordCount(Link<CharString> *link)
{
	Link<CharString>* p=link->getNext();
	while(p!=link)
	{
		bool flag=false;
		int i=0;
		for(i=0;i<wordCount.size();++i)
		{
			if(wordCount[i].first == p->getElem())
			{
				flag=true;
				break;
			}
		}
		if(flag)
		{
			wordCount[i].second++;
		}
		else
		{
			wordCount.push_back(pair<CharString,int>(p->getElem(),1));
		}
		p=p->getNext();
	}
}

void pageInfo::setTexts(CharString &te)
{
	texts=te;
}

void pageInfo::setTitle(CharString &ti)
{
	title=ti;
}

void pageInfo::setUrl(CharString &ur)
{
	url=ur;
}

void pageInfo::setId(int i)
{
	id=i;
}

vector<pair<CharString,int> >& pageInfo::getWordCount()
{
	return wordCount;
}

CharString pageInfo::getTexts()
{
	return texts;
}

CharString pageInfo::getTitle()
{
	return title;
}

CharString pageInfo::getUrl()
{
	return url;
}

int pageInfo::getId()
{
	return id;
}
