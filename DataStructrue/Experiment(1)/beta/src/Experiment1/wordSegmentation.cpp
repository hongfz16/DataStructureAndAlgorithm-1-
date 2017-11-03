#include "wordSegmentation.h"

wordSegmentation::wordSegmentation(string filename,string super_filename)
{
	ifstream fin(filename);
	string temp;
	int count=0;
	while(!fin.eof())
	{
		count++;
		temp.clear();
		fin>>temp;
		CharString cs(temp); 
		dic.insert(cs);
	}
	//cout<<count<<endl;
	fin.close();
	ifstream sfin(super_filename);
	count=0;
	while(!sfin.eof())
	{
		count++;
		temp.clear();
		sfin>>temp;
		CharString cs(temp);
		super_dic.insert(cs);
	}
	//cout<<count<<endl;
	sfin.close();
	//cout<<"load complete"<<endl;
}

wordSegmentation::~wordSegmentation(){}

Link<CharString>* wordSegmentation::max_back_segment(CharString& incstring,int max)
{
	/*
	ifstream fin("xiaowa");
	string tempxiaowa;
	fin>>tempxiaowa;
	CharString xiaowacs(tempxiaowa);
	cout<<xiaowacs.getSize()<<endl;
	if(super_dic.find(xiaowacs)!=super_dic.end())
		cout<<"found"<<endl;
	else
		cout<<"can not find xiaowa"<<endl;
	*/
	/*
	for(int i=0;i<incstring.getSize();++i)
	{
		int itemp=incstring.getIndex(i);
		cout<<itemp<<endl;
	}
	CharString subxiaowa=incstring.subString(8,4);
	ofstream fout("super_dic");
	
	for(auto it=super_dic.begin();it!=super_dic.end();++it)
	{
		CharString temp=(*it);
		if(temp.is_equal(subxiaowa))
			cout<<"yes!"<<endl;
		else
			cout<<"no"<<endl;
		fout<<temp<<endl;
		fout<<"size:"<<temp.getSize()<<endl;
		for(int i=0;i<temp.getSize();++i)
		{
			int itemp=(int)temp.getIndex(i);
			fout<<itemp<<endl;
		}
	}
	*/
	Link<CharString>* relink=new Link<CharString>();
	int pos=incstring.getSize()-1;
	//cout<<pos<<endl;
	//incstring.getIndex(pos);
	//cout<<"test range"<<endl;
	for(int i=pos;i>=0;--i)
	{
		if(incstring.getIndex(i)==' ')
		{
			continue;
		}
		if(incstring.getIndex(i)==0)
		{
			CharString recs;
			--i;
			while(i>=0 && incstring.getIndex(i)!=0)
			{
				recs.append(incstring.getIndex(i));
				--i;
			}
			CharString reverse;
			for(int ii=recs.getSize()-1;ii>=0;--ii)
			{
				reverse.append(recs.getIndex(ii));
			}
			//cout<<reverse<<endl;
			if(relink->empty())
				relink->add(reverse);
			else
				relink->insert(relink->getNode(0),reverse);
			continue;
		}
		/*
		if(incstring.getIndex(i)>0 && incstring.getIndex(i)<=127)
		{
			CharString recs;
			while(i>=0 && incstring.getIndex(i)>=0 && incstring.getIndex(i)<=127)
			{
				//cout<<i<<endl;
				recs.append(incstring.getIndex(i));
				--i;
			}
			++i;
			CharString reverse;
			for(int ii=recs.getSize()-1;ii>=0;--ii)
			{
				reverse.append(recs.getIndex(ii));
			}
			cout<<reverse<<endl;
			if(relink->empty())
				relink->add(reverse);
			else
				relink->insert(relink->getNode(0),reverse);
			continue;
		}
		*/
		int length=0;
		if(i-max*2+1>=0)
			length=max;
		else
			length=(i-1)/2+1;
		for(;length>=1;--length)
		{
			CharString sub=incstring.subString(i-length*2+1,length*2);
			if(super_dic.find(sub)!=super_dic.end())
			{
				if(relink->empty())
					relink->add(sub);
				else
					relink->insert(relink->getNode(0),sub);
				//cout<<sub<<endl;
				i=i-length*2+1;
				break;
			}
			if(length==1 || dic.find(sub)!=dic.end())
			{
				/*
				if(length==1)
					cout<<"length==1"<<endl;
				*/
				if(relink->empty())
					relink->add(sub);
				else
					relink->insert(relink->getNode(0),sub);
				//cout<<sub<<endl;
				i=i-length*2+1;
				break;
			}
		}
	}
	return relink;
}