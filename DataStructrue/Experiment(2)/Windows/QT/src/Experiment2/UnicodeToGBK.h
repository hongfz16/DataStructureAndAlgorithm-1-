/**
@brief 将Unicode转化为GBK编码的类的声明
@file UnicodeToGBK.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#ifndef _UNICODETOGBK_H_
#define _UNICODETOGBK_H_

#include <map>
using std::map;

class UnicodeToGBK
{
public:
	//默认构造函数，读取UnicodeToGBK.csv文件，初始化Unicode与gbk的对应map
	UnicodeToGBK();
	
	//析构函数，释放空间
	~UnicodeToGBK();
	
	//传入的字符串格式为"&#xxxxx;..."，返回值为每个中文字对应的两个窄字符的取值
	int* convert_int(char* unicode,int length);
	
	//传入的为unicode编码，返回值为该编码的中文字对应的两个窄字符的取值
	int* convert_single(int uni);

private:
	//从unicode转为gbk的对应表
	map<int,int> uni2gbk;
};

#endif
