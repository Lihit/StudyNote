#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void main1() {
    auto func1 = []() { cout << "hello world!" << endl; };
    func1();
    auto func2 = [](int a, int b) { return a + b; };
    cout << func2(1, 2) << endl;
}

void main2() {
    vector<int> v = {1, 2, 3};
    auto func1 = [](int v) { cout << v << endl; };
    for_each(v.begin(), v.end(), [](int v) { cout << v << endl; });
    for_each(v.begin(), v.end(), func1);


    int a = 10;
    //加上等号知道a的存在，可以引用,只能读不能写
    auto func2 = [=](int v) {
        v += a;
        cout << v << endl;/* a=10;*/};
    for_each(v.begin(), v.end(), func2);

}

void main3() {
    vector<int> v = {1, 2, 3};

    int a = 10;
    //需要传入引用才能写
    auto func2 = [&a](int v) {
        v += a;
        cout << v << endl;
        a = 10;
    };
    for_each(v.begin(), v.end(), func2);
    cout << a << endl;

}

class test {
public:
    int num;
    vector<int> myv;
public:
    test() {
        num = 10;
        myv = {1, 2, 3};
    }

    void add(int y) {
        auto func1 = [this](int v) {
            v += this->num;
            cout << v << endl;
        };
        for_each(myv.begin(), myv.end(), func1);

        /*************************/
        int x = 3;
        auto func2 = [this, x, y](int v) {
            v += this->num + x + y;
            cout << v << endl;
        };
        for_each(myv.begin(), myv.end(), func2);

        /*************************/
        //也可以只使用一个&，这样就可以获取所有的局部变量和this了
        int i=0;
        auto func3 = [&](int v) {
            v += this->num + x + y;
            cout << v << endl;
            this->myv[i++]=v;
        };
        for_each(myv.begin(), myv.end(), func3);
        //=按照副本引用this，还有当前块语句局部变量，不可以复制名单是可以读取
        //&可以赋值，也可以读取
    }

    void printV() {
        for_each(myv.begin(), myv.end(), [](int v) { cout << v << endl; });
    }
};
void main4() {
    test t;
    t.add(11);
    t.printV();
}
/**
 * lambda的返回值
 */
void main5(){
    auto fun1=[]()->double{cout<<"hello world"<<endl;return 1;};
    cout<<fun1();
    auto fun2=[](int a, double b)-> decltype(a/b){cout<<"hello world"<<endl;return 1;};
    cout<<fun2(1,2);
}

void main6(){
    int a=10;
    auto fun1=[a](int v)mutable{v+=a;cout<<v<<endl;a=1;};
    fun1(12);
    cout<<a<<endl;
}
int main_test1() {
/*    []() { cout << "hello world!" << endl; };//是一个函数指针
    []() { cout << "hello world!" << endl; }();//调用函数*/
    main6();
    return 0;
}