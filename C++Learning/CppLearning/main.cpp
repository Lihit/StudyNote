#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
#include <assert.h>
using namespace std;
//union本质也是一个类 可以在内部有函数
//union 内部数据是共享的 不同对象之间是独立的 代码是共享
//某些节约内存的类可以使用union
//union不可以继承
void main1(){

}

//面向过程的模式
//代码重用主要靠函数
//权限的问题


//c++面向对象模式（数据和代码合为一体）
//类的继承实现了代码重用
//类的封装实现了权限
//类的多态实现一个接口根据需要完成多种功能
//封装可以实现代码的权限，不可以随便调用
//也可以锁定数据的权限，不可以被随便修改
int main(){
    main1();
    return 0;
}