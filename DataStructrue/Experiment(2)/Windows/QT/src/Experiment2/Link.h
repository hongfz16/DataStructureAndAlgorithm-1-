/**
@brief ����ģ���������붨��
@file Link.h
@author �鷽��
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#ifndef _LINK_H_
#define _LINK_H_

#include <iostream>
#include "CharString.h"

//˫��ѭ������ģ�壬���в��洢�κ���Ϣ��ͷ���
template<class T>
class Link
{
public:

	/**********���캯������������**********/
	
	//��ʼ����������prev��nextָ��ָ���Լ�
	Link();
	
	//�������������õݹ�ķ�ʽ�ͷſռ�
	~Link();

	/**********Ҫ��ʵ�ֵĺ���**********/
	
	//������������һ���ڵ�
	void add(T& elem);
	
	//����index���ڵ�ɾ��
	T remove(int index);
	
	//��rmָ��Ľڵ�ɾ��
	T remove(Link* rm);
	
	//�����������Ƿ���ֵ����target�Ľڵ㣬����оͷ��ظýڵ�ָ�룬���򷵻�nullptr
	Link* search(T& target);

	/**********����������ֻ����ͷ�����ã�**********/
	
	//��pos�ڵ�֮ǰ����һ���ڵ㣬Ԫ��Ϊelem
	void insert(Link* pos,T& elem);
	
	//���ص�index���ڵ��ָ��
	Link* getNode(int index);
	
	//��������ͷŶ���ռ�
	void clear();
	
	//�������Ϊ�շ���true�����򷵻�false
	bool empty();
	
	//����������
	int getSize();
	
	//��ӡ����
	void printLink(std::ostream& os);

	/**********��������������ͷ���֮��Ľڵ���Ե��ã�**********/
	
	//���ص�ǰ�ڵ�洢������
	T getElem();
	
	//���ص�ǰ�ڵ�ǰһ���ڵ��ָ��
	Link* getPrev();
	
	//���ص�ǰ�ڵ��һ���ڵ��ָ��
	Link* getNext();

private:

	//��ǰ�ڵ�洢����Ϣ
	T elem;
	
	//ǰһ���ڵ��ָ��
	Link* prev;
	
	//��һ���ڵ��ָ��
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
		//os<<p->getElem()<<" -> ";
		(p->getElem()).print_CharString(os);
		os<<" ";
		p=p->next;
	}
	//os<<p->getElem()<<std::endl;
	(p->getElem()).print_CharString(os);
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
