# coding=<utf8>
from bs4 import BeautifulSoup as bs
from urllib.request import urlopen
import re
import string

useadd=[]


def cleanInput(input):
    r='[，。、（）【】《》？：’!"#$%&\'()*“”！；+,-./:;<=>?@[\\]^_`{|}~]+'
    input = re.sub('\n'," ",input)
    input = re.sub(r'([\d]+)',"",input)
    input = re.sub(r'([A-Za-z]+)',"",input)
    input = re.sub(' '," ",input)
    input = re.sub(r,"",input)
    cleanInput=[]
    input = input.split(' ')
    for item in input:
        item=item.strip(' ')
        if len(item)>1 and item.find("下载附件")==-1 and item.find("上传")==-1 and item.find("发表于")==-1:
            cleanInput.append(item)
    return cleanInput

def get_content(url):
    try:
        html=urlopen(url,timeout=2)
    except Exception as e:
        print(str(e))
        return
    try:
        bsobj=bs(html,"html.parser")
    except Exception as e:
        print(str(e))
        return
    content=bsobj.findAll("td",{"class":"t_f"})
    html.close()
    return content

def get_content_text(content):
    re_content=''
    if content is None:
        return
    for c in content:
        re_content+=(c.get_text())
    return cleanInput(re_content)

def get_link(url):
    try:
        html=urlopen(url,timeout=2)
    except Exception as e:
        print(str(e))
        return
    try:
        bsobj=bs(html,"html.parser")
    except Exception as e:
        print(str(e))
        return
    links=bsobj.findAll("a",{"target":"_blank","href":re.compile("^thread")})
    adds=[]
    for link in links:
        if link.attrs['href'] is not None:
            if link.attrs['href'] not in adds:
                adds.append("http://bbs.cehome.com/"+link.attrs['href'])
                print(link.attrs['href'])
    html.close()
    return adds

def getLib(adds,output):
    global useadd
    i=0
    if adds is None:
        return
    for add in adds:
        if add in useadd:
            continue
        useadd.append(add)
        print("post"+str(i))
        i+=1
        text=get_content_text(get_content(add))
        if text is None:
            continue
        for t in text:
            output.write(t)

def get_posts(urlformat,output):
    for i in range(2,12):
        print("page"+str(i))
        url=urlformat+str(i)+".html"
        getLib(get_link(url),output)

def n_gram(input,n):
    re_list=[]
    for i in range(0,len(input)-n):
        substring=input[i:i+n]
        re_list.append(substring)
    return re_list

output=open("contents.txt","w")
get_posts("http://bbs.cehome.com/forum-43-",output)
output.close()

input=open("test.txt","r")
segment=open("segment.txt","w")
while True:
    line=input.readline()
    if not line:
        break
    for i in range(2,5):
        gram=(n_gram(line,i))
        commalink=",".join(gram)
        segment.write(commalink)

input.close()
segment.close()

word_lst = []
word_dict= {}

wf=open("segment.txt","r")
wf2=open("count.txt","w")

for word in wf:
    word_lst.append(word.split(','))
    for item in word_lst:
        for item2 in item:
            if item2 not in word_dict:
                word_dict[item2] = 1
            else:
                word_dict[item2] += 1

for key in word_dict:
    if word_dict[key]>=3:
        wf2.write(key+' '+str(word_dict[key])+'\n')