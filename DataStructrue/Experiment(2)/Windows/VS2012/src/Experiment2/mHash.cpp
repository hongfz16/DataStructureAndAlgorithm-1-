#include "mHash.h"
mHash::mHash(vector<pageInfo>& pinfos)
{
	magicNum=1226959;//12255871;//9191891;
	dl=new vector<pair<CharString,docLink*> >[magicNum];
	for(int i=0;i<pinfos.size();++i)
	{
		insert(pinfos[i]);
	}
}

mHash::~mHash()
{
	delete []dl;
}

void mHash::insert(pageInfo& pinfo)
{
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
		int hashre=hashFunc(k);
		vector<pair<CharString,docLink*> >& hn=dl[hashre];
		pl.setNum(wordCount[j].second);
		int i=0;
		bool flag=false;
		for(i=0;i<hn.size();++i)
		{
			if(hn[i].first == k)
			{
				flag=true;
				break;
			}
		}
		if(flag)
		{
			hn[i].second->add(pl);
		}
		else
		{
			docLink* link=new docLink();
			link->add(pl);
			hn.push_back(pair<CharString,docLink*>(k,link));
		}
	}
}

long mHash::hashFunc(CharString& cs)
{
	string stdstr=cs.csToStdString();
	long re=0;
	long temp=1;
	for(int i=0;i<stdstr.size();++i)
	{
		long convert=(int)stdstr[i];
		if(convert<0)
			convert=-convert;
		re+=convert*temp%magicNum;
		temp=temp*191%magicNum;
	}
	return re%magicNum;
}

docLink* mHash::search(CharString& cs)
{
	int hashnum=hashFunc(cs);
	vector<pair<CharString,docLink*> >& hn=dl[hashnum];
	for(int i=0;i<hn.size();++i)
	{
		if(hn[i].first == cs)
			return (hn[i].second);
	}
	return nullptr;
}