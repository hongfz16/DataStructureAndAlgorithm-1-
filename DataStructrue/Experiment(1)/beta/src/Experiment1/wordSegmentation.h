#ifndef _WORD_SEGMENTATION_
#define _WORD_SEGMENTATION_

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include "CharString.h"
#include "Link.h"

using namespace std;

class wordSegmentation
{
public:
	wordSegmentation(string filename,string super_filename);
	~wordSegmentation();

	Link<CharString>* max_back_segment(CharString& incstring,int max);
private:
	set<CharString> dic;
	set<CharString> super_dic;
};

#endif