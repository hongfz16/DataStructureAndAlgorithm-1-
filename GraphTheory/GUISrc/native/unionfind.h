#ifndef UNIONFIND_H
#define UNIONFIND_H

#include"siglobal.h"

namespace SI
{
	class UnionFind
	{
	private:
		int *fath;
	public:
		UnionFind(int tn = 0);
		void resize(int tn);
		int getfath(int u);
		void merge(int u, int v);
		~UnionFind();
	};

}
#endif // !UNIONFIND_H