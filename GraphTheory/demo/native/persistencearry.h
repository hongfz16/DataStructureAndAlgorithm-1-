#ifndef PERSISTENCEARRY_H
#define PERSISTENCEARRY_H

#include"siglobal.h"

namespace SI
{
	typedef std::pair<int, int> pii;

	template<class T>
	class ArrayNode
	{
	public:
		int ls, rs;
		T data;
		ArrayNode() :ls(0), rs(0)
		{

		}
	};

	template<class T>
	class PerArray
	{
		typedef ArrayNode<T> node;
	private:
		node* buffer;
		int bufSize;
		int NBuf;
		std::vector<pii> root;
		
	public:
		PerArray() :buffer(NULL), NBuf(0), bufSize(0)
		{
		}
		PerArray(int n, int q) :buffer(NULL), NBuf(0), bufSize(0)
		{
			allocBuffer(n, q);
		}
		void _allocBuffer(int size)
		{
			if (buffer != NULL) delete[] buffer;
			buffer = new node[size];
			bufSize = size;
		}
		void allocBuffer(int n, int q)
		{
			int logn = 0;
			while (n >> logn) ++logn;
			root.resize(q);
			root.clear();
			_allocBuffer(q * logn + n);
		}
		void clear()
		{
			memset(buffer, 0, bufSize * sizeof(node));
			bufSize = 0;
			NBuf = 0;
			root.clear();
		}
		void destroy()
		{
			if (buffer!=NULL) delete[] buffer;
			buffer = NULL;
			bufSize = NBuf = 0;
			root.resize(0);
			root.shrink_to_fit();
		}
		~PerArray()
		{
			destroy();
		}
		void init(T* c, int n)
		{
		
			NBuf = Max(n, 1);
			root.push_back(std::make_pair(1, NBuf));
			for (int i = 1; i <= n; ++i)
			{
				buffer[i].ls = (i << 1);
				buffer[i].rs = (i << 1) + 1;
				buffer[i].data = c[i - 1];
				if (buffer[i].ls > n) buffer[i].ls = buffer[i].rs = 0;
				else if (buffer[i].rs > n) buffer[i].rs = 0;
			}
		}
		int newNode()
		{
			++NBuf;
			if (NBuf > bufSize) return -1;
			return NBuf;
		}

	/*	bool modify_dfs(int oi, int p, int k)
		{
			int i = newNode();
			if (i == -1) return false;
			buffer[i] = buffer[oi];
			if (!k) return true;
			if ((p >> k) & 1)
			{
				buffer[i].rs = NBuf + 1;
				return modify_dfs(buffer[oi].rs, p, k - 1);
			}
			else
			{
				buffer[i].ls = NBuf + 1;
				return modify_dfs(buffer[oi].ls, p, k - 1);
			}
		}*/

		bool _modify(int oi, int p, int k, const T& tdata)
		{
			int i;
			while (true)
			{
				if ((i = newNode()) == -1) return false;

				buffer[i] = buffer[oi];
				if (!k) break;
				if ((p >> (k - 1)) & 1)
				{
					oi = buffer[oi].rs;
					buffer[i].rs = NBuf + 1; 
				}
				else
				{
					oi = buffer[oi].ls;
					buffer[i].ls = NBuf + 1;
				}
				--k;
			}
			buffer[i].data = tdata;
			return true;
			/*int i = newNode();
			if (i == -1) return false;
			buffer[i] = buffer[oi];
			if (!k) return true;
			if ((p >> k) & 1)
			{
				buffer[i].rs = NBuf + 1;
				return modify_dfs(buffer[oi].rs, p, k - 1);
			}
			else
			{
				buffer[i].ls = NBuf + 1;
				return modify_dfs(buffer[oi].ls, p, k - 1);
			}*/

		}


		bool modify(int p, const T& tdata)
		{
			int k = 0;
			for (++p; p >> k; ++k);
			root.push_back(std::make_pair(NBuf + 1, NBuf + k));
			//modify_dfs(root[root.size() - 2], p, k - 1);
			return _modify(root[root.size() - 2].first, p, k - 1, tdata);
		}

		const T& at(int x, int p)
		{
			int k = 0;
			for (++p; p >> k; ++k);
			--k;
			int i = root[x].first;
			while (k)
			{
				if ((p >> (k - 1)) & 1) i = buffer[i].rs;
				else i = buffer[i].ls;
				--k;
			}
			return buffer[i].data;
		}

		void resume(int k)
		{
			++k;
			while (root.size() > k) root.pop_back();
			NBuf = root[k - 1].second;
		}

		void nopmodify()
		{
			root.push_back(root[root.size() - 1]);
		}

		int sizeq()
		{
			return root.size();
		}
	};
}
#endif // !PERSISTENCEARRY_H