/**
@brief �ĵ�������
@file doclink.h
@author �鷽��
@email hongfz16@163.com
@version 2.0
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
    //��װ��ʵ������ģ����
	Link<pageLink> link;
    //��ǰ�ĵ������Ӧ�ĵ���ID
	int wordID;
    //�ĵ���Ŀ
	int DF;
    //�õ������ĵ��г��ִ���
	int Occur;

public:
    //��ȡ�ĵ�����
	Link<pageLink> *getLink();
    //����ĵ�����ڵ�
    void add(pageLink& pl);
    //��������ID��Ӧ�Ľڵ�
    Link<pageLink> *search(int id);
    //�޸Ķ�Ӧ����ID�ڵ����Ϣ
	void edit(int id,pageLink& pl);
    //ɾ����Ӧ����
	void remove(int id);
    //���õ���ID
	void setID(int id);
    //��ȡ����ID
	int getID();
    //��ȡ�ĵ���Ŀ
	int getDF();
    //��ȡ���ʳ����ܴ���
	int getOccur();
};

#endif // DOCLINK_H
