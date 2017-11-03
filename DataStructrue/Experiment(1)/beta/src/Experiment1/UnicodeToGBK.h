#ifndef _UNICODETOGBK_H_
#define _UNICODETOGBK_H_

#include <map>
using std::map;

class UnicodeToGBK
{
public:
	UnicodeToGBK();
	~UnicodeToGBK();

	wchar_t* convert(char* unicode,int length);
	int* convert_int(char* unicode,int length);
	int* convert_single(int uni);

private:
	map<int,int> uni2gbk;
};

#endif