/**
@brief ջģ���������붨��
@file main.cpp
@author �鷽��
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>

template<class T>
class Stack
{
public:
	/**********���캯������������**********/

	//��ʼ��ջ����ʼջ�ռ��СΪ1000
	Stack();
	
	//�ͷ�ջ�ռ�
	~Stack();

	/********** **********/

	//��ջ�����Ԫ��
	void push(T ele);
	
	//����һ��Ԫ��
	void pop();
	
	//����ջ��Ԫ��
	T top();
	
	//���ջΪ�շ���true�����򷵻�false
	bool empty();

private:

	//ָ��ջ�׵�ָ��
	T* base;
	
	//ָ��ջ������һ��λ�õ�ָ��
	T* ptrtop;
	
	//ջ��ǰ������
	int size;
	
	//ջ��Ԫ�ص�����
	int num;

	//��ʼ��ʱ�����ջ�Ŀռ�
	static int init_size;
	
	//ÿ��ջ��Ҫ�����ʱ��ռ������
	static int delta_size;
};

template<class T>
int Stack<T>::init_size=1000;

template<class T>
int Stack<T>::delta_size=10;

template<class T>
Stack<T>::Stack()
{
	base=new T[init_size];
	size=init_size;
	ptrtop=base;
	num=0;
}

template<class T>
Stack<T>::~Stack()
{
	delete[] base;
}

template<class T>
void Stack<T>::push(T ele)
{
	if(num==size-1)
	{
		T* new_base=new T[size+delta_size];
		for(int i=0;i<size;++i)
		{
			new_base[i]=base[i];
		}
		delete base;
		base=new_base;
		size+=delta_size;
	}
	base[num]=ele;
	++ptrtop;
	++num;
}

template<class T>
void Stack<T>::pop()
{
	if(num==0)
	{
		std::cerr<<"Stack empty!"<<std::endl;
		throw;
	}
	--num;
	--ptrtop;
}

template<class T>
T Stack<T>::top()
{
	if(num==0)
	{
		std::cerr<<"Stack empty!"<<std::endl;
		throw;
	}
	return base[num-1];
}

template<class T>
bool Stack<T>::empty()
{
	if(ptrtop==base)
		return true;
	else
		return false;
}

#endif
