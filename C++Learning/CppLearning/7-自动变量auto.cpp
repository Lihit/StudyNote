#include <iostream>
#include <typeinfo>
#include <cstdarg>
#include <vector>
#include <algorithm>

using namespace std;

//自动变量，自动获取类型，输出，泛型
//自动变量，可以实现自动循环一维数组
//自动变量类型
void main1() {
    auto num1 = 10;
    auto num2 = 20 / 2.4;//通用的传入接口
    cout << num1 << '\t' << num2 << endl;
    cout << typeid(num2).name() << endl;
    decltype(num1) numA = 11;//通用的备份借口
    cout << numA << endl;
}

void main2() {
    int num[3] = {1, 2, 3};
    int n[2][3] = {{1, 2, 3},
                   {4, 5, 6}};
    //二维数组无法用ａｕｔｏ来遍历
    for (auto i:num) {
        cout << i << endl;
    }
    for (auto i:n) {
        for (int j = 0; j < 3; j++) {
            cout << *(j + i) << endl;
        }
    }
}

template<typename T>
T getMax(T *p, const int n) {
    T maxNum = p[0];
    for (int i = 1; i < n; ++i) {
        if (p[i] > maxNum) {
            maxNum = p[i];
        }
    }
    return maxNum;
}

template<typename T>
T sum(int n, int b, ...) {//累加
    va_list arg_ptr;//参数列表的指针
    va_start(arg_ptr, n);//限定从ｃｏｎｓｔ开始，限定多少个参数
    T sumret = 0;
    for (int i = 0; i < n; ++i) {
        sumret += va_arg(arg_ptr, T);
    }
    va_end(arg_ptr);
    return sumret;
}

template<typename T>
vector<T> getV(int n, ...) {//累加
    va_list arg_ptr;//参数列表的指针
    va_start(arg_ptr, n);//限定从ｃｏｎｓｔ开始，限定多少个参数
    vector<T> ret;
    for (int i = 0; i < n; ++i) {
        ret.push_back(va_arg(arg_ptr, T));
    }
    va_end(arg_ptr);
    return ret;
}

void main3() {
    vector<int> ret = getV<int>(3, 11, 22, 33);
    for_each(ret.begin(), ret.end(), [](int v) { cout << v << endl; });
}

//根据实际自动发推导出类型
//函数参数不允许使用自变量auto
template<class T1, class T2>
auto get(T1 data1, T2 data2) -> decltype(data1 * data2) {
    return data1 * data2;
}

void main4() {
    cout << typeid(get<double, char>(12.0, 'a')).name() << endl;
    cout<<get<double, char>(12.0, 'a')<<endl;

}

int main() {
    main4();
    return 0;
}