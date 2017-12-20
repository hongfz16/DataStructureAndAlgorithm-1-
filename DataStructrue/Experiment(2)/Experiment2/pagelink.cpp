#include "pagelink.h"

pageLink::pageLink()
{

}

void pageLink::setNum(int n)
{
	num=n;
}

void pageLink::setUrl(CharString &ur)
{
	url=ur;
}

void pageLink::setTexts(CharString &te)
{
	texts=te;
}

void pageLink::setTitle(CharString &ti)
{
	title=ti;
}

void pageLink::setId(int i)
{
	id=i;
}

int pageLink::getNum()
{
	return num;
}

CharString pageLink::getUrl()
{
	return url;
}

CharString pageLink::getTexts()
{
	return texts;
}

CharString pageLink::getTitle()
{
	return title;
}

int pageLink::getId()
{
	return id;
}
