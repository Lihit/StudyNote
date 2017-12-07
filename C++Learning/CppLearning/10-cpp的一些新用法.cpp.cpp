//
// Created by wenshao on 2017/12/5.
//

#include <iostream>
#include <tuple>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <array>
using namespace std;
void main1(){
    array<double ,4> d={1.1,2.2,3.3,4.4};
    array<double ,4> dnew=d;//一个好处是可以赋值
    for (int i = 0; i < 4; ++i) {
        cout<<dnew[i]<<endl;
    }
}

void main2(){
    array<string,3> s1={"notepad","calc","tasklist"};
    for (int i = 0; i < 3; ++i) {
        cout<<s1[i]<<endl;
        system(s1[i].c_str());
    }
}

void main3(){
    vector<int> myv={1,2,3,4};
    int ret=0;
    int *p=&ret;
    //适用于array
    for_each(myv.begin(),myv.end(),[p](int d){(*p)+=d;});
    cout<<ret<<endl;
}

//tuple多元数组
void main1() {
    int d = 10;
    double dou = 1.22;
    char ch = 'a';
    string s = "hello";
    //访问下表只能是常量
    tuple<int, double, char, string> mytuple(d, dou, ch, s);
    auto data = get<0>(mytuple);
    cout << data << endl;
    cout<< typeid(data).name()<<endl;
}
int main(){
    main3();
    return 0;
}