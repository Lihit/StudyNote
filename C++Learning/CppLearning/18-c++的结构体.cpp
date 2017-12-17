//
// Created by wenshao on 2017/12/17.
//

#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
#include <assert.h>
using namespace std;

//c++的结构体可以在一开始赋值
struct test{
    int num=10;
};
//匿名结构体
struct {
    int num;//不允许初始化
}sx,sy;
//不允许结构体内部使用自己
//但是可以使用指针

void main1(){
    test t1;
    cout<<t1.num<<endl;
}
//空类占用一个字节，表明类的存在
//代码区不会占用字节
class kong{

};
void main2(){
    cout<<sizeof(kong)<<endl;
}
int main(){
    main2();
    return 0;
}