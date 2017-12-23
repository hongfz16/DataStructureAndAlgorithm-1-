#ifndef INVERTEDDOCS_H
#define INVERTEDDOCS_H

#include "mAVL.h"
#include "CharString.h"
#include "doclink.h"
#include "pageinfo.h"
#include "wordSegmentation.h"
#include "mhash.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class invertedDocs
{
public:
	invertedDocs();
	invertedDocs(vector<pageInfo>& pinfos,wordSegmentation* _dic);
	~invertedDocs();

private:
	mAVL<CharString,docLink>* mtree;
	mHash* mhash;
	wordSegmentation* dic;

public:
	docLink* Search(CharString key);
	docLink* hashSearch(CharString key);
	void addDoc(pageInfo& pinfo);
	vector<pair<int, int> > getResult(vector<CharString> queries, bool useAVL);
	void printResult(vector<pair<int, int> > &re, ofstream &fout);

	void batchSearch(string filename, string outputfilename);
};

#endif // INVERTEDDOCS_H
