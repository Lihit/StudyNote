//
// Created by wenshao on 17-12-29.
//

#include <iostream>
using namespace std;

class Area{
public:
    const int x;
    const int y;
    mutable int z;
    int xy;
    Area(int a,int b):x(a),y(b){
        cout<<"我是构造函数"<<endl;
    }
    void printxy() const{
        cout<<x<<" "<<y<<" "<<z<<" "<<xy<<endl;
    }
    void setxy(int z) const{
        //int *pa= const_cast<int *>(&x);
        //*pa=1000;
        this->z=z;
    }
};
void main1(){
    //const对象本可以使用非ｃｏｎｓｔ函数
    const Area a(10,20);
    a.printxy();
    a.setxy(12);
    a.printxy();
}

//c++使用nullptr
//NULL实际上是等于０（ｃ语言风格）
void go(int num){
    cout<<"int"<<endl;
}
void go(void *p){
    cout<<"void *"<<endl;
}
void main2(){
    void *p=NULL;
    go(p);//根据c++的强类型处理会调用void*
    //go(NULL);造成歧义
    go(nullptr);//强类型处理会调用void*
    //nullptr是c++的空指针
}
int main(){
    main2();
    return 0;
}