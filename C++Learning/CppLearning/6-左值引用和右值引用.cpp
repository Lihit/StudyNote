#include <iostream>

using namespace std;

//左值是可以放在赋值号左边被复制的值，必须在内存里边有实体
//右值放在赋值号右边取出值付给其他变量的值，可以在内存也可以再ｃｐｕ
void main1() {
    int a = 5;
    int &ra(a);
    ra = 100;
    cout << a << endl;
    cout << ra << endl;
}

//左值引用使用指针实现的
void main2() {
    int num1(22);
    int num2(11);
    int *pnum(&num1);
    int &rnum(num2);
    int *&rpnum(pnum);
    rpnum = &num2;//引用可以改变指针的指向
    *rpnum = 1000;
    cout << *pnum << endl;
    cout << num1 << endl;

}

void main3() {
    int num1(22);
    int num2(11);
    int *p;
    p = &num1;//取地址是在寄存器
    p = &num2;
    int *&&rpnum = &num1;//引用右值
    p = rpnum;//用于对象拷贝
}

int &get() {
    int a = 10;//a再栈上
    int &ra = a;
    return ra;
}

void main4() {
    int &a = get();
    cout << a << endl;
    cout << "hello" << endl;
    cout << a << endl;

}

int *&getdata() {
    int *p = new int(10);
    int *&rp(p);
    return rp;
}

void main5() {
    int *&rp = getdata();
    int *p=rp;
    cout<<*rp<<endl;
    cout<<*p<<endl;
    cout << "hello" << endl;
    cout<<*rp<<endl;
    cout<<*p<<endl;
    delete(p);//c++删除内存后，禁止访问
    cout<<p<<endl;
    cout<<*p<<endl;
}

int main() {
    int (*p)[10] = new int[5][10];
    p[1][1]=1000;
    for(int i=0;i<5;i++){
        for (int j = 0; j < 10; ++j) {
            cout<<p[i][j]<<endl;
        }
    }
    //main5();
    return 0;
}