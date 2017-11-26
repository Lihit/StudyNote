#include <iostream>

using namespace std;

void main1(){
    const int num=5;
    int array[num]={0};
    int *p=(int*)&num;//可以编译通过，但是禁止执行
    *p=10;
    cout<<num<<endl;
    int *p1= const_cast<int *>(&num);//可以去掉const 属性，但是还是修改不了
    *p1=111;
    cout<<num<<endl;

}
void main2(){
    int a=10;
    const int  b=20;
    int const *p1(&a);//限定权限
    const int *p2(&b);
    int * const p11(&a);
    //int * const p22(&b);//类型不匹配

    const int *const p111(&a);
    const int *const p222(&b);

}

//c++权限问题和强类型
//因为为了权限的编程，只读不可写的权限，int const *p1,c++强类型会忽略
//给予可读可写的权限 int *const p//const int 强类型会发生作用
//const int * const p;给予只读的权限

void main3(){
    const int num=100;
    const int &rnum=num;
    cout<<&num<<endl;
    cout<<&rnum<<endl;
}
int main(){
    main3();
    return 0;
}