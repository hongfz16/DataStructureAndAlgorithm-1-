#ifndef EDGEINFO_H
#define EDGEINFO_H

#include "siglobal.h"

namespace SI
{
	class EdgeInfo
	{
	public:
		int u;
		int v;
		int w;
		EdgeInfo(int ts = -1, int te = -1, int tw = 0);
		int length() const;
		int start() const;
		int end() const;
		friend std::istream& operator >> (std::istream& in, EdgeInfo& obj);
	};
}
#endif // !EDGEINFO_H
