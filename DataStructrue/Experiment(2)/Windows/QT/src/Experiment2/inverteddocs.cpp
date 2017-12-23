/**
@brief 倒排文档类定义
@file inverteddocs.cpp
@author 洪方舟
@email hongfz16@163.com
@version 2.0
@date 2017.12.23
*/
#include "inverteddocs.h"

invertedDocs::invertedDocs()
{
	mtree = new mAVL<CharString,docLink>();
}

invertedDocs::invertedDocs(vector<pageInfo> &pinfos, wordSegmentation *_dic)
{
	dic=_dic;
	mtree = new mAVL<CharString,docLink>();
	bool taller=false;
	bool success=false;
	for(int i=0;i<pinfos.size();++i)
	{
		vector<pair<CharString,int> >& wordCount=pinfos[i].getWordCount();
		CharString texts=pinfos[i].getTexts();
		CharString title=pinfos[i].getTitle();
		CharString url=pinfos[i].getUrl();
		int id=pinfos[i].getId();
		pageLink pl;
		pl.setUrl(url);
		pl.setTexts(texts);
		pl.setTitle(title);
		pl.setId(id);
		for(int j=0;j<wordCount.size();++j)
		{
			CharString k=wordCount[j].first;
			mAVL<CharString,docLink> *tn=Insert(mtree,k,taller,success);
			pl.setNum(wordCount[j].second);
			docLink& link=tn->editData();
			link.add(pl);
		}
	}
	mhash=new mHash(pinfos);
}

invertedDocs::~invertedDocs()
{
	delete mtree;
}

docLink* invertedDocs::Search(CharString key)
{
	mAVL<CharString,docLink>* reavl=mtree->Search(key);
	if(reavl)
		return &(reavl->editData());
	else
		return nullptr;
}

docLink* invertedDocs::hashSearch(CharString key)
{
	docLink* re=mhash->search(key);
	return re;
}

void invertedDocs::addDoc(pageInfo &pinfo)
{
	bool taller=false;
	bool success=false;
	vector<pair<CharString,int> >& wordCount=pinfo.getWordCount();
	CharString texts=pinfo.getTexts();
	CharString title=pinfo.getTitle();
	CharString url=pinfo.getUrl();
	int id=pinfo.getId();
	pageLink pl;
	pl.setUrl(url);
	pl.setTexts(texts);
	pl.setTitle(title);
	pl.setId(id);
	for(int j=0;j<wordCount.size();++j)
	{
		CharString k=wordCount[j].first;
		mAVL<CharString,docLink> *tn=Insert(mtree,k,taller,success);
		pl.setNum(wordCount[j].second);
		docLink& link=tn->editData();
		link.add(pl);
	}
}

bool comp(const pair<pair<int,int>,int>& le,const pair<pair<int,int>,int>& ri)
{
	if(le.second==ri.second)
	{
		return le.first.second < ri.first.second;
	}
	return le.second < ri.second;
}

vector<pair<int,int> > invertedDocs::getResult(vector<CharString> queries,bool useAVL)
{
	vector<pair<int,int> > re;
	vector<pair<pair<int,int>,int> > pagecount; //id wordcount pagecount
	for(int i=0;i<queries.size();++i)
	{
		CharString query=queries[i];

		CharString newinfo2;
		for(int i=0;i<query.getSize();)
		{
			if(i<query.getSize() && (query.getIndex(i)>127 || query.getIndex(i)<0))
						{
							newinfo2.append(query.getIndex(i));
							newinfo2.append(query.getIndex(i+1));
							i+=2;
							while(i<query.getSize() && (query.getIndex(i)>127 || query.getIndex(i)<0))
							{
								newinfo2.append(query.getIndex(i));
								newinfo2.append(query.getIndex(i+1));
								i+=2;
							}
						}
						if(i<query.getSize() && query.getIndex(i)<=127 && query.getIndex(i)>0)
						{
							newinfo2.append((char)0);
							newinfo2.append(query.getIndex(i));
							++i;
							while(i<query.getSize() && query.getIndex(i)<=127 && query.getIndex(i)>0)
							{
								newinfo2.append(query.getIndex(i));
								++i;
							}
							newinfo2.append((char)0);
						}
		}
		query=newinfo2;

		Link<CharString>* seg=dic->divideWords(query,8);
		Link<CharString>* p=seg->getNext();
		while(p!=seg)
		{
			CharString cs=p->getElem();
			docLink* sre;
			if(useAVL)
				sre=Search(cs);
			else
				sre=hashSearch(cs);
			if(sre==nullptr)
			{
				p=p->getNext();
				continue;
			}
			Link<pageLink>* lpl=sre->getLink();
			Link<pageLink>* pp=lpl->getNext();
			while(pp!=lpl)
			{
				bool found=false;
				int j=0;
				for(j=0;j<pagecount.size();++j)
				{
					if(pagecount[j].first.first==pp->getElem().getId())
					{
						found=true;
						break;
					}
				}
				if(found)
				{
					pagecount[j].second++;
					pagecount[j].first.second+=pp->getElem().getNum();
				}
				else
				{
					pair<pair<int,int>,int> npair;
					npair.first=pair<int,int>(pp->getElem().getId(),pp->getElem().getNum());
					npair.second=1;
					pagecount.push_back(npair);
				}
				pp=pp->getNext();
			}
			p=p->getNext();
		}
	}
	sort(pagecount.begin(),pagecount.end(),comp);
	for(int i=0;i<pagecount.size();++i)
	{
		re.push_back(pagecount[i].first);
	}
	return re;
}

void invertedDocs::printResult(vector<pair<int,int> > &re,ofstream& fout)
{
	for(int i=re.size()-1;i>=0;--i)
	{
		fout<<"("<<re[i].first<<","<<re[i].second<<")"<<" ";
	}
	fout<<endl;
}

void invertedDocs::batchSearch(string inputfilename,string outputfilename)
{
	ifstream fin(inputfilename);
	ofstream fout(outputfilename);
	string line;
	while(getline(fin,line))
	{
		vector<CharString> queries;
		for(int i=0;i<line.length();++i)
		{
			CharString cs;
			while(i<line.length() && line[i]!=' ')
			{
				cs.append(line[i]);
				++i;
			}
			queries.push_back(cs);
		}
		vector<pair<int,int> > re=getResult(queries,true);
		printResult(re,fout);
	}
}
