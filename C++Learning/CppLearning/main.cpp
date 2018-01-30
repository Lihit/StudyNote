#include <iostream>
<<<<<<< HEAD
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
=======
//类模板的成员函数没有实例化，不会自动找到他，需要手动包含

using namespace std;
//类模板可以有默认值
//但是需要加上<>

//编译系统检查出来的语法错误，导致程序运行结果不正确的逻辑错误，都不属于异常的范围
//异常是指一个可以正确运行的程序再运行中可能会发生的错误

//标识错误的类型
class wrong{

};
//Ｃ语言的异常
int intdiv(int a,int b){
    try {
        if(b==0){
            throw wrong();
        }
        else if(b==10){
            throw "b==10是不对的";
        }
        return a/b;
    }catch (wrong){
        cout<<"除法异常已经处理"<<endl;
        return -1;
    }catch (const char * e){
        cout<<e<<endl;
    }
}
//面向对象的异常
class myArray{
public:
    int *p;
    myArray(int num){
        p=new int[num];
        if(num<0){
            throw wrong();
        }
        for (int i = 0; i <num ; ++i) {
            p[i]=0;
        }
    }
};
int main1(){
    try{
        myArray ma(-10);
    }catch (wrong){
        cout<<"数组长度应该大于０"<<endl;
    }
}
>>>>>>> e8dc5dcdc524676ecd48f38c553aff68985a1bba
int main(){
    int ret=intdiv(10,10);
    return 0;
}