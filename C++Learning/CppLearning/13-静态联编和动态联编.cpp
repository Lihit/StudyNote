//
// Created by wenshao on 18-1-1.
//

#include <iostream>
using namespace std;

//多态是指一个名字，多种语义；或是界面相同，多种实现
//重载函数是多态性的一种简单形式
//虚函数允许函数调用与函数体的；联系再运行时才进行成为动态联编
//编译的时候确定的叫做静态联编
class A{
public:
    void go(){
        cout<<"A::nothing"<<endl;
    }
    void go(int num){
        cout<<"num"<<endl;
    }
    void go(char *str){
        cout<<"str"<<endl;
    }
};
class B:public A{
public:
    //派生类重写基类的重载函数会全部覆盖掉
    void go(){
        cout<<"B::nothing"<<endl;
    }
    void go() const{
        cout<<"B::nothing const"<<endl;
    }
};
//父类和子类之间的重载，同名函数会覆盖
//即使这个参数的类型不一样，不能直接调用，必须调用父类默认生成的对象来调用
void main1(){
    //类内的重载还包括const和非const的重载
    B* b=new B;
    b->go();
    const B*bnew=new B;
    bnew->go();
}
//静态联编可以根据三种方式区分
//１.根据参数的特征加以区分
//２.使用::加以区分
//３.根据类对象加以区分
int main(){
    main1();
    return 0;
}