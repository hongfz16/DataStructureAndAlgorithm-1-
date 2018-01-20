#include "persistence_unionfind.h"

namespace SI
{
	Persistence_UnionFind::Persistence_UnionFind(int tn, int tq) :fath(tn, tq), rank(tn, tq), cnt(1, tq)
	{
		int *temp = new int[tn];
		for (int i = 0; i < tn; ++i)
			temp[i] = i;
		fath.init(temp, tn);
		for (int i = 0; i < tn; ++i)
			temp[i] = 1;
		rank.init(temp, tn);
		temp[0] = tn;
		cnt.init(temp, 1);
	}

	int Persistence_UnionFind::count(int k)
	{
		return cnt.at(k, 0);
	}

	void Persistence_UnionFind::resize(int tn, int tq)
	{
		fath.destroy();
		fath.allocBuffer(tn, tq);
		rank.destroy();
		rank.allocBuffer(tn, tq);
		cnt.destroy();
		cnt.allocBuffer(1, tq);
	}

	int Persistence_UnionFind::getfath(int x, int u)
	{
		int fa;
		while ((fa = fath.at(x, u)) != u) 
			u = fa;
		return fa;
	}

	void Persistence_UnionFind::merge(int u, int v)
	{
		int lastm = fath.sizeq() - 1;
		u = getfath(lastm, u);
		v = getfath(lastm, v);
		if (!(u^v))
		{
			fath.nopmodify();
			rank.nopmodify();
			cnt.nopmodify();
			return;
		}
		int rku = rank.at(lastm, u);
		int rkv = rank.at(lastm, v);
		if (rku >= rkv)
		{
			fath.modify(v, u);
			if (!(rku^rkv))
				rank.modify(u, rku + 1);
			else rank.nopmodify();
		}
		else
		{
			fath.modify(u, v);
			rank.nopmodify();
		}
		cnt.modify(0, cnt.at(cnt.sizeq() - 1, 0) - 1);
	}

	void Persistence_UnionFind::resume(int k)
	{
		fath.resume(k);
		rank.resume(k);
		cnt.resume(k);
	}

	Persistence_UnionFind::~Persistence_UnionFind()
	{

	}

	int Persistence_UnionFind::sizeq()
	{
		return fath.sizeq();
	}
}