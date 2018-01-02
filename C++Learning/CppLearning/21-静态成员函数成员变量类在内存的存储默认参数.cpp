//
// Created by wenshao on 2017/12/25.
//

#include <iostream>
using namespace std;

class myclass{
public:
    int num;
    int data;
    int *p;
    const int coint;
    int &myint;//引用必须在构造的时候初始化
    static int shu;//声明
    static const int dashu;//声明
public:
    //const一旦初始化，不会读内存，从代码区的符号表自动生成
    myclass(int a,int b):coint(a),myint(b){
        //引用是公用地址 常量是开辟备份机制
        cout<<&a<<" "<<&b<<endl;
        cout<<&coint<<" "<<&myint<<endl;
        const int*p=&coint;
        int *px= const_cast<int *>(p);
        *px=100;
        cout<<coint<<" "<<*px<<endl;
    }
    static void go(){

    }
    void run(){

    }
};
int myclass::shu=100;//初始化
const int myclass::dashu=200;//是一个常量，不可以被修改
//引用必须初始化，反复赋值，类中的引用必须在构造函数时初始化
void main1(){
    //类中的普通成员变量
    //类名 变量名 在栈上
    //类名 *指针名 =new 类名 //堆上
    //函数都在代码区 类的函数都是共享的
    myclass mc(10,29);

    void (myclass::*p1)()=&myclass::run;//代码共享 所有的类对象共享代码
    void (*p2)()=&myclass::go;//代码共享 所有的类对象共享代码

}

void main2(){
    //类的外部，一开始必须初始化，用常量强行替换，不读内存
    //类的内部，必须构建一个类才能初始化，const和C语言一样

    myclass mc(10,29);
    //static const int dashu;在静态区  引用的时候不读内存
}

void main3(){
    const int *px=&(myclass::dashu);
    int *p= const_cast<int *>(px);
    *p=1000;//静态常量区可以访问，但是不可以被修改
    cout<<*px<<" "<<*p<<endl;
}

//默认参数
class goodclass{
public:
    int num=1;//默认初始化的值，c++11新特性
    const int data=20;//可以少写构造函数
public:
    void show(){
        cout<<num<<" "<<data<<endl;
    }
};
//类中的const默认还是可以被修改的，与C语言const一致
void main4(){
    goodclass gc;
    const int *px=&(gc.data);
    int *p= const_cast<int *>(px);
    cout<<gc.data<<" "<<*px<<" "<<*p<<endl;
    *p=1000;//静态常量区可以访问，但是不可以被修改
    cout<<gc.data<<" "<<*px<<" "<<*p<<endl;
}
int main(){
    main4();
    return 0;
}