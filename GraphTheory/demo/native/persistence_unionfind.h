#ifndef PERSISTENCE_UNIONFIND_H
#define PERSISTENCE_UNIONFIND_H

#include "siglobal.h"
#include "persistencearry.h"

namespace SI
{
	class Persistence_UnionFind
	{
	private:
		PerArray<int> fath;
		PerArray<int> rank;
		PerArray<int> cnt;
	public:
		Persistence_UnionFind(int tn = 0, int tq = 0);
		void resize(int tn, int tq);
		int getfath(int x,int u);
		void merge(int u, int v);
		void resume(int k);
		int sizeq();
		int count(int k);
		~Persistence_UnionFind();
	};
}
#endif // !PERSISTENCE_UNIONFIND_H