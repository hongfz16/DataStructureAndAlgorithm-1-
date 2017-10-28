#ifndef _CHARSTRING_H_
#define _CHARSTRING_H_

#include <string>
using std::string;

class CharString
{
public:
	CharString();
	CharString(char init);
	CharString(char init,int num);
	CharString(string& init);
	CharString(char* init);
	~CharString();

	int indexOf(CharString& targetString,int pos);
	CharString* subString(int pos,int len);
	CharString* concat(CharString& targetString);
	void assign(CharString& targetString);

	void append(char c);
	void append(char* c);
	void append(string& s);
	void append(CharString& cs);
	char getIndex(int index);
	int getSize();
	int getCapability();
	void print(std::ostream& os);
	bool empty();
	void clear();

private:
	static int init_size;
	static int delta_size;
	int size; //capability
	int num; //length
	char* base;

};

#endif