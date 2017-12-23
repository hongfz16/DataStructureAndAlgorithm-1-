/**
@brief 声明CharString字符串类
@file CharString.h
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#ifndef _CHARSTRING_H_
#define _CHARSTRING_H_

#include <iostream>
#include <string>
using std::string;

class CharString
{
public:

	/**********构造函数、析构函数**********/

	//默认构造函数，预留1000个位置
	CharString();
	
	//重载构造函数1，构造出包含一个给定字符的字符串
	CharString(char init);
	
	//重载构造函数2，构造出包含num个给定字符的字符串
	CharString(char init,int num);
	
	//重载构造函数3，使用string类型初始化
	CharString(string& init);
	
	//重载构造函数4，使用char*初始化
	CharString(char* init);
	
	
	//拷贝构造函数
	CharString(const CharString& cs);
	
	//析构函数，释放base指向的空间
	~CharString();

	/**********文档要求实现的函数**********/
	
	//返回从pos开始的第一个匹配targetString的位置的index（pos从0开始数，以下表示index的都是从0开始数）
	int indexOf(CharString& targetString,int pos);
	
	//返回从pos位置开始长度为len的字符串（包含第pos个）
	CharString subString(int pos,int len);

	//将targetString连接到本身之后，返回一个连接好的字符串的指针，这个操作并不会改变本身或者targetString
	CharString* concat(CharString& targetString);

	//赋值，将targetString赋值给this
	void assign(CharString& targetString);


	/**********其他函数**********/

	//将c加入到本字符串末尾
	void append(char c);

	//将c字符串接到本字符串末尾
	void append(char* c);

	//将string接到本字符串末尾
	void append(string& s);

	//将CharString字符串加到本字符串末尾
	void append(CharString& cs);

	//返回第index个字符
	char getIndex(int index) const;
	
	//返回字符串长度
	int getSize() const;

	//返回字符串预留长度
	int getCapability() const;
	
	//打印字符串
	void print(std::ostream& os);
	
	//如果字符串为空就返回true，不为空返回false
	bool empty();
	
	//清空字符串
	void clear();

	//如果两字符串相同返回true，否则返回false
	bool is_equal(CharString target) const;

	//上一个函数的string重载版本
	bool is_equal(string target);

	//重载标准输出流操作符
	friend std::ostream& operator<<(std::ostream& out,CharString& obj);
	
	//赋值函数
	CharString& operator=(const CharString& other);

	//重载相等运算符
	bool operator == (const CharString& other) const;

	//重载小于运算符
	bool operator < (const CharString& other) const;

	bool operator > (const CharString& other) const;

	//输出字符串
	void print_CharString(std::ostream& os);
	
	string csToStdString();

private:
	//未指定长度时的默认长度
	static int init_size;

	//每次需要扩展长度的时候增加的size
	static int delta_size;

	//预留的空间
	int size;
	
	//字符串长度
	int num;
	
	//指向字符串的指针
	char* base;

};

#endif
