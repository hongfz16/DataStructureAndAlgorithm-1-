// unordered_map::insert
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void display(unordered_map<string,double> myrecipe,string str)
{
    cout << str << endl;
    for (auto& x: myrecipe)
        cout << x.first << ": " << x.second << endl;
    cout << endl;
}

int main ()
{
    unordered_map<string,double>
    myrecipe,
    mypantry ;//= {{"milk",2.0},{"flour",1.5}};

    /****************插入*****************/
    pair<string,double> myshopping ("baking powder",0.3);
    myrecipe.insert (myshopping);                        // 复制插入
    myrecipe.insert (make_pair<string,double>("eggs",6.0)); // 移动插入
    myrecipe.insert (mypantry.begin(), mypantry.end());  // 范围插入
    //myrecipe.insert ({{"sugar",0.8},{"salt",0.1}});    // 初始化数组插入(可以用二维一次插入多个元素，也可以用一维插入一个元素)
    myrecipe["coffee"] = 10.0;  //数组形式插入

    display(myrecipe,"myrecipe contains:");

    /****************查找*****************/
    unordered_map<string,double>::const_iterator got = myrecipe.find ("coffee");

    if ( got == myrecipe.end() )
        cout << "not found";
    else
        cout << "found "<<got->first << " is " << got->second<<"\n\n";
    /****************修改*****************/
    myrecipe.at("coffee") = 9.0;
    myrecipe["milk"] = 3.0;
    display(myrecipe,"After modify myrecipe contains:");


    /****************擦除*****************/
    myrecipe.erase(myrecipe.begin());  //通过位置
    myrecipe.erase("milk");    //通过key
    display(myrecipe,"After erase myrecipe contains:");

    /****************交换*****************/
    myrecipe.swap(mypantry);
    display(myrecipe,"After swap with mypantry, myrecipe contains:");

    /****************清空*****************/
    myrecipe.clear();
    display(myrecipe,"After clear, myrecipe contains:");
    return 0;
}
