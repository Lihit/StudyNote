//
// Created by wenshao on 2017/12/20.
//

#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
#include <assert.h>
#include <array>
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

//所有的类默认都有一个构造函数和析构函数
//构造函数和析构函数都可以重载
//没有返回值
class myclass{
public:
    int num;//有两种初始化方式
public:
    myclass():num(19){
        //num=10;
        cout<<"create class:myclass()"<<endl;
    }
    myclass(int data){//构造函数可以重载
        cout<<"create class:myclass(int data)"<<endl;
        num=data;
    }
    ~myclass(){
        cout<<"delete class"<<endl;
    }
};
void main2(){
    myclass my1(102);
    myclass my=100;
    myclass *myptr=new myclass(199);
    myclass *myptr2(new myclass(199));
}

//系统会自动生成构造函数和析构函数
class fushu{
public:
    fushu();
    fushu(int data);
    ~fushu();

public:
    int num;
};
fushu::fushu() {
    cout<<"create class:fushu()"<<endl;
}
fushu::fushu(int data) {
    num=data;
    cout<<"create class:fushu()"<<endl;
}
fushu::~fushu() {
    cout<<"delete class:~fushu()"<<endl;
}
//被包含的，最先分配，最后释放
class math{
public:
    math():fushu1(100),my1(10000){
        cout<<fushu1.num<<endl;
        cout<<my1.num<<endl;
        cout<<"create class:math()"<<endl;
    }
    ~math(){
        cout<<"delete class:math()"<<endl;
    }

public:
    myclass my1;
    fushu fushu1;

};

void main3(){
    math math1;
}
class classsobj{
public:
    int num;
public:
    explicit classsobj(int data){//explict可以强制类调用时必须是显示调用
        num=data;
        cout<<"create class:classsobj()"<<endl;
    }
    ~classsobj(){
        cout<<"delete class:classsobj()"<<endl;
    }
};

void main4(){
    classsobj c1(100);
    classsobj obj(0);//创建对象必须选择合适的构造函数
    classsobj *cobj=new classsobj(10);
    //但是创建数组会比较麻烦
    //需要用到c++风格的数组
    array<classsobj,10> myarray={c1,*cobj};
}
int main(){
    main4();
    return 0;
}