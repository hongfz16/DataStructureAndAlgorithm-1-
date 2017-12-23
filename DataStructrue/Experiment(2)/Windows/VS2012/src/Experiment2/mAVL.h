/**
@brief AVL数模板类
@file mAVL.h
@author 洪方舟
@email hongfz16@163.com
@version 3.0
@date 2017.12.23
*/

#ifndef _MAVL_H_
#define _MAVL_H_

#include <iostream>
using namespace std;

const int LH=1;
const int EH=0;
const int RH=-1;

template<class KEY,class DATA>
class mAVL;

//左旋
template<class KEY,class DATA>
void R_Rotate(mAVL<KEY,DATA>*& p)
{
	mAVL<KEY,DATA>* lc=p->lchild;
	p->lchild=lc->rchild;
	lc->rchild=p;
	p=lc;
}

//右旋
template<class KEY,class DATA>
void L_Rotate(mAVL<KEY,DATA>*& p)
{
	mAVL<KEY,DATA>* rc=p->rchild;
	p->rchild=rc->lchild;
	rc->lchild=p;
	p=rc;
}

//左子树不平衡
template<class KEY,class DATA>
void LeftBalance(mAVL<KEY,DATA>*& t)
{
	mAVL<KEY,DATA>* lc=t->lchild;
	mAVL<KEY,DATA>* rd=lc->rchild;
	switch(lc->bf)
	{
		case LH:
		t->bf=lc->bf=EH;
		R_Rotate(t);
		break;
			
		case RH:
		switch(rd->bf)
		{
			case LH: t->bf=RH; lc->bf=EH; break;
			case EH: t->bf=lc->bf=EH; break;
			case RH: t->bf=EH; lc->bf=LH; break;
		}
		rd->bf=EH;
		L_Rotate(t->lchild);
		R_Rotate(t);
		break;

		case EH:
		t->bf=LH;
		lc->bf=RH;
		R_Rotate(t);
		break;
	}
}

//右子树不平衡
template<class KEY,class DATA>
void RightBalance(mAVL<KEY,DATA>*& t)
{
	mAVL<KEY,DATA>* rc=t->rchild;
	mAVL<KEY,DATA>* ld=rc->lchild;
	switch(rc->bf)
	{
		case LH:
		switch(ld->bf)
		{
			case LH: t->bf=EH; rc->bf=RH; break;
			case EH: t->bf=rc->bf=EH; break;
			case RH: t->bf=LH; rc->bf=EH; break;
		}
		ld->bf=EH;
		R_Rotate(t->rchild);
		L_Rotate(t);
		break;

		case RH:
		t->bf=rc->bf=EH;
		L_Rotate(t);
		break;

		case EH:
		t->bf=RH;
		rc->bf=LH;
		L_Rotate(t);
		break;
	}
}

//插入节点
template<class KEY,class DATA>
mAVL<KEY,DATA>* Insert(mAVL<KEY,DATA>*& avl,KEY& k,bool& taller,bool& success)
{
	mAVL<KEY,DATA>*& lchild=avl->lchild;
	mAVL<KEY,DATA>*& rchild=avl->rchild;
	int& bf=avl->bf;
	mAVL<KEY,DATA>* re=nullptr;
	if(avl->empty)
	{
		avl->key=k;
		taller=true;
		success=true;
		avl->empty=false;
		return avl;
	}
	if(k==avl->key)
	{
		taller=false;
		success=false;
		return avl;
	}
	if(k<avl->key)
	{
		if(lchild==nullptr) lchild=new mAVL<KEY,DATA>();
		re=Insert(lchild,k,taller,success);
		if(success==false)
			return re;
		if(taller)
		{
			switch(bf)
			{
				case LH:
				LeftBalance(avl);
				taller=false;
				break;

				case EH:
				bf=LH;
				taller=true;
				break;

				case RH:
				bf=EH;
				taller=false;
				break;
			}
		}
	}
	else
	{
		if(rchild==nullptr) rchild=new mAVL<KEY,DATA>();
		re=Insert(rchild,k,taller,success);
		if(success==false)
			return re;
		if(taller)
		{
			switch(bf)
			{
				case LH:
				bf=EH;
				taller=false;
				break;

				case EH:
				bf=RH;
				taller=true;
				break;
				
				case RH:
				RightBalance(avl);
				taller=false;
				break;
			}
		}
	}
	return re;
}

//删除节点
template<class KEY,class DATA>
bool deleteNode(mAVL<KEY,DATA>*& t,KEY k,bool& shorter)
{
	if(t==nullptr)
		return false;
	if(t->key==k)
	{
		mAVL<KEY,DATA>* q=nullptr;
		if(t->lchild==nullptr)
		{
			q=t;
			t=t->rchild;
			q->rchild=nullptr;
			delete q;
			shorter=true;
		}
		else if(t->rchild==nullptr)
		{
			q=t;
			t=t->lchild;
			q->lchild=nullptr;
			delete q;
			shorter=true;
		}
		else
		{
			q=t->lchild;
			while(q->rchild!=nullptr)
			{
				q=q->rchild;
			}
			t->data=q->data;
			t->key=q->key;
			deleteNode(t->lchild,q->key,shorter);
			if(shorter)
			{
				switch(t->bf)
				{
					case LH:
					t->bf=EH;
					shorter=true;
					break;

					case EH:
					t->bf=RH;
					shorter=false;
					break;

					case RH:
					if(t->rchild->bf==EH)
						shorter=false;
					else
						shorter=true;
					RightBalance(t);
					break;
				}
			}

		}
	}
	else if(k<t->key)
	{
		if(!deleteNode(t->lchild,k,shorter))
			return false;
		if(shorter)
		{
			switch(t->bf)
			{
				case LH:
				t->bf=EH;
				shorter=true;
				break;

				case EH:
				t->bf=RH;
				shorter=false;
				break;

				case RH:
				if(t->rchild->bf==EH)
					shorter=false;
				else
					shorter=true;
				RightBalance(t);
				break;
			}
		}
	}
	else
	{
		if(!deleteNode(t->rchild,k,shorter))
			return false;
		if(shorter)
		{
			switch(t->bf)
			{
				case LH:
				if(t->lchild->bf==EH)
					shorter=false;
				else
					shorter=true;
				LeftBalance(t);
				break;

				case EH:
				t->bf=LH;
				shorter=false;
				break;

				case RH:
				t->bf=EH;
				shorter=true;
				break;
			}
		}
	}
	return true;
}

//AVL树定义
template<class KEY,class DATA>
class mAVL
{
public:
	mAVL()
	{
		lchild=rchild=nullptr;
		bf=EH;
		empty=true;
	}
	~mAVL()
	{
		if(lchild!=nullptr)
			delete lchild;
		if(rchild!=nullptr)
			delete rchild;
	}

	mAVL* Search(KEY& k)
	{
		if(k==key)
			return this;
		else if(lchild!=nullptr && k<key)
			return lchild->Search(k);
		else if(rchild!=nullptr && k>key)
			return rchild->Search(k);
		return nullptr;
	}

	KEY key;
	DATA data;

	bool empty;

	mAVL* lchild;
	mAVL* rchild;
	int bf;

public:
	KEY getKey() {return key;}
	DATA getData() {return data;}
	bool isempty() {return empty;}
	mAVL* getlchild() {return lchild;}
	mAVL* getrchild() {return rchild;}
	int getBf() {return bf;}

	KEY& editKey() {return key;}
	DATA& editData() {return data;}
	mAVL*& editlchild() {return lchild;}
	mAVL*& editrchild() {return rchild;}
	int& editBf() {return bf;}
};

#endif
