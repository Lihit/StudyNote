//
// Created by wenshao on 2017/12/5.
//
#include <iostream>
#include <cstdlib>
#include <cstdio>
using  namespace std;

/**
 * 普通的类型转换
 */
void main1(){
    printf("%d\n",78.33);
    printf("%d\n", static_cast<int>(78.33));
    printf("%f\n", static_cast<float >(72));
    int *p= static_cast<int*>(malloc(100*sizeof(int)));
}
//const int num =0; 可以修改但是无法生效，编译的时候直接从符号表取值
//const int *p;指向变量只读不可写
//const_cast可以去掉常量指针属性
void main2(){
    int num[3]={1,2,3};
    const int *p=num;
    //会出错
    //*p=10;
    //*(p+1)=100;
    int *pnew= const_cast<int*>(p);
    *pnew=100;
    cout<<num[0]<<endl;
}
//指针是强类型 类型决定了数据的解析方式，内存大小等
void main3(){
    int num=3;
    char *p= reinterpret_cast<char*>(&num);
    for (int i = 0; i <4 ; ++i) {
        printf("%c,%d,%p\n",*(p+i),*(p+i),p+i);
    }
}
//dynamic_cast类指针的转换
int main(){
    main3();
    return 0;
}
