#ifndef SIGRAPH_H
#define SIGRAPH_H

#include "siglobal.h"
#include "unionfind.h"
#include "persistence_unionfind.h"

using std::cout;
using std::endl;

#define mp(a,b) make_pair(a,b)

namespace SI
{
	using std::priority_queue;
	using std::pair;
	using std::vector;
	using PUF = Persistence_UnionFind;
	template<class EdgeInfo>
	class EdgeNode
	{
	public:
		EdgeInfo* pdata;
		EdgeNode* next;

		EdgeNode() :pdata(NULL), next(NULL)
		{

		}
		EdgeNode(EdgeNode* tnext, const EdgeInfo& tdata) :next(tnext)
		{
			pdata = new EdgeInfo(tdata);
		}

		int start()
		{
			return pdata->start();
		}

		int end()
		{
			return pdata->end();
		}
	};

	template<class T>
	class Greater
	{
	public:
		bool operator()(const T& a, const T& b)
		{
			return a > b;
		}
	};

	template<class EdgeInfo, class VertexInfo>
	class SIGraph
	{
		typedef EdgeNode<EdgeInfo> edge;
		typedef VertexInfo vertex;
		typedef pair<int, int> pii;
		//private:
	public:
		static const int INF = 1 << 29;

		int n, m;
		int sz;
		EdgeNode<EdgeInfo>** Elast;
		VertexInfo* V;
		PUF* puf;
		int* wl;
	public:
		SIGraph(int tn = 0) :sz(tn), n(tn), m(0), Elast(NULL), V(NULL), wl(NULL), puf(NULL)
		{
			if (!n) return;
			_allocBuffer();
		}
		void _allocBuffer()
		{
			if (Elast == NULL) Elast = new edge*[n];
			std::memset(Elast, 0, n * sizeof(edge*));
			if (V == NULL) V = new VertexInfo[n];
		}
		void setVertexInfo(int u, const VertexInfo& tvi)
		{
			V[u] = tvi;
		}
		void delList(edge* edgeListNode)
		{
			if (edgeListNode == NULL) return;
			delList(edgeListNode->next);
			delete edgeListNode;
		}
		void clear()
		{
			for (int i = 0; i < n; ++i)
			{
				delList(Elast[i]);
				Elast[i] = NULL;
			}
			delete[] V;
		}
		void destroy()
		{
			for (int i = 0; i < n; ++i)
				delList(Elast[i]);
			delete[] Elast;
			for (int i = 0; i < n; ++i)
				delete V[i];
			delete[] V;
			if (puf != NULL) delete puf;
			if (wl != NULL) delete[] wl;
			Elast = V = NULL;
			puf = wl = NULL;
			n = m = sz = 0;
		}
		void appendSize(int nn)
		{
			edge** nlast = new edge*[nn];
			std::memcpy(nlast, Elast, n * sizeof(edge*));
			std::memset(nlast + n, 0, (nn - n) * sizeof(edge*));
			delete[] Elast;
			Elast = nlast;
			vertex** nV = new vertex*[nn];
			memcpy(nV, V, n * sizeof(vertex*));
			memset(nV + n, 0, (nn - n) * sizeof(vertex*));
			delete[] V;
			V = nV;
			n = sz = nn;
		}
		void addPath(const EdgeInfo& ei)
		{
			//	cout << ei.start() << endl;
			edge* ne = new edge(Elast[ei.start()], ei);
			Elast[ei.start()] = ne;
			++m;
		}
		void delPath(int u, int v)
		{
			//		if (n == 0)return;
			edge* pp = NULL;
			edge* np = NULL;
			for (np = Elast[u]; np && np->end() != v; np = np->next) pp = np;
			if (np == NULL) return;
			if (pp == NULL) Elast[u] = np->next;
			else pp->next = np->next;
			delete np;
			--m;
		}
		//No out_of_range test
		int dijkstra(int u, int* dist, SIGraph* pgraph = NULL)
		{
			static priority_queue<pii, vector<pii>, Greater<pii> > q;
			int v, w;
			int pu = u;
			edge** prev = new edge*[n];
			while (!q.empty()) q.pop();
			for (int i = 0; i < n; ++i) dist[i] = INF;
			dist[u] = 0;
			q.push(std::make_pair(0, u));
			for (int i = 1; i < n; ++i)
			{
				while (!q.empty() && dist[q.top().second] != q.top().first)
					q.pop();
				if (q.empty()) return -1;
				u = q.top().second;
				q.pop();
				for (edge* p = Elast[u]; p != NULL; p = p->next)
					if (dist[v = p->end()] >(w = (dist[u] + p->pdata->length())))
					{
						q.push(std::make_pair((dist[v] = w), v));
						prev[v] = p;
					}
			}
			if (pgraph != NULL)
			{
				pgraph->clear();
				for (u = 0; u < n; ++u)
					if (u^pu)
						pgraph->addPath(*(prev[u]->pdata));//(prev[u]->start, u, *(prev[u]->pdata));
			}
			delete[] prev;
			return 0;
		}

		int dijkstraStep(int stp, int u, int* dist, EdgeInfo* selEdge = NULL, EdgeInfo* rprev = NULL)
		{
			static priority_queue<pii, vector<pii>, Greater<pii> > q;
			static EdgeInfo** prev = NULL;
			int v, w, rtn;
			static int pu;
			if (stp == 0)
			{
				if (prev != NULL)
				{
					delete[] prev;
				}
				prev = new EdgeInfo*[n];
				while (!q.empty()) q.pop();
				for (int i = 0; i < n; ++i) dist[i] = INF;
				if (rprev != NULL)
					for (int i = 0; i < n; ++i)
						rprev[i].setInfo(-1, -1, -1);
				dist[pu = u] = 0;
				q.push(std::make_pair(0, u));
			}

			while (!q.empty() && dist[q.top().second] != q.top().first)
				q.pop();
			if (q.empty()) return -1;
			u = q.top().second;
			if (selEdge != NULL && (pu^u)) *selEdge = *prev[u];
			if (rprev != NULL && (pu^u)) rprev[u] = *prev[u];
			rtn = dist[u];
			q.pop();
			for (edge* p = Elast[u]; p != NULL; p = p->next)
				if (dist[v = p->end()] > (w = (dist[u] + p->pdata->length())))
				{
					q.push(std::make_pair((dist[v] = w), v));
					prev[v] = p->pdata;
				}
			return rtn;
		}

		int prim(int u, SIGraph* pgraph = NULL)
		{
			static priority_queue<pii, vector<pii>, Greater<pii> > q;
			int v, w;
			int pu = u;
			int rtn = 0;
			int* dist = new int[n];
			char* used = new char[n];
			edge** prev = new edge*[n];
			while (!q.empty()) q.pop();
			for (int i = 0; i < n; ++i) dist[i] = INF, used[i] = 0;
			dist[u] = 0;
			q.push(std::make_pair(0, u));
			for (int i = 0; i < n; ++i)
			{
				while (!q.empty() && used[q.top().second]) q.pop();
				if (q.empty()) return -1;
				used[u = q.top().second] = 1;
				rtn += q.top().first;
				q.pop();
				for (edge* p = Elast[u]; p != NULL; p = p->next)
					if (!used[v = p->end()] && dist[v] >(w = p->pdata->length()))
					{
						q.push(std::make_pair((dist[v] = w), v));
						prev[v] = p;
					}
			}
			if (pgraph != NULL)
			{
				pgraph->clear();
				for (u = 0; u < n; ++u)
					if (u^pu)
						pgraph->addPath(*(prev[u]->pdata));
			}
			delete[] dist;
			delete[] used;
			delete[] prev;
			return rtn;
		}

		int primStep(int stp, int u, EdgeInfo* selEdge = NULL)
		{
			static priority_queue<pii, vector<pii>, Greater<pii> > q;
			int v, w;
			static int pu; //= u;
			static int rtn; //= 0;
			static int* dist = NULL; //= new int[n];
			static char* used = NULL; //= new char[n];
			static EdgeInfo** prev = NULL; //= new edge*[n];
			if (!stp)
			{
				pu = u;
				rtn = 0;
				if (dist != NULL) delete[] dist;
				if (used != NULL) delete[] used;
				if (prev != NULL) delete[] prev;
				dist = new int[n];
				used = new char[n];
				prev = new EdgeInfo*[n];
				while (!q.empty()) q.pop();
				for (int i = 0; i < n; ++i) dist[i] = INF, used[i] = 0;
				dist[u] = 0;
				q.push(std::make_pair(0, u));
			}

			while (!q.empty() && used[q.top().second]) q.pop();
			if (q.empty()) return -1;
			used[u = q.top().second] = 1;
			rtn += q.top().first;
			q.pop();
			if (selEdge != NULL && (u^pu)) *selEdge = *prev[u];
			for (edge* p = Elast[u]; p != NULL; p = p->next)
				if (!used[v = p->end()] && dist[v] > (w = p->pdata->length()))
				{
					q.push(std::make_pair((dist[v] = w), v));
					prev[v] = p->pdata;
				}
			return rtn;

		}

		static bool cmp_EdgeInfoStar_w_smaller(EdgeInfo* pa, EdgeInfo* pb)
		{
			return pa->w < pb->w;
		}

		int Kruskal(SIGraph* pgraph = NULL)
		{
			int rtn = 0;
			int totE = 0;
			int k = 0;
			int u, v;
			UnionFind* UF = new UnionFind(n);
			EdgeInfo** edges = new EdgeInfo*[m];
			for (int u = 0; u < n; ++u)
				for (edge*p = Elast[u]; p != NULL; p = p->next)
					edges[totE++] = p->pdata;
			std::sort(edges, edges + totE, cmp_EdgeInfoStar_w_smaller);

			for (int i = 1; i < n; ++i)
			{
				while (k < totE && (UF->getfath(u = (edges[k]->u)) == UF->getfath(v = edges[k]->v)))
					++k;
				if (!(k^totE)) break;
				rtn += edges[k]->w;
				if (pgraph != NULL) pgraph->addPath(*(edges[i]));
				UF->merge(u, v);
			}
			delete[] edges;
			delete UF;
			if (!(k^totE)) rtn = -1;
			return rtn;
		}

		bool KruskalStep(int stp, EdgeInfo* selEdge, int ST)
		{
			static int totE;// = 0;
			static int k;// = 0;
			int u, v;
			static UnionFind* UF = NULL; //new UnionFind(n);
			static EdgeInfo** edges = NULL;// = new EdgeInfo*[m];

			if (!stp)
			{
				if (UF != NULL) delete UF;
				if (edges != NULL) delete[] edges;
				totE = 0;
				k = 0;
				UF = new UnionFind(n);
				edges = new EdgeInfo*[m];
				for (int u = 0; u < n; ++u)
					for (edge*p = Elast[u]; p != NULL; p = p->next)
						if (p->pdata->length() >= ST) edges[totE++] = p->pdata;
				std::sort(edges, edges + totE, cmp_EdgeInfoStar_w_smaller);
			}


			while (k < totE && (UF->getfath(u = (edges[k]->u)) == UF->getfath(v = edges[k]->v)))
				++k;
			if (!(k^totE)) return false;
			*selEdge = *edges[k];
			UF->merge(u, v);
			return true;
		}

		/*	bool cmp_rk(int i, int j)
		{
		return wl[i] > wl[j];
		}*/

		void QSort_rk(int* a, int l, int r, int *w)
		{
			if (l >= r) return;
			int t = a[l];
			int i = l, j = r;
			while (i < j)
			{
				while (i < j && w[a[j]] <= w[t]) --j;
				a[i] = a[j];
				while (i < j&&w[a[i]] >= w[t]) ++i;
				a[j] = a[i];
			}
			a[i] = t;
			QSort_rk(a, l, i - 1, w);
			QSort_rk(a, i + 1, r, w);
		}

		static bool cmp_greater(int a, int b)
		{
			return a > b;
		}

		void connectivityInit()
		{
			puf = new PUF(n, m);

			/*	for (int i = 0; i < n; ++i)
			cout << puf->getfath(puf->sizeq() - 1, i) << " ";*/

			wl = new  int[m + 1];
			int* rk = new int[m + 1];
			int* st = new int[m + 1];
			int* ed = new int[m + 1];
			int totE = 0;
			for (int u = 0; u<n; ++u)
				for (edge* p = Elast[u]; p != NULL; p = p->next)
				{
					st[++totE] = p->pdata->start();
					ed[totE] = p->pdata->end();
					wl[totE] = p->pdata->length();
					rk[totE] = totE;
				}
			//std::sort(rk + 1, rk + 1 + m, &SIGraph::cmp_rk);
			QSort_rk(rk, 1, m, wl);

			for (int i = 1; i <= totE; ++i)
			{
				puf->merge(st[rk[i]], ed[rk[i]]);
				//for (int u = 0; u < n; ++u)
				//	cout << puf->getfath(puf->sizeq() - 1, u) << " ";
				//cout << endl;
			}
			std::sort(wl + 1, wl + 1 + m, cmp_greater);
			delete[] rk;
			delete[] st;
			delete[] ed;
		}

		bool connectivityQuery(int u, int v, int ST)
		{
			int k = std::upper_bound(wl + 1, wl + 1 + m, ST, cmp_greater) - wl - 1;
			return puf->getfath(k, u) == puf->getfath(k, v);
		}

		int connectivityCount(int ST)
		{
			int k = std::upper_bound(wl + 1, wl + 1 + m, ST, cmp_greater) - wl - 1;
			return puf->count(k);
		}

		int connectivitySize(int u, int ST)
		{
			int k = std::upper_bound(wl + 1, wl + 1 + m, ST, cmp_greater) - wl - 1;
			return puf->getsize(k, u);
		}

		int connectivityRep(int u, int ST)
		{
			int k = std::upper_bound(wl + 1, wl + 1 + m, ST, cmp_greater) - wl - 1;
			return puf->getfath(k, u);
		}

		void closenesscentrality(int* c)
		{
			int* dist = new int[n];
			for (int u = 0; u < n; ++u)
			{
				dijkstra(u, dist);
				c[u] = 0;
				for (int i = 0; i < u; ++i)
					c[u] += dist[i];
			}
			delete[] dist;
		}

		void _calcSigmas(int* dist, int *id, int *temp)
		{
			int u, v;
			memset(temp, 0, n * sizeof(int));
			QSort_rk(id, 0, n - 1, dist);
			for (int i = 0; i < n; ++i)
			{
				//if (!(i^src)) continue;
				for (edge* p = Elast[u = id[i]]; p != NULL; p = p->next)
				{
					if (dist[u] + p->pdata->length() == dist[v = p->pdata->end()])
						temp[u] += temp[p->pdata->end()] + 1;
				}
			}
		}

		void betweennessCentralityImproved(int* c)
		{
			int *dist = new int[n];
			int *temp = new int[n];
			int *id = new int[n];
			memset(c, 0, n * sizeof(int));
			for (int u = 0; u < n; ++u) id[u] = u;
			for (int u = 0; u < n; ++u)
			{
				dijkstra(u, dist);
				_calcSigmas(dist, id, temp);
				for (int i = 0; i < n; ++i) c[i] += temp[i];
			}
			delete[] dist;
			delete[] temp;
			delete[] id;
		}

		void betweennessCentrality(int* c)
		{
			int** d;
			d = new int*[n];
			for (int i = 0; i < n; ++i)
				d[i] = new int[n];
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j) d[i][j] = INF;
			for (int i = 0; i < n; ++i) d[i][i] = 0;
			for (int u = 0; u < n; ++u)
				for (edge* p = Elast[u]; p != NULL; p = p->next)
					d[u][p->end()] = p->pdata->length();
			for (int k = 0; k < n; ++k)
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < n; ++j)
						d[i][j] = Min(d[i][j], d[i][k] + d[k][j]);
			for (int i = 0; i < n; ++i)
				for (int k = 0; k < n; ++k)
					for (int j = 0; j < n; ++j)
						c[k] += !(d[i][j] ^ (d[i][k] + d[k][j]));
			for (int i = 0; i < n; ++i)
				delete d[i];
			delete d;
		}

		void exportGraph(int u, int ST, SIGraph* pgraph)
		{
			int* Q = new int[n + 1];
			char* used = new char[n];
			int head = 0, tail = 0;
			int v;
			memset(used, 0, n * sizeof(char));
			pgraph->clear();
			Q[tail++] = u;
			used[u] = 1;
			while (head^tail)
			{
				u = Q[head++];
				for (edge* p = Elast[u]; p != NULL; p = p->next)
				{
					if (p->pdata->length() < ST) continue;
					pgraph->addPath(*(p->pdata));
					if (!used[v = p->pdata->end()])
					{
						Q[tail++] = v;
						used[v] = 1;
					}
				}
			}
			sz = tail;
			delete[] Q;
			delete[] used;
		}

		void printGraph()
		{
			cout << sz << " " << m << endl;
			for (int u = 0; u<n; ++u)
				for (edge* p = Elast[u]; p != NULL; p = p->next)
				{
					cout << p->pdata->start() << " " << p->pdata->end() << " " << p->pdata->length() << endl;
				}
		}

		int getEdges(EdgeInfo* edges, int ST)
		{
			int NN = 0;
			for (int u = 0; u<n; ++u)
				for (edge* p = Elast[u]; p != NULL; p = p->next)
				{
					if (p->pdata->length() < ST || p->pdata->end() <= u) continue;
					edges[NN++] = *(p->pdata);
				}
			return NN;
		}
	};

}

#endif // !SIGRAPH_H
