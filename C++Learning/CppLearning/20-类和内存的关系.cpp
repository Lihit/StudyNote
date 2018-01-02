//
// Created by wenshao on 2017/12/20.
//
#include<iostream>

class myclass
{
public:
    int num;
    int data;
    int *p;
    const int coint;
    int & myint;
    static int shu;//声明
    static const int dashu;

public:
    static void go()
    {

    }

    void run()
    {

    }
//常量，引用，必须重载构造函数初始化，
    myclass(int a, int b) :myint(a), coint(b)
    {
        //引用就是共用地址，常量新开辟备份机制
        std::cout << &a << "  " << &b << std::endl;
        std::cout << &myint << "  " << &coint << std::endl;

        const int *p = &coint;//地址
        std::cout << *p << "   " << coint << std::endl;
        int *px = const_cast<int *>(p);//去掉const转换
        *px = 12;
        std::cout << coint << "  " << *px << std::endl;

    }
    ~myclass()
    {

    }

};
int myclass::shu = 0;//初始化
const int myclass::dashu = 20;//常量

int  main()
{
    myclass m1(100,29);
    const int *px = &(myclass::dashu);
    std::cout << px << std::endl;
    int *p = const_cast<int *> (px);
    //*p = 123;//静态常量区可以访问，不可以修改，
    std::cout << *px << "  " << *p << "   " << myclass::dashu;

    //std::cin.get();
    return 0;


}


class mywindowW
{

public:
    int  &num;//引用，必须在构造的初始化,
    //引用今天可以引用这个人，明天引用那个人


public:
    mywindowW(int data) :num(data)
    {

    }

};

int mainrr()
{
    int data = 20;//引用必须初始化，反复赋值，类中的引用必须在构造函数初始化
    mywindowW  my1(data);
    std::cout << my1.num; //加上endl关闭输出，当作地址，否则当作变量
    int dataA = 201;
    my1.num = dataA;
    std::cout << my1.num;//加上endl关闭输出，当作地址，否则当作变量
    std::cin.get();

    return 0;
}

int mainr()
{

    int data2 = 11;

    int  data1 = 22;//引用必须初始化，反复赋值，
    int & da = data1;
    std::cout << da<< std::endl;
    da = data2;
    std::cout << da<<std::endl;

    std::cin.get();
    return 0;
}

class mywindowWW
{

public:

    const int num;

public:
    mywindowWW(int data) :num(data)
    {

    }

};
void mainconst()
{
    int int1 = 20;
    mywindowWW  mywindowWW1(int1);//初始化,常量必须构造的时候初始化
    //类的外部一旦初始化以后，不会读内存，从代码区的符号表自动生成，
    std::cout << mywindowWW1.num << std::endl;

    //mywindowWW1.num = 19;//mywindowWW1”: 不能给常量赋值


    std::cin.get();
}



void main2312312()
{
    //类中的普通成员变量
    //类名 变量名  //栈上
    //类名 *指针名 =new  类名   //堆上
    //类的静态成员  静态区
    //成员函数，静态函数都在代码区，类的函数都是共享
    //myclass myclass1(10, 9);
    //int a(5);

    //void(myclass::*p1)() = &myclass::run;
    //代码共享，所有的类对象共享对象，
    //void(*p2)() = &myclass::go;//静态函数，与对象没有关系


    //引用本质就是变量的别名，4个字节，本质是一个指针

    myclass myclass1(10, 9);

    //static const int dashu; 静态区，修改
    //

    //int a;
    //int &ra;



    std::cin.get();

}
