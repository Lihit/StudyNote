//
// Created by wenshao on 18-1-2.
//

#include <iostream>
using namespace std;

//纯虚函数死一个可以在基类中说明的虚函数，在基类没有定义，要求任何派生类都可以定义自己自己的版本
//纯虚函数为各个派生类提供一个公共的界面
//一个具有纯虚函数的类叫做抽象类　
//无法实例化抽象类
class base{
public:
    virtual void show()=0;
    //纯虚函数可以有实现也可以没有实现
    virtual void go(){//但是这样就不是纯虚函数了
        cout<<"go"<<endl;
    }
};

class run:public base{
public:
    virtual void show(){
        cout<<"hello"<<endl;
    }
};
void main1(){
    //抽象类无法实例化，但是可以实例化指针
    base *bs;
    //纯虚函数和抽象类与虚函数起到了接口的作用
    //用同一个接口完成不同的功能
    //纯虚函数完全是为了接口的存在

}
//抽象类也可以实现继承
int main(){
    main1();
    return 0;
}