//
// Created by wenshao on 2017/12/10.
//

#include <iostream>
#include <functional>
#include <array>
#include <algorithm>

using namespace std;
//递归实现起来比较简单
//但是算起来效率不高

//模板元
//把运行时消耗的资源，在编译的区间进行优化

template <int N>
struct data{
    enum {res=data<N-1>::res+data<N-2>::res};
};
template <>
struct data<1>{
    enum {res=1};
};
template <>
struct data<2>{
    enum {res=2};
};
void main1(){
    int num=data<45>::res;
    cout<<num<<endl;
}
int main(){
    main1();
    return 0;
}