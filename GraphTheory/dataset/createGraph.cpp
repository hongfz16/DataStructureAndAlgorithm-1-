#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

typedef unordered_map<string,int> String2Int;

class user
{
public:
	user(string _username,int _id):username(_username),id(_id){}
	~user(){}

	string username;
	int id;
	vector<int> seenfilms;
};

class film
{
public:
	film(string _filmname,int _id,float _rate,int _type):filmname(_filmname),id(_id),rate(_rate),type(_type){}
	~film(){}

	string filmname;
	int id;
	float rate;
	int type;
	vector<int> seenusers;
};

class csvFile
{
public:
	csvFile(string filename)
	{
		ifstream fin(filename);
		string line,seg;
		while(getline(fin,line))
		{
			if(line.empty())
				continue;
			vector<string> vecline;
			seg.clear();
			for(int i=0;i<line.size();++i)
			{
				if(line[i]!=',') seg+=line[i];
				else
				{
					vecline.push_back(seg);
					seg.clear();
				}
			}
			vecline.push_back(seg);
			csv.push_back(vecline);
		}
		fin.close();
	}
	~csvFile(){}

	vector<vector<string> > csv;
};

void getFilmMap(String2Int& filmmap,String2Int& typemap,vector<film>& filmlist,string filename)
{
	csvFile filmfile(filename);
	int typecount=0;
	int filmcount=0;
	string type,name,strrate;
	for(int i=0;i<filmfile.csv.size();++i)
	{
		type=filmfile.csv[i][0];
		if(typemap.find(type)==typemap.end())
			typemap[type]=(typecount++);
		name=filmfile.csv[i][1];
		if(filmmap.find(name)!=filmmap.end())
		{
			continue;
		}
		strrate=filmfile.csv[i][2];
		float rate=atof(strrate.c_str());
		filmlist.push_back(film(name,filmcount,rate,typemap[type]));
		filmmap[name]=filmcount;
		++filmcount;
	}
}

void getUserInfo(String2Int& usermap,vector<user>& userlist,String2Int& filmmap,vector<film>& filmlist,string filename)
{
	csvFile userfile(filename);
	int usercount=0;
	string filmname,username;
	for(int i=0;i<userfile.csv.size();++i)
	{
		filmname=userfile.csv[i][0];
		int filmid=0;
		auto filmit=filmmap.find(filmname);
		if(filmit!=filmmap.end())
			filmid=filmit->second;
		else
			continue;
		username=userfile.csv[i][1];
		if(usermap.find(username)==usermap.end())
		{
			usermap[username]=usercount;
			userlist.push_back(user(username,usercount));
			++usercount;
		}
		userlist[usermap[username]].seenfilms.push_back(filmid);
		filmlist[filmid].seenusers.push_back(usermap[username]);
	}
}

void createUserGraph(vector<user>& userlist,string filename,string jsonfilename)
{
	ofstream fout(filename);
	fout<<userlist.size()<<" "<<"#####"<<endl;
	ofstream jsonfout(jsonfilename);
	jsonfout<<"{"<<endl<<"	\"nodes\": ["<<endl;
	int vcount=0;
	for(int i=0;i<userlist.size();++i)
	{
		jsonfout<<"{\"id\":\""<<i<<"\", \"name\": \""<<userlist[i].username<<"\", \"group\":"<<1<<"}";
		if(i!=userlist.size()-1)
			jsonfout<<","<<endl;
		else
			jsonfout<<endl<<"],"<<endl<<"\"links\": ["<<endl;
		sort(userlist[i].seenfilms.begin(),userlist[i].seenfilms.end());
	}
	for(int i=0;i<userlist.size();++i)
	{
		cout<<i<<endl;
		for(int j=i+1;j<userlist.size();++j)
		{
			int samecount=0;
			vector<int>& ilist=userlist[i].seenfilms;
			vector<int>& jlist=userlist[j].seenfilms;
			int ii=0,jj=0;
			while(ii<ilist.size()&&jj<jlist.size())
			{
				if(ilist[ii]==jlist[jj])
				{
					++samecount;
					++ii;
					++jj;
				}
				else if(ilist[ii]<jlist[jj])
					++ii;
				else
					++jj;
			}
			if(samecount>15)
			{
				if(vcount!=0)
					jsonfout<<","<<endl;
				fout<<i<<" "<<j<<" "<<samecount<<endl;
				jsonfout<<"{\"source\": \""<<i<<"\", \"target\": \""<<j<<"\", \"value\": "<<samecount<<"}";
				++vcount;
			}
		}
		//if(i>2000) break;
	}
	jsonfout<<endl<<"	]"<<endl<<"}"<<endl;
	jsonfout.close();
	fout.seekp(0,ios::beg);
	fout<<userlist.size()<<" "<<vcount<<endl;
	fout.close();
}

void createFilmGraph(vector<film>& filmlist,string filename,string jsonfilename)
{
	ofstream fout(filename);
	fout<<filmlist.size()<<" "<<"#####"<<endl;
	ofstream jsonfout(jsonfilename);
	jsonfout<<"{"<<endl<<"	\"nodes\": ["<<endl;
	int vcount=0;
	for(int i=0;i<filmlist.size();++i)
	{
		jsonfout<<"{\"id\":\""<<i<<"\", \"name\": \""<<filmlist[i].filmname<<"\", \"group\":"<<1<<"}";
		if(i!=filmlist.size()-1)
			jsonfout<<","<<endl;
		else
			jsonfout<<endl<<"],"<<endl<<"\"links\": ["<<endl;
		sort(filmlist[i].seenusers.begin(),filmlist[i].seenusers.end());
	}
	for(int i=0;i<filmlist.size();++i)
	{
		cout<<i<<endl;
		for(int j=i+1;j<filmlist.size();++j)
		{
			int samecount=0;
			vector<int>& ilist=filmlist[i].seenusers;
			vector<int>& jlist=filmlist[j].seenusers;
			int ii=0,jj=0;
			while(ii<ilist.size()&&jj<jlist.size())
			{
				if(ilist[ii]==jlist[jj])
				{
					++samecount;
					++ii;
					++jj;
				}
				else if(ilist[ii]<jlist[jj])
					++ii;
				else
					++jj;
			}
			if(samecount>0)
			{
				if(vcount!=0)
					jsonfout<<","<<endl;
				fout<<i<<" "<<j<<" "<<samecount<<endl;
				jsonfout<<"{\"source\": \""<<i<<"\", \"target\": \""<<j<<"\", \"value\": "<<samecount<<"}";
				++vcount;
			}
		}
		//if(i>2000) break;
	}
	jsonfout<<endl<<"	]"<<endl<<"}"<<endl;
	jsonfout.close();
	fout.seekp(0,ios::beg);
	fout<<filmlist.size()<<" "<<vcount<<endl;
	fout.close();
}

int main()
{
	String2Int filmmap,typemap,usermap;
	vector<film> filmlist;
	vector<user> userlist;
	string moviefilename="movie.csv";
	string userfilename="user.csv";
	string outfilename="usergraph.txt";
	string jsonfilename="usergraph.json";
	string filmfilename="filmgraph.txt";
	string jsonfilmfilename="filmgraph.json";
	getFilmMap(filmmap,typemap,filmlist,moviefilename);
	getUserInfo(usermap,userlist,filmmap,filmlist,userfilename);
	//createUserGraph(userlist,outfilename,jsonfilename);
	createFilmGraph(filmlist,filmfilename,jsonfilmfilename);
	return 0;
}