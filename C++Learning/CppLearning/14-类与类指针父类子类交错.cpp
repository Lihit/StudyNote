//
// Created by wenshao on 18-1-1.
//

#include <iostream>
using namespace std;

//dynamic_cast类和类之间的转换需要用到
class fu{
public:
    char *strp;
    fu(){
        cout<<"fu被构造了"<<endl;
        strp="fu";
    }
    void print(){
        cout<<"i am fu"<<endl;
    }
    void fufu(){
        cout<<strp<<endl;
    }
    ~fu(){
        cout<<"fu被析构了"<<endl;
    }
};
class zi:public fu{
public:
    char *strp1;
    zi(){
        cout<<"zi被构造了"<<endl;
        strp1="zi";
    }
    void print(){
        cout<<"i am zi"<<endl;
    }
    void zizi(){
        cout<<strp1<<endl;
    }
    ~zi(){
        cout<<"zi被析构了"<<endl;
    }
};
void main1(){
    //父类指针指向子类
    fu *fu1=new zi;
    //fu1->fufu();
    //fu1->print();
    //子类指针指向父类会报错,可以用static_cast转换
    //dynamic_cast使用与虚函数转换
    //zi *zi1=new fu;
    fu *fu2=new fu;
    zi* zi1= static_cast<zi*>(fu2);
    zi1->fu::print();
    zi1->print();
    zi1->fufu();
    zi1->zizi();
    //类的函数共享
    //引用了调用类的内部变量的函数无法执行
    //没有调用的话可以执行
    cout<<"hello"<<endl;
}
//父类指针引用父类对象，可以正常引用
//子类指针引用子类对象，覆盖父类的同名函数
//父类指针引用子类对象，只能引用父类的函数
//子类指针引用父类对象，子类不涉及内部数据的函数会调用成功
//设计内部数据的调用成功但是执行失败
//子类指针无法引用父类的同名方法


//类而言，数据是私有的，代码是共享的
//指针为空，指向一个类，可以直接调用方法
//设计内部成员会崩溃，不可以执行
void main2(){
    zi* z(nullptr);//空指针
    z->print();

}

//delete
void main3(){
    {
        //fu *pfu=new fu;
        //delete pfu;
    }
    {
        //zi *pzi=new zi;
        //delete pzi;
    }
    {
        //fu *pfu=new zi;
        //delete pfu;//会出现内存泄露，zi类没有被析构
    }
    {
        zi *pzi= static_cast<zi*>(new fu);
        delete pzi;//内存越界，有时出错
    }
}
int main(){
    main3();
    return 0;
}