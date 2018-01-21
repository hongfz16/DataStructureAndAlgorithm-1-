#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream> 
#include <string>
#include <unistd.h>
using namespace std;
extern "C" {
#define EXPORT __attribute__((visibility("default")))
EXPORT
double Add(double a, double b,char* buffer)
{ 
	// std::ofstream fout("hererer");
	// fout<<"hello asshole"<<std::endl;
	// ifstream fin("./filmgraph.json");
	// if(fin.is_open())
	// 	return 0;
	// else
	// 	return -1;
	int maxfilename=100;
	getcwd(buffer,maxfilename);
	return 0;
}
void testPtr(int* intptr,int a)
{
	*intptr=a;
}
struct structtest
{
	int inttest;
	char* stringtest;
};
void teststruct(struct structtest* st)
{
	st->inttest=999;
	//st->stringtest=(char*)malloc(10*sizeof(char));
	int i=0;
	for(i=0;i<9;++i)
	{
		(st->stringtest)[i]='a';
	}
	//(st->stringtest)[9]='\0';
}
}