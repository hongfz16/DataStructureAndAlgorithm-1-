#ifndef HTML_FETCHER_H
#define HTML_FETCHER_H

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <windows.h>
#include <wininet.h>
#include <locale.h>  

#define MAXSIZE 1024
#pragma comment(lib, "Wininet.lib") 


void fetchHTML(TCHAR* url,FILE* tarFile);
void urlopen(TCHAR* url, FILE* tarFile);


#endif //HTML_FETCHER_H