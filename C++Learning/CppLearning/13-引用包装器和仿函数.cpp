//
// Created by wenshao on 2017/12/10.
//

#include <iostream>
#include <functional>
#include <array>
#include <algorithm>

using namespace std;
using namespace std::placeholders;
/*
 * 引用包装器
 */
template <typename T>//模板函数 引用无效 引用包装器
void com(T arg){
    arg++;
}
void main1(){
    int count=10;
    int &rcount=count;
    com(count);
    cout<<count<<endl;
    com(rcount);
    cout<<rcount<<endl;
    //ref(变量）函数模板直接引用
    //引用包装器
    com(ref(count));
    cout<<count<<endl;
}

/*
 * 引用内部函数绑定机制
 */
//仿函数 创建一个函数指针 引用一个结构体或是类的内部函数
struct MyStruct{
    void add(int a){
        cout<<a<<endl;
    }
    void add2(int a,int b){
        cout<<a+b<<endl;
    }
};
void main2(){
    MyStruct struct1;
    auto func=bind(&MyStruct::add,&struct1,_1);
    func(100);
    auto func2=bind(&MyStruct::add2,&struct1,_1,_2);
    func2(100,200);
}

void main3(){
    MyStruct s1;
    //创建函数指针 类结构体 数据私有 代码共享
    //函数通过调用 调用需要传递对象名进行区分
    void(MyStruct::*p)(int a)=&MyStruct::add;
    p(100);
}
int main(){
    main3();
    return 0;
}