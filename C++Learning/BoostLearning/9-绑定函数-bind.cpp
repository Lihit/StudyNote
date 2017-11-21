#include <iostream>
#include <boost/bind.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace boost;

int f(int a, int b) { return a + b; }   //二元函数
int g(int a, int b, int c) { return a + b + c; } //三元函数
typedef int (*f_type)(int, int);      //函数指针定义
typedef int (*g_type)(int, int, int); //函数指针定义

/**
 * bind的简单使用
 */
void main1() {
    cout << bind(f, 1, 1)() << endl;
    cout << bind(f, _1, _2)(10, 10) << endl;
    cout << bind(g, 10, _2, _1)(11, 1) << endl;
}

/**
 * bind绑定成员变量
 */
void main2() {
    typedef pair<int, string> pair_t;
    pair_t p(12, "hello");
    cout << bind(&pair_t::first, p)() << endl;
    cout << bind(&pair_t::second, p)() << endl;

}

/**
 * 绑定函数对象
 */
void main3() {
    cout << (bind(greater<int>(), _1, 10)(20) ? "true" : "false") << endl;
    cout << (bind(plus<int>(), _1, _2)(12, 11)) << endl;
    cout << (bind(modulus<int>(), _1, 3)(10)) << endl;
}

/*bind采用拷贝的方式保存绑定对象和参数，这意味着绑定表达式中的每一个变量都会有一份拷贝，
如果函数对象或值参数很大、拷贝代价很高，或者无法拷贝，那么bind的使用就会受到限制。
因此bind库可以搭配ref库使用，ref库包装了对象的引用，可以让bind存储对象引用的拷贝，
从而降低了拷贝的代价。但这也带来了一个隐患，因为有时候bind的调用可能会延后很久，
程序员必须保证bind被调用时引用是有效的。如果调用是引用的变量或者函数对象你被销毁了，那么将会发生未定义行为。*/


/**
 * 绑定非标准函数
 */
void main4() {
    int x=6,y=7;
    bind<int>(printf,"%d+%d=%d\n",_1,_2,_3)(x,y,x+y);
}

int main_test9() {
    main4();
    return 0;
}