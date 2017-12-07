//
// Created by wenshao on 2017/12/5.
//

#include <iostream>
#include <functional>

using namespace std;

//函数包装器 T是数据类型 F是函数
//作用：
//第一，设计执行接口，接口设计关卡，计数
//第二，函数包装器依赖于函数模板适用于通用模型
//第三，函数代码可以嵌套在另外一个函数，实现代码增值
//函数包装器可以用于管理内嵌函数，外部函数调用
template <typename T,typename F>
T run(T v,F f){
    static int count=0;
    count++;
    cout<<"执行 "<<count<<endl;
    if(count>1){
        T vx(0);
        return vx;
    }
    return f(v);
};

int test(int d){
    return d+100;
}
void main1(){
    double db=12.9;
    function<double(double)> fun1=[](double u){return 2*u;};//c++的新语法
    cout<<run(db,fun1)<<endl;
    cout<<run(12,test)<<endl;
}
int main(){
    main1();
    return 0;
}