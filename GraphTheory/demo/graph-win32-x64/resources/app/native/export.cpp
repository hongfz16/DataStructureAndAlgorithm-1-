#if defined(_WIN32)
#define DllExport   __declspec(dllexport)
#else
#define DllExport
#endif

//#include
//#include "json.hpp"
//#include "GerwGraph.h"
//#include "Utility.h"
//#include <fstream>
//#include <iostream>
//#include "ConnectedComponent.h"
//using json = nlohmann::json;
//using namespace std;
#include"siglobal.h"
#include"sigraph.h"
#include"EdgeInfo.h"
#include"VertexInfo.h"

using SI::EdgeInfo;
using SI::VertexInfo;
using Edge = SI::EdgeNode<EdgeInfo>;
using Graph = SI::SIGraph<EdgeInfo, VertexInfo>;

extern "C" {

	DllExport Graph* createGraph_n(int n)
	{
		Graph* pG = new Graph(n);
		return pG;
	}

	DllExport void destroyGraph(Graph* pG)
	{
		if (pG != NULL) delete pG;
	}

	DllExport EdgeInfo* createEdgeInfo(int u = 0, int v = 0, int w = 0)
	{
		EdgeInfo* pE = new EdgeInfo(u, v, w);
		return pE;
	}

	DllExport void destroyEdgeInfo(EdgeInfo* pE)
	{
		if(pE!=NULL) delete pE;
	}

	DllExport Graph* createGraph_s(const char* s)
	{
		Graph* pG;
		std::ifstream fin;
		fin.open(s);
		int n, m, u, v;
		EdgeInfo ei;
		fin >> n;
		pG = new Graph(n);
		for (int i = 0; i < n; ++i)
			fin >> pG->V[i];
		for (fin >> m; m; --m)
		{
			fin >> ei;
			pG->addPath(ei);
		}
		return pG;
	}

	DllExport int dijkstraStep(Graph* pG, int stp, int u, int* dist, EdgeInfo* pE,EdgeInfo* pprev)
	{
		return pG->dijkstraStep(stp, u, dist, pE, pprev);
	}

	DllExport int dijkstra(Graph* pG, int u, int* dist, Graph* pSG = NULL)
	{
		return pG->dijkstra(u, dist, pSG);
	}

	/**
	@param [in] pG ptr_to_graph
	@param [in] u start_vertex
	@param [out] pSG ptr_to_MST
	@retval the tot length of edges in MST
	*/
	DllExport int prim(Graph* pG, int u, Graph* pSG = NULL)
	{
		return pG->prim(u, pSG);
	}

	/**
	@param [in] stp step
	@param [out] pE the_selected_edge_in_this_step
	*/
	DllExport int primStep(Graph* pG, int stp, int u, EdgeInfo* pE)
	{
		return pG->primStep(stp, u, pE);
	}

	/**
	@param [in] pG ptr_to_graph
	@param [out] pSG ptr_to_MST
	@retval S the tot length of edges in MST
	@retval -1 failed
	*/
	DllExport int kruskal(Graph* pG, Graph* pgraph = NULL)
	{
		return pG->Kruskal(pgraph);
	}

	/**
	@param[in] stp step
	@param[out] pE the_selected_edge_in_this_step
	@retval true success
	@retval false failed
	*/
	DllExport bool kruskalStep(Graph* pG, int stp, EdgeInfo* pE)
	{
		return pG->KruskalStep(stp, pE);
	}
	
	/**
	@param [in] pG ptr_to_graph
	@param [out] c the_ith_element_is_the_centerality_of_the_ith_vertex
	*/
	DllExport void betweennessCentrality(Graph* pG, int* c)
	{
		return pG->betweennessCentrality(c);
	}

	DllExport void connectivityInit(Graph* pG)
	{
		pG->connectivityInit();
	}

	DllExport bool connectivityQuery(Graph* pG, int u, int v, int ST)
	{
		return pG->connectivityQuery(u, v, ST);
	}

	DllExport int connectivityCount(Graph* pG, int ST)
	{
		return pG->connectivityCount(ST);
	}

	DllExport int connectivitySize(Graph* pG,int u, int ST)
	{
		return pG->connectivitySize(u, ST);
	}

	DllExport int connectivityRep(Graph* pG, int u, int ST)
	{
		return pG->connectivityRep(u, ST);
	}


	DllExport void closenesscentrality(Graph* pG, int *c)
	{
		pG->closenesscentrality(c);
	}
}