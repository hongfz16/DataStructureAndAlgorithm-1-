#include "../Stack.h"
#include <iostream>
using namespace std;

int main()
{
	Stack<int> testStack;
	if(testStack.empty())
		cout<<"empty"<<endl;
	else
		cout<<"not empty"<<endl;
	for(int i=0;i<999;++i)
	{
		testStack.push(i);
	}
	cout<<testStack.top()<<endl;
	for(int i=0;i<998;++i)
	{
		testStack.pop();
		//cout<<testStack.top()<<endl;
	}
	cout<<testStack.top()<<endl;
	if(testStack.empty())
		cout<<"empty"<<endl;
	else
		cout<<"not empty"<<endl;
	for(int i=0;i<1500;++i)
	{
		testStack.push(i);
		//cout<<testStack.top()<<endl;
	}
	cout<<testStack.top()<<endl;
	return 0;
}