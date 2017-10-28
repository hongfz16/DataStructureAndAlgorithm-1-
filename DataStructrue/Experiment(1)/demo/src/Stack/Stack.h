#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>

template<class T>
class Stack
{
public:
	/**********构造函数和析构函数**********/

	//初始化栈，初始栈空间大小为1000
	Stack();
	
	//释放栈空间
	~Stack();

	/********** **********/

	//向栈顶添加元素
	void push(T ele);
	
	//弹出一个元素
	void pop();
	
	//返回栈顶元素
	T top();
	
	//如果栈为空返回true，否则返回false
	bool empty();

private:

	//指向栈底的指针
	T* base;
	
	//指向栈顶上面一个位置的指针
	T* ptrtop;
	
	//栈当前的容量
	int size;
	
	//栈内元素的数量
	int num;

	//初始化时分配给栈的空间
	static int init_size;
	
	//每次栈需要扩大的时候空间的增量
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
	delete base;
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
	*ptrtop=ele;
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
	return *(ptrtop-1);
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