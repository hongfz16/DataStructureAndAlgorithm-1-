/**
@brief �ĵ�������
@file doclink.h
@author �鷽��
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef DOCLINK_H
#define DOCLINK_H

#include "Link.h"
#include "pagelink.h"
#include "CharString.h"

class docLink
{
public:
	docLink();
	~docLink(){}

private:
	//��װ��ʵ������ģ��
	Link<pageLink> link;
	//����ID
	int wordID;
	//�ĵ�����
	int DF;
	//���ʳ�����Ŀ
	int Occur;

public:
	//��ȡ����
	Link<pageLink> *getLink();
	//��ӽڵ�
	void add(pageLink& pl);
	//����ID��Ӧ�Ľڵ�
	Link<pageLink> *search(int id);
	//�༭ID��Ӧ�Ľڵ�
	void edit(int id,pageLink& pl);
	//ɾ��ID��Ӧ�Ľڵ�
	void remove(int id);
	//����ID
	void setID(int id);
	//��ȡ����
	int getID();
	int getDF();
	int getOccur();
};

#endif // DOCLINK_H
