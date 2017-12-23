/**
@brief �����ĵ���
@file inverteddocs.h
@author �鷽��
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef INVERTEDDOCS_H
#define INVERTEDDOCS_H

#include "mAVL.h"
#include "CharString.h"
#include "doclink.h"
#include "pageinfo.h"
#include "wordSegmentation.h"
#include "mHash.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class invertedDocs
{
public:
	invertedDocs();
	//����������Ϣ���쵹���ĵ�
	invertedDocs(vector<pageInfo>& pinfos,wordSegmentation* _dic);
	~invertedDocs();

private:
	//AVL��
	mAVL<CharString,docLink>* mtree;
	//��ϣ��
	mHash* mhash;
	//�ִ���
	wordSegmentation* dic;

public:
	//ʹ��AVL����key��Ӧ������
	docLink* Search(CharString key);
	//ʹ��Hash����key��Ӧ������
	docLink* hashSearch(CharString key);
	//����ĵ�
	void addDoc(pageInfo& pinfo);
	//��ȡ��ѯ��Ϣ
	vector<pair<int, int> > getResult(vector<CharString> queries,bool choose);
	//��ӡ��ѯ��Ϣ�������
	void printResult(vector<pair<int, int> > &re, ofstream &fout);
	//��������ѯ�������ѯ�ļ����ͽ����ŵ�ַ
	void batchSearch(string filename, string outputfilename,bool choose);
};

#endif // INVERTEDDOCS_H
