/**
@brief �����ĵ���
@file inverteddocs.h
@author �鷽��
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/

#ifndef INVERTEDDOCS_H
#define INVERTEDDOCS_H

#include "mAVL.h"
#include "CharString.h"
#include "doclink.h"
#include "pageinfo.h"
#include "wordSegmentation.h"
#include "mhash.h"
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
    //���ݴ����ҳ����Ϣ��������ʼ��
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
    //ʹ��AVL�������ؼ��ʣ������ĵ�����
	docLink* Search(CharString key);
    //ʹ�ù�ϣ�������������ĵ�����
	docLink* hashSearch(CharString key);
    //���ݴ���ҳ����Ϣ������뵹���ĵ�
	void addDoc(pageInfo& pinfo);
    //���ݴ���Ĳ�ѯ���������
	vector<pair<int, int> > getResult(vector<CharString> queries, bool useAVL);
    //�������ӡ���������
    void printResult(vector<pair<int, int> > &re, ofstream &fout);
    //���������������뱾�ز�ѯ�ļ����Լ�����ļ���
	void batchSearch(string filename, string outputfilename);
};

#endif // INVERTEDDOCS_H
