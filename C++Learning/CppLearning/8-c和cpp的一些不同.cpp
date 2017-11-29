#include <iostream>
using namespace std;

//c++检测右值内存有实体，自动转换为左值
//c　语言不会把右值转为左值
//c++全局变量和静态全局变量没有声明和定义的区别
//c++是强类型系统　函数返回值必须有类型
int a;
//int a;
static int b;
void main1(){
    int a=3;
    (a=3)=4;
    cout<<a<<endl;
    int b=5;
    (++b)++;
    cout<<b<<endl;
    (a>b?a:b)=100;
    cout<<b<<endl;
    //c++的register可以取地址
    register int num=0;//寄存器的变量
    cout<<&num<<endl;
}
//c++编译器　变异的宽泛
//为了修改源代码　后面留下拓展
//站位　站位参数
void test(int a,double,int){

}
int main(){
    main1();
    return 0;
}