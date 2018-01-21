#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include <fstream>

using namespace std;

const int MAXN = 1000;
const int MAXM = 5000;
const int MAXW = 20000;
const int MAXT = 10;
int n, m;

int u, v, w;

int T;

inline int getrand()
{
	return rand();//(rand() << 16) + rand();
}
int main()
{
	ofstream fout("random.txt");
	ofstream jsonfout("jsonrandom.json");
	srand((unsigned)time(NULL));
	for (T = 1 /*getrand()*/ % MAXT; T; --T)
	{
		fout << (n = getrand() % MAXN + 1) << " ";
		fout << (m = (n + getrand() % MAXM)) << endl;
		jsonfout<<"{"<<endl<<"	\"nodes\": ["<<endl;
		for(int i=0;i<n;++i)
		{
			if(i!=0)
				jsonfout<<","<<endl;
			jsonfout<<"		{\"id\": \""<<i<<"\", \"group\":  "<<1<<"}";
		}
		jsonfout<<endl<<"],"<<endl<<"\"links\": ["<<endl;
		for (int i = 1; i < n; ++i)
		{
			u = getrand() % i;
			w = getrand() % MAXW;
			fout << u << " " << i << " " << w << endl;
			jsonfout<<"		{\"source\": \""<<u<<"\", \"target\": \""<<i<<"\", \"value\":"<<w<<"},"<<endl;
		}
		for (int i = n; i <= m; ++i)
		{
			if(i!=n)
				jsonfout<<","<<endl;
			u = getrand() % n + 1;
			v = getrand() % n + 1;
			w = getrand() % MAXW + 1;
			fout << u-1 << " " << v-1 << " " << w << endl;
			jsonfout<<"		{\"source\": \""<<u-1<<"\", \"target\": \""<<v-1<<"\", \"value\":"<<w<<"}";
		}
		jsonfout<<endl<<"	]"<<"}"<<endl;
	}
	//cout << endl << 0 << endl;
	return 0;
}