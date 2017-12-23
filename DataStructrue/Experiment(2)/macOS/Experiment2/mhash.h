#ifndef _MHASH_H_
#define _MHASH_H_

#include <iostream>
#include <string>
#include <vector>
#include "CharString.h"
#include "doclink.h"
#include "pageinfo.h"
#include "wordSegmentation.h"

class mHash
{
public:
	mHash(vector<pageInfo>& pinfo);
	~mHash();

private:
	vector<pair<CharString,docLink*> >* dl;
	long magicNum;
	long hashFunc(CharString& cs);

public:
	void insert(pageInfo& pi);
	docLink* search(CharString& cs);

};

#endif
