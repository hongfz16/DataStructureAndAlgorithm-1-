#include"siglobal.h"
#include"unionfind.h"

namespace SI
{
	UnionFind::UnionFind(int tn) :fath(NULL)
	{
		resize(tn);
	}

	UnionFind::~UnionFind()
	{
		if (fath != NULL) delete[] fath;
	}
	
	void UnionFind::resize(int tn)
	{
		if (!tn) return;
		if (fath != NULL) delete[] fath;
		fath = new int[tn];
		for (int i = 0; i < tn; ++i)
			fath[i] = i;
	}

	int UnionFind::getfath(int u)
	{
		if (fath[u] != u) fath[u] = getfath(fath[u]);
		return fath[u];
	}

	void UnionFind::merge(int u, int v)
	{
		u = getfath(u);
		v = getfath(v);
		if (!(u ^ v)) return;
		fath[u] = v;
	}
}