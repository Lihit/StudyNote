//
// Created by wenshao on 18-1-2.
//

#include <iostream>

using namespace std;
//虚函数本质是一个函数指针

class fu {
public:
    //虚函数占据四个字节的地址
    void name() {//虚函数实际上是一个函数指针，自动调用传进来对象的函数覆盖虚函数
        cout << "fu" << endl;
        cout << "x=" << x << endl;
    }

    int x;

    fu(int a) : x(a) {

    }
};

class zi : public fu {
public:
    void name() {
        cout << "zi" << endl;
        cout << "x=" << x << ";y=" << y << endl;
    }

    int y;

    zi(int a, int b) : fu(a), y(b) {

    }
};

class sun : public zi {
public:
    void name() {
        cout << "sun" << endl;
        cout << "x=" << x << ";y=" << y << ";z=" << z << endl;
    }

    int z;

    sun(int a, int b, int c) : zi(a, b), z(c) {

    }
};

void main1() {
    fu *pfu = new fu(10);
    pfu->name();
    zi *pzi = static_cast<zi *>(pfu);
    pzi->name();
    sun *psun = static_cast<sun *>(pfu);
    psun->name();
}

void main2() {
    cout << sizeof(fu) << endl;
    fu fu1(1);
    zi zi1(2, 3);
    sun sun1(4, 5, 6);
    fu *pfu;
    pfu = &fu1;
    pfu->name();
    pfu = &zi1;
    pfu->name();
    pfu = &sun1;
    pfu->name();
    ((sun *) pfu)->name();
    ((zi *) pfu)->name();
}
//构造函数不可以是虚函数,不可以再构造
//但是析构函数可以加virtual
//可以防止内存泄露
class A{
public:
    A(){
        cout<<"create A"<<endl;
    }
    virtual ~A(){
        cout<<"delete A"<<endl;
    }
};
class B:public A{
public:
    B(){//B创建的时候会自动调用Ａ的构造函数
        cout<<"create B"<<endl;
    }
    ~B(){//Ｂ析构的时候会自动调用Ａ的析构函数
        cout<<"delete B"<<endl;
    }
};
void main3(){
//    A* a=new A;
//    delete a;
//    B* b=new B;
//    delete b;

//    A* a1=new B;
//    delete a1;//加上了virtual可以防止内存泄露
    B* b=new B;
    delete b;

}
//在派生类中重载基类的虚函数要求函数名，返回类型，参数个数，参数类型和顺序完全相同
int main() {
    main3();
    return 0;
}