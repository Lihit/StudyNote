//
// Created by wenshao on 2017/12/10.
//

#include <iostream>
#include <functional>
#include <array>
#include <algorithm>

using namespace std;

/**
 * 去掉转义字符
 */
void main1(){
    //可以去掉转义字符
    string path=R"(C:\Program Files\Sublime Text 3\sublime_text.exe")";
    system(path.c_str());
}
/**
 * 别名
 * @return
 */
int add(int a,int b){
    return a+b;
}
//using 只用用于简写数据类型
typedef int(*p)(int a,int b);
using FUNC=int(*)(int a,int b);
void main2(){
    p func=add;
    int ret=func(10,11);
    cout<<ret<<endl;
    FUNC func2=add;
    int ret2=func2(10,11);
    cout<<ret2<<endl;
}
int main(){
    main2();
    return 0;
}