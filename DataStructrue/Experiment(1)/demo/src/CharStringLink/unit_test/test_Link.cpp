#include "../Link.h"
#include <iostream>
using namespace std;

int main()
{
	Link<int> m_link;
	for(int i=0;i<10;++i)
	{
		m_link.add(i);
	}
	m_link.clear();

	if(m_link.empty())
		cout<<"Empty"<<endl;

	for(int i=10;i<20;++i)
	{
		m_link.add(i);
	}
	m_link.printLink(cout);

	m_link.remove(0);
	m_link.printLink(cout);

	Link<int>* p=m_link.getNext();
	m_link.remove(p);
	m_link.printLink(cout);

	int temp=17;
	Link<int>* q=m_link.search(temp);
	cout<<q->getElem()<<endl;

	temp=170;
	m_link.insert(q,temp);
	m_link.printLink(cout);

	for(int i=0;i<9;++i)
	{
		m_link.remove(0);
		m_link.printLink(cout);
	}

	cout<<m_link.getSize()<<endl;
	return 0;
}