#ifndef VERTEXINFO_H
#define VERTEXINFO_H

#include"siglobal.h"

namespace SI
{
	class VertexInfo
	{
	public:
		VertexInfo();
		friend std::istream& operator >> (std::istream& in, VertexInfo& obj);
	};
}

#endif // !VERTEXINFO_H
