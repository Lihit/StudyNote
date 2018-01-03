//
// Created by wenshao on 2018/1/3.
//

#include <iostream>
//类模板的成员函数没有实例化，不会自动找到，需要手动添加
using namespace std;
//抽象类也可以实现继承
//仅有一个指针指向虚函数表
//一个或者多个虚函数，或者多个纯虚函数都占四个字节
//一个指针存储了虚函数表的地址
class basebase{
public:
    virtual void show()=0;
    virtual void hide()=0;
    int xx;
    int yy;
};
class base:public basebase{
public:
    int x,y;
    virtual void show(){

    }
    virtual void hide(){

    }
};
void main1(){
    cout<< sizeof(base)<<endl;
    cout<< sizeof(basebase)<<endl;
}
//定义两种数据类型的类模板
//STL 数据结构 算法 适合任何类型
template <class T1,class T2>
class myclass{
public:
    T1 t1;
    T2 t2;
    myclass(T1 t11,T2 t22):t1(t11),t2(t22){

    }
    void print(){
        cout<<t1<<" "<<t2<<endl;
    }
};
template <class T,int n>//n可以在类中被使用，但是不能被修改，不是类的成员
class temp{
public:
    T* myarray;
    temp(){
        myarray=new T[n];
    }
};
int main(){
    main1();
    return 0;
}