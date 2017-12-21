#include "doclink.h"

docLink::docLink()
{
	DF=0;
	Occur=0;
}

Link<pageLink>* docLink::getLink()
{
	return &link;
}

void docLink::add(pageLink &pl)
{
	Link<pageLink>* p=link.getNext();
	while(p!=&link)
	{
		if(p->getElem().getNum()<pl.getNum())
		{
			break;
		}
		p=p->getNext();
	}
	link.insert(p,pl);

	++DF;
	Occur+=pl.getNum();
}

Link<pageLink> *docLink::search(int id)
{
	Link<pageLink>* p=link.getNext();
	while(p!=&link)
	{
		if(p->getElem().getId()==id)
			return p;
		p=p->getNext();
	}
	return nullptr;
}

void docLink::edit(int id, pageLink &pl)
{
	Link<pageLink>* p=search(id);
	if(p)
	{
		p->getElem().setId(pl.getId());
		CharString te=pl.getTexts();
		CharString ti=pl.getTitle();
		CharString ur=pl.getUrl();
		p->getElem().setTexts(te);
		p->getElem().setTitle(ti);
		p->getElem().setUrl(ur);
	}
}

void docLink::remove(int id)
{
	Link<pageLink>* p=search(id);
	if(p)
	{
		link.remove(p);
	}
}

int docLink::getID()
{
	return wordID;
}

int docLink::getDF()
{
	return DF;
}

int docLink::getOccur()
{
	return Occur;
}
