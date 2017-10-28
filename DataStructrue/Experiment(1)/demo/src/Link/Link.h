#ifndef _LINK_H_
#define _LINK_H_

#include <iostream>

//双向循环链表模板，含有不存储任何信息的头结点
template<class T>
class Link
{
public:

	/**********构造函数与析构函数**********/
	
	//初始化操作，将prev和next指针指向自己
	Link();
	
	//析构函数，采用递归的方式释放空间
	~Link();

	/**********要求实现的函数**********/
	
	//向链表最后添加一个节点
	void add(T& elem);
	
	//将第index个节点删除
	T remove(int index);
	
	//将rm指向的节点删除
	T remove(Link* rm);
	
	//查找链表中是否有值等于target的节点，如果有就返回该节点指针，否则返回nullptr
	Link* search(T& target);

	/**********其他函数（只允许头结点调用）**********/
	
	//在pos节点之前插入一个节点，元素为elem
	void insert(Link* pos,T& elem);
	
	//返回第index个节点的指针
	Link* getNode(int index);
	
	//清空链表，释放多余空间
	void clear();
	
	//如果链表为空返回true，否则返回false
	bool empty();
	
	//返回链表长度
	int getSize();
	
	//打印链表
	void printLink(std::ostream& os);

	/**********其他函数（除了头结点之外的节点可以调用）**********/
	
	//返回当前节点存储的数据
	T getElem();
	
	//返回当前节点前一个节点的指针
	Link* getPrev();
	
	//返回当前节点后一个节点的指针
	Link* getNext();

private:

	//当前节点存储的信息
	T elem;
	
	//前一个节点的指针
	Link* prev;
	
	//后一个节点的指针
	Link* next;

};

template<class T>
Link<T>::Link()
{
	next=this;
	prev=this;	
}

template<class T>
Link<T>::~Link()
{
	if(prev==nullptr) return;
	prev->next=nullptr;
	delete next;
}

template<class T>
void Link<T>::insert(Link* pos,T& _elem)
{
	Link<T>* temp=pos->prev;
	Link<T>* p=new Link();
	p->prev=temp;
	p->next=pos;
	pos->prev=p;
	temp->next=p;
	p->elem=_elem;
}

template<class T>
void Link<T>::add(T& _elem)
{
	insert(this,_elem);
}

template<class T>
T Link<T>::remove(int index)
{
	Link<T>* p=getNode(index);
	return remove(p);
}

template<class T>
T Link<T>::remove(Link* p)
{
	if(p==this)
	{
		std::cerr<<"Can not delete head node"<<std::endl;
		throw;
	}
	Link<T>* pl=p->prev;
	Link<T>* pr=p->next;
	p->next=p;
	p->prev=p;
	T re=p->elem;
	delete p;
	pl->next=pr;
	pr->prev=pl;
	return re;
}

template<class T>
Link<T>* Link<T>::search(T& target)
{
	Link<T>* p=next;
	while(p!=this)
	{
		if(p->elem==target)
			return p;
		else
			p=p->next;
	}
	return nullptr;
}

template<class T>
Link<T>* Link<T>::getNode(int index)
{
	Link<T>* p=next;
	for(int i=0;i<index;++i)
	{
		p=p->next;
		if(p==this)
		{
			//p=p->next;
			std::cerr<<"Out of range!"<<std::endl;
			throw;
		}
	}
	return p;
}

template<class T>
void Link<T>::clear()
{
	if(next==this)
		return;
	Link<T>* n=next;
	Link<T>* p=prev;
	next=this;
	prev=this;
	n->prev=p;
	p->next=n;
	delete n;
}

template<class T>
bool Link<T>::empty()
{
	if(next==this)
		return true;
	else
		return false;
}

template<class T>
int Link<T>::getSize()
{
	Link<T>* p=next;
	int count=0;
	while(p!=this)
	{
		++count;
		p=p->next;
	}
	return count;
}

template<class T>
void Link<T>::printLink(std::ostream& os)
{
	if(next==this)
		return;
	Link<T>* p=next;
	while(p!=this->prev)
	{
		os<<p->getElem()<<" -> ";
		p=p->next;
	}
	os<<p->getElem()<<std::endl;
}

template<class T>
T Link<T>::getElem()
{
	return elem;
}

template<class T>
Link<T>* Link<T>::getPrev()
{
	return prev;
}

template<class T>
Link<T>* Link<T>::getNext()
{
	return next;
}

#endif