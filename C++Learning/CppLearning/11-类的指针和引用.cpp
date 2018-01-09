//
// Created by wenshao on 17-12-30.
//

#include <iostream>
using namespace std;


void dt(...);
class myclass{
public:
    int x;
    int y;
public:
    myclass(int a,int b):x(a),y(b){

    }
    void printxt();
};
void myclass::printxt() {
    cout<<x<<" "<<y<<endl;
}
void main1(){
    myclass *p1(new myclass(21,11));
    p1->printxt();
    myclass p2(199,888);
    p2.printxt();
    myclass **pp(&p1);//二级指针存储一级指针的地址
    (*pp)->printxt();
    (**pp).printxt();

}
int main2(){
    unsigned int i=1;
    unsigned char c='c';
    float f=1.2;
    unsigned long int e=22;
    const char *p;
    p="hsidhi";
    const double d=2222;
    cout<<"hello";
    return 0;
}

class A{
    int i=0;
public:
    virtual void show(){
        cout<<"i am A"<<endl;
    }

public:
    static void test1(){
        cout<<"test1";
    }
    static void test2(){
        test1();
        cout<<"test2";
    }
};
class B:public A{
public:
    virtual void show(){
        cout<<"i am B"<<endl;
    }
};

void test(A* a){
    a->show();
}
void ttt(int ,char,float){

}

int func(int x,int y){
    return x+y;
}
int main222222222(){
    B *b=new B;
    test(b);
    int a=1;
    switch(a){
        case 1:
            cout<<"1"<<endl;
        case 2:
            cout<<"2"<<endl;
        default:
            cout<<"default"<<endl;

    }
    return 0;
}

int main(){
    int *p=0;
    delete p;
    cout<<"hello";
    return 0;
}