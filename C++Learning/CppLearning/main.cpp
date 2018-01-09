#include <iostream>
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
int main(){
    int ret=intdiv(10,10);
    return 0;
}