/**
@brief ����CharString�ַ�����
@file CharString.h
@author �鷽��
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

	/**********���캯������������**********/

	//Ĭ�Ϲ��캯����Ԥ��1000��λ��
	CharString();
	
	//���ع��캯��1�����������һ�������ַ����ַ���
	CharString(char init);
	
	//���ع��캯��2�����������num�������ַ����ַ���
	CharString(char init,int num);
	
	//���ع��캯��3��ʹ��string���ͳ�ʼ��
	CharString(string& init);
	
	//���ع��캯��4��ʹ��char*��ʼ��
	CharString(char* init);
	
	
	//�������캯��
	CharString(const CharString& cs);
	
	//�����������ͷ�baseָ��Ŀռ�
	~CharString();

	/**********�ĵ�Ҫ��ʵ�ֵĺ���**********/
	
	//���ش�pos��ʼ�ĵ�һ��ƥ��targetString��λ�õ�index��pos��0��ʼ�������±�ʾindex�Ķ��Ǵ�0��ʼ����
	int indexOf(CharString& targetString,int pos);
	
	//���ش�posλ�ÿ�ʼ����Ϊlen���ַ�����������pos����
	CharString subString(int pos,int len);

	//��targetString���ӵ�����֮�󣬷���һ�����Ӻõ��ַ�����ָ�룬�������������ı䱾�����targetString
	CharString* concat(CharString& targetString);

	//��ֵ����targetString��ֵ��this
	void assign(CharString& targetString);


	/**********��������**********/

	//��c���뵽���ַ���ĩβ
	void append(char c);

	//��c�ַ����ӵ����ַ���ĩβ
	void append(char* c);

	//��string�ӵ����ַ���ĩβ
	void append(string& s);

	//��CharString�ַ����ӵ����ַ���ĩβ
	void append(CharString& cs);

	//���ص�index���ַ�
	char getIndex(int index) const;
	
	//�����ַ�������
	int getSize() const;

	//�����ַ���Ԥ������
	int getCapability() const;
	
	//��ӡ�ַ���
	void print(std::ostream& os);
	
	//����ַ���Ϊ�վͷ���true����Ϊ�շ���false
	bool empty();
	
	//����ַ���
	void clear();

	//������ַ�����ͬ����true�����򷵻�false
	bool is_equal(CharString target) const;

	//��һ��������string���ذ汾
	bool is_equal(string target);

	//���ر�׼�����������
	friend std::ostream& operator<<(std::ostream& out,CharString& obj);
	
	//��ֵ����
	CharString& operator=(const CharString& other);

	//������������
	bool operator == (const CharString& other) const;

	//����С�������
	bool operator < (const CharString& other) const;

	bool operator > (const CharString& other) const;

	//����ַ���
	void print_CharString(std::ostream& os);

    //ת��ΪSTL�ַ���
	string csToStdString();

private:
	//δָ������ʱ��Ĭ�ϳ���
	static int init_size;

	//ÿ����Ҫ��չ���ȵ�ʱ�����ӵ�size
	static int delta_size;

	//Ԥ���Ŀռ�
	int size;
	
	//�ַ�������
	int num;
	
	//ָ���ַ�����ָ��
	char* base;

};

#endif
