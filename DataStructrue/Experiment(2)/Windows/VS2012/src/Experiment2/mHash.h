/**
@brief ��ϣ����
@file mHash.h
@author �鷽��
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef _MHASH_H_
#define _MHASH_H_

#include <iostream>
#include <string>
#include <vector>
#include "CharString.h"
#include "doclink.h"
#include "pageinfo.h"
#include "wordSegmentation.h"

class mHash
{
public:
	//���ݴ������ӵ���Ϣ�����ϣ��
	mHash(vector<pageInfo>& pinfo);
	~mHash();

private:
	//�����ͻʹ��vector
	vector<pair<CharString,docLink*> >* dl;
	//������
	long magicNum;
	//��ϣ����
	long hashFunc(CharString& cs);

public:
	//����ڵ�
	void insert(pageInfo& pi);
	//�����ĵ�
	docLink* search(CharString& cs);

};

#endif