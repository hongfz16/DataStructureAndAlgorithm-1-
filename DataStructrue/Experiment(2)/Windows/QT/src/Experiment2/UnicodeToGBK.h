/**
@brief ��Unicodeת��ΪGBK������������
@file UnicodeToGBK.h
@author �鷽��
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
	//Ĭ�Ϲ��캯������ȡUnicodeToGBK.csv�ļ�����ʼ��Unicode��gbk�Ķ�Ӧmap
	UnicodeToGBK();
	
	//�����������ͷſռ�
	~UnicodeToGBK();
	
	//������ַ�����ʽΪ"&#xxxxx;..."������ֵΪÿ�������ֶ�Ӧ������խ�ַ���ȡֵ
	int* convert_int(char* unicode,int length);
	
	//�����Ϊunicode���룬����ֵΪ�ñ���������ֶ�Ӧ������խ�ַ���ȡֵ
	int* convert_single(int uni);

private:
	//��unicodeתΪgbk�Ķ�Ӧ��
	map<int,int> uni2gbk;
};

#endif
