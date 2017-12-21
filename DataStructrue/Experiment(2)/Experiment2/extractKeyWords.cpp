/**
@brief 栈结构网页解析函数定义
@file extractKeyWords.cpp
@author 洪方舟
@email hongfz16@163.com
@version 1.0
@date 2017.11.3
*/

#include "extractKeyWords.h"
using namespace std;

//0 "发帖大类" <div class="z">第三个<a>
//1 "发帖小类" <div class="z">第四个<a>
//2 "发帖标题" <div class="z">第五个<a>
//3 "发帖内容" 全文第一个<td class="t_f">里面的<p>
//4 "发帖人" 全文第一个<div class="authi">里面的<a>
//5 "发帖日期" 全文第二个<div class="authi">里面的<em>
//6 "发帖类型" 全文唯一一个<div class="ts z h1">里面第一个<a>
//"分词结果"

#define NEED_PRINT

class label
{
public:
	label(){}
	label(const label& la)
	{
		type=la.type;
		class_name=la.class_name;
	}
	label& operator=(const label& other)
	{
		type=other.type;
		class_name=other.class_name;
		return *this;
	}
	CharString type;
	CharString class_name;
};

label get_label_info(CharString& html,int pos)
{
	label re_label;
	int i=0;
	int size=html.getSize();

	for(i=pos+1;i<size && html.getIndex(i)!=' ' && html.getIndex(i)!='>';++i)
	{
		re_label.type.append(html.getIndex(i));
	}
	while(html.getIndex(i)!='>')
	{
		++i;
	}
	CharString sub=html.subString(pos,i-pos+1);
	string temp("class");
	CharString target(temp);
	int class_pos=sub.indexOf(target,0);
	if(class_pos!=-1)
	{
		for(;sub.getIndex(class_pos)!='"' && sub.getIndex(class_pos)!='\'';++class_pos){}
		++class_pos;
		for(;sub.getIndex(class_pos)!='"' && sub.getIndex(class_pos)!='\'';++class_pos)
		{
			re_label.class_name.append(sub.getIndex(class_pos));
		}
	}
	return re_label;
}

CharString get_close_info(CharString& html,int pos)
{
	CharString re;
	//cout<<html.getIndex(pos+1)<<endl;
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
		if(i<size-1 && html.getIndex(i)=='/' && html.getIndex(i+1)=='>')
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
	return -1;
}

int find_content(Stack<label>& m_stack,CharString& html,int pos,CharString* info)
{
	int size=html.getSize();
	int i=0;
	//bool flag=false;
	bool canread=false;

	int count=0;

	for(i=pos;i<size;++i)
	{
		//cout<<html.getIndex(i);
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)!='!' && html.getIndex(i+1)!='/')
		{
			label new_la=get_label_info(html,i);
			//cout<<"found new lable"<<endl;
			m_stack.push(new_la);
			for(;html.getIndex(i)!='>';++i);

			//cout<<new_la.type<<endl;
			//if(new_la.type.is_equal("ignore_js_op"))
			//{
				//count++;
				//cout<<count<<endl;
			//}

			if(new_la.type.is_equal(string("p")) || new_la.class_name.is_equal(string("t_f")) || new_la.type.is_equal(string("font")))//&& flag==false)
			{
				/*
				for(;html.getIndex(i)!='>';++i);
				for(++i;html.getIndex(i)!='<';++i)
				{
					info[3].append(html.getIndex(i));
				}
				--i;

				flag=true;*/
				
				canread=true;
			}
			else
			{
				canread=false;
			}
			if(new_la.type.is_equal(string("img")) || new_la.type.is_equal(string("br")))
			{
				m_stack.pop();
				if(m_stack.top().class_name.is_equal("t_f") || m_stack.top().class_name.is_equal("p") || m_stack.top().class_name.is_equal("font"))
					canread=true;
			}
			//cout<<"found something"<<endl;
			//cout<<pos<<" "<<size<<" "<<i<<endl;
			continue;
		}

		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)=='/')
		{
			if(m_stack.empty())
			{
				cerr<<"Stack empty!"<<endl;
				return -1;
			}
			//cout<<"before judge return"<<endl;
			//cout<<m_stack.top().class_name<<endl;
			if(m_stack.top().class_name.is_equal(string("t_f")))
			{
				//cout<<"enter the func"<<endl;
				return i-1;
			}
			//cout<<"after judge return"<<endl;
			//cout<<"before pop"<<endl;
			m_stack.pop();
			CharString close_info=get_close_info(html,i);
			//cout<<endl;
			//cout<<"/"<<close_info<<endl;
			if(m_stack.top().class_name.is_equal("t_f") || m_stack.top().type.is_equal("p") || m_stack.top().type.is_equal("font"))
			{
				canread=true;
			}
			for(;html.getIndex(i)!='>';++i);
			continue;
		}

		if(canread)
		{
			if(html.getIndex(i)==' ')
				continue;
			info[3].append(html.getIndex(i));
			//cout<<html.getIndex(i);
		}


		/*
		if(i<size-1 && html.getIndex(i)=='/' && html.getIndex(i+1)=='>')
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
					if(info[3].empty())
					{
						int ii=pos;
						for(ii=pos;html.getIndex(ii)!='>';++ii);
						++ii;
						for(;html.getIndex(ii)!=' ';++ii);
						for(;html.getIndex(ii)!='<' || html.getIndex(ii+1)!='/';++ii)
						{
							info[3].append(html.getIndex(ii));
						}
						CharString replace;
						for(int ii=0;ii<info[3].getSize();++ii)
						{
							if(ii+2<info[3].getSize() && info[3].getIndex(ii)=='<' && info[3].getIndex(ii+1)=='b' && info[3].getIndex(ii+2)=='r')
							{
								ii+=2;
								continue;
							}
							if(ii+1<info[3].getSize() && info[3].getIndex(ii)=='/' && info[3].getIndex(ii+1)=='>')
							{
								++ii;
								continue;
							}
							replace.append(info[3].getIndex(ii));
						}
						info[3]=replace;
					}
					return i-1;
				}
				else
				{
					cerr<<"HTML Format Error!"<<endl;
				}
			}
		}
		*/
	}
	return -1;
}

int find_author(Stack<label>& m_stack,CharString& html,int pos,CharString* info)
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
				--i;
				flag=true;
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
	return -1;
}

int find_date(Stack<label>& m_stack,CharString& html,int pos,CharString* info)
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
			if(new_la.type.is_equal(string("em")) && flag==false)
			{
				for(;html.getIndex(i)!='>';++i);
				bool flag1=false;
				bool flag2=false;
				for(++i;html.getIndex(i)!='<';++i)
				{
					if(html.getIndex(i)==' ' && flag1==false)
					{
						flag1=true;
						++i;
					}
					if(html.getIndex(i)==' ' && flag1==true)
					{
						flag2=true;
						++i;
					}
					if(flag1==true && flag2==false)
					{
						info[5].append(html.getIndex(i));
					}
				}
				--i;
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
	return -1;
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
					if(html.getIndex(i)=='[' || html.getIndex(i)==']')
						continue;
					info[6].append(html.getIndex(i));
				}
				flag=true;
				--i;
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
	return -1;
}

void traverse_html(Stack<label>& m_stack,CharString& html,CharString* info)
{
	bool found[5];
	for(int i=0;i<5;++i)
	{
		found[i]=false;
	}
	int size=html.getSize();
	for(int i=0;i<size-1;++i)
	{
		if(i<size-1 && html.getIndex(i)=='<' && html.getIndex(i+1)!='!' && html.getIndex(i+1)!='/')
		{
			label new_la=get_label_info(html,i);
			if(new_la.type.is_equal(string("div")) && new_la.class_name.is_equal(string("z")) && found[0]==false)
			{
				int temp=find_basic_info(m_stack,html,i,info);
				if(temp!=-1)
					i=temp;
				else
				{
					cerr<<"cannot find pair"<<endl;
				}
				found[0]=true;
				continue;
			}
			if(new_la.type.is_equal(string("td")) && new_la.class_name.is_equal(string("t_f")) && found[1]==false)
			{
				//cout<<"finding content"<<endl;
				int temp=find_content(m_stack,html,i,info);
				//cout<<"found content"<<endl;
				if(temp!=-1)
					i=temp;
				else
				{
					cerr<<"cannot find pair"<<endl;
				}
				found[1]=true;
				continue;
			}
			if(new_la.type.is_equal(string("div")) && new_la.class_name.is_equal(string("authi")) && found[2]==false)
			{
				int temp=find_author(m_stack,html,i,info);
				if(temp!=-1)
					i=temp;
				else
				{
					cerr<<"cannot find pair"<<endl;
				}
				found[2]=true;
				continue;
			}
			if(new_la.type.is_equal(string("div")) && new_la.class_name.is_equal(string("authi")) && found[3]==false)
			{
				int temp=find_date(m_stack,html,i,info);
				if(temp!=-1)
					i=temp;
				else
				{
					cerr<<"cannot find pair"<<endl;
				}
				found[3]=true;
				continue;
			}
			if(new_la.type.is_equal(string("div")) && new_la.class_name.is_equal(string("ts z h1")) && found[4]==false)
			{
				int temp=find_type(m_stack,html,i,info);
				if(temp!=-1)
					i=temp;
				else
				{
					cerr<<"cannot find pair"<<endl;
				}
				found[4]=true;
				continue;
			}
			m_stack.push(new_la);
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
				//cout<<close_info<<endl;
				label top=m_stack.top();
				if(top.type.is_equal(close_info))
				{
					m_stack.pop();
				}
				else
				{
					//cerr<<"HTML Format Error!"<<endl;
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

void print_info(CharString* info,int _size,ofstream& os,wordSegmentation& dic,UnicodeToGBK& u2g,pageInfo& pinfo)
{
	for(int i=0;i<_size-1;++i)
	{
		if(i==3 && !info[3].empty())
		{
			string replace;
			CharString sub("&#");
			if(info[3].indexOf(sub,0)==-1)
			{
				CharString nbspsub("&nbsp;");
				int pos=0;
				while(1)
				{
					pos=info[3].indexOf(nbspsub,pos);
					if(pos==-1)
						break;
					CharString le=info[3].subString(0,pos);
					le.append(' ');
					CharString ri=info[3].subString(pos+6,info[3].getSize()-pos-6);
					CharString* done=le.concat(ri);
					info[3]=(*done);
				}
				CharString replacecomma;
				for(int ii=0;ii<info[3].getSize();++ii)
				{
					if(info[3].getIndex(ii)!=',')
						replacecomma.append(info[3].getIndex(ii));
					else
					{
						int* re=u2g.convert_single(65292);
						char comma1=re[0];
						char comma2=re[1];
						replacecomma.append(comma1);
						replacecomma.append(comma2);
					}
				}
				info[3]=replacecomma;
				CharString newinfo3;
				for(int ii=0;ii<info[3].getSize();)
				{
					/*
					if(ii<info[3].getSize() && info[3].getIndex(ii)>0 && info[3].getIndex(ii)<=127)
					{
						newinfo3.append((char)0);
						newinfo3.append(info[3].getIndex(ii));
						++ii;
						while(ii<info[3].getSize() && info[3].getIndex(ii)>0 && info[3].getIndex(ii)<=127)
						{
							newinfo3.append(info[3].getIndex(ii));
							++ii;
						}
						newinfo3.append((char)0);
					}
					if(ii<info[3].getSize())
						newinfo3.append(info[3].getIndex(ii));
					*/
					if(ii<info[3].getSize()-1 && (info[3].getIndex(ii)>127 || info[3].getIndex(ii)<0))
					{
						newinfo3.append(info[3].getIndex(ii));
						newinfo3.append(info[3].getIndex(ii+1));
						//cout<<info[3].getIndex(ii)<<info[3].getIndex(ii+1)<<endl;
						ii+=2;
						while(ii<info[3].getSize()-1 && (info[3].getIndex(ii)>127 || info[3].getIndex(ii)<0))
						{
							//cout<<info[3].getIndex(ii)<<info[3].getIndex(ii+1)<<endl;
							newinfo3.append(info[3].getIndex(ii));
							newinfo3.append(info[3].getIndex(ii+1));
							ii+=2;
						}
					}
					if(ii<info[3].getSize() && info[3].getIndex(ii)<=127 && info[3].getIndex(ii)>0)
					{
						newinfo3.append((char)0);
						newinfo3.append(info[3].getIndex(ii));
						//cout<<(int)info[3].getIndex(ii);
						++ii;
						while(ii<info[3].getSize() && info[3].getIndex(ii)<=127 && info[3].getIndex(ii)>0)
						{
							newinfo3.append(info[3].getIndex(ii));
							++ii;
						}
						newinfo3.append((char)0);
					}
				}
				info[3]=newinfo3;
#ifdef NEED_PRINT
				os<<info[i]<<",";
#endif
				continue;
			}
			int size=info[3].getSize();
			for(int ii=0;ii<size;++ii)
			{
				bool flag=false;
				string temp;
				temp.clear();
				int sum=0;
				if(info[3].getIndex(ii)=='&')
				{
					ii+=2;
					while(info[3].getIndex(ii)!=';')
					{
						sum=sum*10+info[3].getIndex(ii)-'0';
						++ii;
					}
				}
				else
				{
					flag=true;
					char nullchar=0;
					temp+=nullchar;
					while(ii<size && info[3].getIndex(ii)!='&')
					{
						if(info[3].getIndex(ii)!=',')
							temp+=info[3].getIndex(ii);
						else
						{
							int* re=u2g.convert_single(65292);
							char comma1=re[0];
							char comma2=re[1];
							string scomma;
							scomma+=comma1;
							scomma+=comma2;
							temp+=scomma;
						}

						++ii;
					}
					temp+=nullchar;
					--ii;
				}
				if(flag==false)
				{
					int *re=u2g.convert_single(sum);
					string sstring;
					sstring+=(char)re[0];
					sstring+=(char)re[1];
					replace+=sstring;
				}
				else
				{
					replace+=temp;
				}
			}
			CharString info3_replace(replace);
			info[3]=info3_replace;
#ifdef NEED_PRINT
			os<<info[3]<<",";
#endif
			continue;
		}
#ifdef NEED_PRINT
		os<<info[i]<<",";
#endif
	}
#ifdef NEED_PRINT
	os<<info[_size-1]<<",";
#endif
	CharString newinfo2;
	for(int i=0;i<info[2].getSize();)
	{
		if(i<info[2].getSize() && (info[2].getIndex(i)>127 || info[2].getIndex(i)<0))
					{
						newinfo2.append(info[2].getIndex(i));
						newinfo2.append(info[2].getIndex(i+1));
						i+=2;
						while(i<info[2].getSize() && (info[2].getIndex(i)>127 || info[2].getIndex(i)<0))
						{
							newinfo2.append(info[2].getIndex(i));
							newinfo2.append(info[2].getIndex(i+1));
							i+=2;
						}
					}
					if(i<info[2].getSize() && info[2].getIndex(i)<=127 && info[2].getIndex(i)>0)
					{
						newinfo2.append((char)0);
						newinfo2.append(info[2].getIndex(i));
						++i;
						while(i<info[2].getSize() && info[2].getIndex(i)<=127 && info[2].getIndex(i)>0)
						{
							newinfo2.append(info[2].getIndex(i));
							++i;
						}
						newinfo2.append((char)0);
					}
	}
	info[2]=newinfo2;
	Link<CharString>* title_seg=dic.max_back_segment(info[2],8);
#ifdef NEED_PRINT
	title_seg->printLink(os);
	os<<" ";
#endif
	Link<CharString>* seg=dic.max_back_segment(info[3],8);
#ifdef NEED_PRINT
	seg->printLink(os);
#endif

	pinfo.setTexts(info[3]);
	pinfo.setTitle(info[2]);
	pinfo.setWordCount(title_seg);
	pinfo.setWordCount(seg);

	delete title_seg;
	delete seg;
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

void extractKeyWords(string inputfilename,string outputfilename,string url,int count,wordSegmentation& dic,UnicodeToGBK& u2g,pageInfo& pinfo)
{
	CharString info[7];
	string filename(inputfilename);
	extractInfo(info,filename);
	ofstream fout;
	fout.open(outputfilename,ios::app);
	fout<<count<<","<<url<<",";
	print_info(info,7,fout,dic,u2g,pinfo);
	fout<<endl;
	fout.close();
	cout<<"Finish processing the "<<count<<"th file!"<<endl;
}
