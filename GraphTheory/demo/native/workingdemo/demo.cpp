#include <stdio.h>
#include <stdlib.h>
#include <iostream>
extern "C" {
#define EXPORT __attribute__((visibility("default")))
EXPORT
double Add(double a, double b) 
{ 
	return a+b;
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