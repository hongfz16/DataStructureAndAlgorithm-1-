#include "EdgeInfo.h"

namespace SI
{
	EdgeInfo::EdgeInfo(int ts, int te, int tw) :u(ts), v(te), w(tw)
	{

	}
	int EdgeInfo::length() const
	{
		return w;
	}
	int EdgeInfo::start() const
	{
		return u;
	}
	int EdgeInfo::end() const
	{
		return v;
	}
	std::istream& operator >> (std::istream& in, EdgeInfo& obj)
	{
		in >> obj.u >> obj.v >> obj.w;
		return in;
	}
}