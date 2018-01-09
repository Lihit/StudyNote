//
// Created by wenshao on 17-12-31.
//

#include <iostream>
using namespace std;

//类对象的类型转换有两种方式：
//构造函数和转换函数
class fushu{
private:
    int x;
    int y;
public:
    explicit fushu(int num){//explicit可以避免隐式转换引发歧义
        x=y=num;
        cout<<"我是构造函数"<<endl;
    }
    void print(){
        cout<<x<<"+"<<y<<"i"<<endl;
    }
    //不支持友元函数
    //只支持成员函数
    operator int(){//类与类之间的转换
        return x+y;
    }
    operator float();
};
fushu::operator float(){
    return x-y;
}
//转换有赋值和括号
void main1(){
    //int num=10.7;
    //隐式转换和显示转换
    fushu f=(fushu)10;//显示类型转换
    f.print();
    int data=f;
    cout<<data<<endl;
    float md=f;
    cout<<md<<endl;
}

//类型转换函数
void main2(){
    int num=100;
    fushu f1(num);
    f1.print();
    int data=(int)f1+10;
    cout<<data<<endl;
}

//类与类之间的类型转换
class test1{
public:
    int x;
    int y;
public:
    test1(){
        this->x=0;
        this->y=0;
    }
};
class mianji{
public:
    friend class test1;
private:
    int cx;
    int cy;
public:
    mianji(){
        this->cx=0;
        this->cy=0;
    }
    mianji(test1 t1){
        this->cx=t1.x;
        this->cy=t1.y;
    }
    operator test1(){
        test1 temp;
        temp.x=cx+100;
        temp.y=cy;
        return temp;
    }
};
void main3(){
    test1 t1;
    mianji m1=t1;
    test1 t2;
    t2=m1;
}
int main(){
    main3();
    return 0;
}