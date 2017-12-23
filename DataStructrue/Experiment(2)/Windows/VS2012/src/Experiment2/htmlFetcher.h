/**
@brief 通过url获取html文件的函数声明
@file htmlFetcher.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

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

//参数为url字符串，文件指针，获取的网页直接写入文件中
void fetchHTML(TCHAR* url,FILE* tarFile);
void urlopen(TCHAR* url, FILE* tarFile);


#endif //HTML_FETCHER_H