//
// Created by wenshao on 2017/12/9.
//


#include <iostream>
#include <functional>

using namespace std;

//通用可变参数模板
void showall(){}//空函数 接口 最后结束递归时调用
template <typename T,typename... Args>
void showall(const T &value,const Args &... args){
    cout<<value<<endl;
    showall(args...);
};
void main1(){
    int num1=12,num2=1,num3=111;
    double db1=12.1,db2=11.1;
    char str[40]="hello";
    char ch='c';
    showall(num1);
    showall(num1,db1);
    showall(db2,str);
    showall(ch,str,num1,db1);
}
int main(){
    main1();
    return 0;
}