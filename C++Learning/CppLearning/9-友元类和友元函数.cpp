//
// Created by wenshao on 17-12-29.
//

#include <iostream>
using namespace std;
//如果已经生命并定义了，那么不会再用默认的
class A{
public:
    A(){};
    A(const A &obj);//只有声明，编译器会自动生成
    A(int a);
};
void main1(){
    A a;//编译器会生成默认的构造函数
    //A b(a);//编译器会生成默认的拷贝构造函数
    //A c(2);
}
//ｄｅｌｅｔｅ可以禁用默认生成函数，禁用构造无法实例化
//禁用拷贝构造，可以禁止别人拷贝你的值
//ｄｅｆａｕｌｔ默认存在

//友元函数
class B{
private:
    int b;
    friend void showb(B * pB);//友元函数可以访问类的私有变量
    //友元函数声明有ｆｒｉｅｎｄ，定义就不需要
    //或者定义再内部
public:
    //B()= delete;//默认删除构造函数，无法实例化
    B(){
        b=100;
    };//默认存在

};
void showb(B * pB){
    cout<<pB->b<<endl;
}
void main3(){
    B btmp;
    showb(&btmp);
}



//友元类
class window{

};
int main(){
    main3();
    return 0;
}