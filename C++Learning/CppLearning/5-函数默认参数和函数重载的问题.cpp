#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

void go(int a){
    cout<<a<<endl;
}
void go(double a){
    cout<<a<<endl;
}
void go(int a, double b){
    cout<<a<<" "<<b<<endl;
}
void main1(){
    void(*p1)(int a)=go;
    void(*p2)(double a)=go;
    void(*p3)(int b, double a)=go;
    printf("%p\n",p1);
    printf("%p\n",p2);
    printf("%p\n",p3);

}
//默认参数一定要放在右边，不然会报错
void print(int a,int b=1,int c=2){
    cout<<a<<b<<c<<endl;
}
void print(int a){
    cout<<a<<endl;
}
void main2(){
    //上边两个函数如果直接调用print(1)会报错
    //print(1);//发生函数重载
    //正确的做法是利用函数指针
    //函数指针没有默认参数
    //函数重载和函数默认参数冲突,一定会报错
    void (*pt1)(int a,int b,int c)=print;
    pt1(110,1,1);
}

int main(){
    main2();
    return 0;
}