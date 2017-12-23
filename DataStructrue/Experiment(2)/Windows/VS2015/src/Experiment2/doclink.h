#ifndef DOCLINK_H
#define DOCLINK_H

#include "Link.h"
#include "pagelink.h"
#include "CharString.h"

class docLink
{
public:
	docLink();
	~docLink(){}

private:
	Link<pageLink> link;
	int wordID;
	int DF;
	int Occur;

public:
	Link<pageLink> *getLink();
	void add(pageLink& pl);
	Link<pageLink> *search(int id);
	void edit(int id,pageLink& pl);
	void remove(int id);

	void setID(int id);

	int getID();
	int getDF();
	int getOccur();
};

#endif // DOCLINK_H
