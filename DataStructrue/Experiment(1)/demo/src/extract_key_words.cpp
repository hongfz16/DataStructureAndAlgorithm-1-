#include <iostream>
#include <fstream>
#include <string>

#include "Stack/Stack.h"
#include "CharString/CharString.h"

using namespace std;

//0 "发帖大类" <div class="z">第三个<a>
//1 "发帖小类" <div class="z">第四个<a>
//2 "发帖标题" <div class="z">第五个<a>
//3 "发帖内容" 全文第一个<td class="t_f">里面的<p>
//4 "发帖人" 全文第一个<div class="authi">里面的<a>
//5 "发帖日期" 全文第二个<div class="authi">里面的<em>
//6 "发帖类型" 全文唯一一个<div class="ts z h1">里面第一个<a>
//"分词结果"

struct label
{
	CharString type;
	CharString class_name;
};

label get_label_info(CharString& html,int pos)
{
	label re_label;
	int i=0;
	int size=html.getSize();
	CharString type;
	CharString class_name;
	for(i=pos+1;i<size && html.getIndex(i)!=' ' && html.getIndex(i)!='>';++i)
	{
		type.append(html.getIndex(i));
	}
	while(html.getIndex(i)!='>')
	{
		++i;
	}
	CharString sub=html.subString(pos,i);
	string temp("class");
	CharString target(temp);
	int class_pos=sub.indexOf(target,0);
	if(class_pos!=-1)
	{
		for(;sub.getIndex(class_pos)!='"';++class_pos){}
		++class_pos;
		for(;sub.getIndex(class_pos)!='"';++class_pos)
		{
			class_name.append(sub.getIndex(class_pos));
		}
	}
	re_label.type=type;
	re_label.class_name=class_name;
	return re_label;
}

CharString get_close_info(CharString& html,int pos)
{
	CharString re;
	for(int i=pos+2;html.getIndex(i)!='>' && html.getIndex(i)!=' ';++i)
	{
		re.append(html.getIndex(i));
	}
	return re;
}

int find_basic_info(Stack<label>& m_stack,CharString& html,int pos,CharString* info)
{
	int size=html.getSize();
	int count=0;
	int i=0;
	for(i=pos;i<size;++i)
	{
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)!='!' && html.getIndex(i+1)!='/')
		{
			label new_la=get_label_info(html,i);
			m_stack.push(new_la);
			if(new_la.type.is_equal(string("a")))
			{
				++count;
				for(;html.getIndex(i)!='>';++i);
				if(count==3 || count==4 || count==5)
				{	
					for(++i;html.getIndex(i)!='<';++i)
					{
						info[count-3].append(html.getIndex(i));
					}
					--i;
				}
			}
		}
		if(i<size-1 && html.getIndex(i)=='/' && html.getIndex(i+1)!='>')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
				m_stack.pop();
		}
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)=='/')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
			{
				CharString close_info=get_close_info(html,i);
				label top=m_stack.top();
				if(top.type.is_equal(close_info) && !top.class_name.is_equal(string("z")))
				{
					m_stack.pop();
				}
				else if(top.type.is_equal(close_info) && top.class_name.is_equal(string("z")))
				{
					return i-1;
				}
				else
				{
					cerr<<"HTML Format Error!"<<endl;
				}
			}
		}
	}
}

int find_content(Stack<label>& m_stack,CharString& html,int pos,CharString* info)
{
	int size=html.getSize();
	int i=0;
	for(i=pos;i<size;++i)
	{
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)!='!' && html.getIndex(i+1)!='/')
		{
			label new_la=get_label_info(html,i);
			m_stack.push(new_la);
			if(new_la.type.is_equal(string("p")))
			{
				for(;html.getIndex(i)!='>';++i);
				for(++i;html.getIndex(i)!='<';++i)
				{
					info[3].append(html.getIndex(i));
				}
				--i;
			}
		}
		if(i<size-1 && html.getIndex(i)=='/' && html.getIndex(i+1)!='>')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
				m_stack.pop();
		}
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)=='/')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
			{
				CharString close_info=get_close_info(html,i);
				label top=m_stack.top();
				if(top.type.is_equal(close_info) && !top.class_name.is_equal(string("t_f")))
				{
					m_stack.pop();
				}
				else if(top.type.is_equal(close_info) && top.class_name.is_equal(string("t_f")))
				{
					return i-1;
				}
				else
				{
					cerr<<"HTML Format Error!"<<endl;
				}
			}
		}
	}
}

int find_author(Stack<label>& m_stack,CharString& html,int pos,CharString* info)
{
	int size=html.getSize();
	int i=0;
	for(i=pos;i<size;++i)
	{
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)!='!' && html.getIndex(i+1)!='/')
		{
			label new_la=get_label_info(html,i);
			m_stack.push(new_la);
			if(new_la.type.is_equal(string("a")))
			{
				for(;html.getIndex(i)!='>';++i);
				for(++i;html.getIndex(i)!='<';++i)
				{
					info[4].append(html.getIndex(i));
				}
				--i;
			}
		}
		if(i<size-1 && html.getIndex(i)=='/' && html.getIndex(i+1)!='>')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
				m_stack.pop();
		}
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)=='/')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
			{
				CharString close_info=get_close_info(html,i);
				label top=m_stack.top();
				if(top.type.is_equal(close_info) && !top.class_name.is_equal(string("authi")))
				{
					m_stack.pop();
				}
				else if(top.type.is_equal(close_info) && top.class_name.is_equal(string("authi")))
				{
					return i-1;
				}
				else
				{
					cerr<<"HTML Format Error!"<<endl;
				}
			}
		}
	}
}

int find_date(Stack<label>& m_stack,CharString& html,int pos,CharString* info)
{
	int size=html.getSize();
	int i=0;
	for(i=pos;i<size;++i)
	{
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)!='!' && html.getIndex(i+1)!='/')
		{
			label new_la=get_label_info(html,i);
			m_stack.push(new_la);
			if(new_la.type.is_equal(string("em")))
			{
				for(;html.getIndex(i)!='>';++i);
				for(++i;html.getIndex(i)!='<';++i)
				{
					if(html.getIndex(i)>='0' || html.getIndex(i)<='9')
						info[4].append(html.getIndex(i));
				}
				--i;
			}
		}
		if(i<size-1 && html.getIndex(i)=='/' && html.getIndex(i+1)!='>')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
				m_stack.pop();
		}
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)=='/')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
			{
				CharString close_info=get_close_info(html,i);
				label top=m_stack.top();
				if(top.type.is_equal(close_info) && !top.class_name.is_equal(string("authi")))
				{
					m_stack.pop();
				}
				else if(top.type.is_equal(close_info) && top.class_name.is_equal(string("authi")))
				{
					return i-1;
				}
				else
				{
					cerr<<"HTML Format Error!"<<endl;
				}
			}
		}
	}
}

int find_type(Stack<label>& m_stack,CharString& html,int pos,CharString* info)
{
	int size=html.getSize();
	int i=0;
	bool flag=false;
	for(i=pos;i<size;++i)
	{
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)!='!' && html.getIndex(i+1)!='/')
		{
			label new_la=get_label_info(html,i);
			m_stack.push(new_la);
			if(new_la.type.is_equal(string("a")) && flag==false)
			{
				for(;html.getIndex(i)!='>';++i);
				for(++i;html.getIndex(i)!='<';++i)
				{
					info[4].append(html.getIndex(i));
				}
				flag=true;
				--i;
			}
		}
		if(i<size-1 && html.getIndex(i)=='/' && html.getIndex(i+1)!='>')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
				m_stack.pop();
		}
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)=='/')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
			{
				CharString close_info=get_close_info(html,i);
				label top=m_stack.top();
				if(top.type.is_equal(close_info) && !top.class_name.is_equal(string("ts z h1")))
				{
					m_stack.pop();
				}
				else if(top.type.is_equal(close_info) && top.class_name.is_equal(string("ts z h1")))
				{
					return i-1;
				}
				else
				{
					cerr<<"HTML Format Error!"<<endl;
				}
			}
		}
	}
}

void traverse_html(Stack<label>& m_stack,CharString& html,CharString* info)
{
	bool found[5];
	for(int i=0;i<5;++i)
	{
		found[i]=false;
	}
	int size=html.getSize();
	for(int i=0;i<size;++i)
	{
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)!='!' && html.getIndex(i+1)!='/')
		{
			label new_la=get_label_info(html,i);
			m_stack.push(new_la);
			if(new_la.type.is_equal(string("div")) && new_la.class_name.is_equal(string("z")) && found[0]==false)
			{
				i=find_basic_info(m_stack,html,i,info);
				found[0]=true;
				continue;
			}
			if(new_la.type.is_equal(string("td")) && new_la.class_name.is_equal(string("t_f")) && found[1]==false)
			{
				i=find_content(m_stack,html,i,info);
				found[1]=true;
				continue;
			}
			if(new_la.type.is_equal(string("div")) && new_la.class_name.is_equal(string("authi")) && found[2]==false)
			{
				i=find_author(m_stack,html,i,info);
				found[2]=true;
				continue;
			}
			if(new_la.type.is_equal(string("div")) && new_la.class_name.is_equal(string("authi")) && found[3]==false)
			{
				i=find_date(m_stack,html,i,info);
				found[3]=true;
				continue;
			}
			if(new_la.type.is_equal(string("div")) && new_la.class_name.is_equal(string("ts z h1")) && found[4]==false)
			{
				i=find_type(m_stack,html,i,info);
				found[4]=true;
				continue;
			}
		}
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)=='/')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
			{
				CharString close_info=get_close_info(html,i);
				label top=m_stack.top();
				if(top.type.is_equal(close_info))
				{
					m_stack.pop();
				}
				else
				{
					cerr<<"HTML Format Error!"<<endl;
				}
			}
		}
		if(i<size-1 && html.getIndex(i)=='/' && html.getIndex(i+1)=='>')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
			}
			else
				m_stack.pop();
		}
	}
}

void print_info(CharString* info,int size,ostream& os)
{
	for(int i=0;i<size;++i)
	{
		os<<info[i]<<endl;
	}
}

void extractInfo(CharString* info,string filename)
{
	ifstream fin(filename);
	string s;
	string temp;
	while(!fin.eof())
	{
		fin>>temp;
		s+=" ";
		s+=temp;
	}
	CharString html(s);
	Stack<label> m_stack;
	traverse_html(m_stack,html,info);
}

int main()
{
	CharString info[7];
	string filename("test.html");
	extractInfo(info,filename);
	print_info(info,7,cout);
	return 0;
}