#include "../CharString.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	/*
	CharString testcs('a');
	testcs.print(cout);
	CharString testcs1('a',10);
	testcs1.print(cout);
	CharString testcs2("asdfasdfasdf");
	testcs2.print(cout);
	char* a={"asdfasdfa\0"};
	CharString testcs3(a);
	testcs3.print(cout);
	CharString cs;
	string test="abcdefghij";
	for(int i=0;i<10;++i)
	{
		cs.append(test);
	}
	cs.print(cout);
	//(cs.subString(10,20))->print(cout);
	CharString css;
	css.assign(cs);
	css.print(cout);
	cs.append(css);
	cs.print(cout);
	*/
	CharString testcs("1234798798234782345asdfasdfqw345234345");
	if(1)
	{
		CharString* test=new CharString("asdfasdf");
		cout<<*test<<endl;
		delete test;
	}
	cout<<"here"<<endl;
	//CharString target("aaabaaaa");
	//cout<<testcs.indexOf(target,0)<<endl;
	//cout<<testcopy<<endl;
	return 0;
}