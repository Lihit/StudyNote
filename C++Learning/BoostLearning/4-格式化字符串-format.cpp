#include <iostream>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

/**
 * format的基本使用
 */
void main41(){
    cout<<format("%2.3f,%d")%1.2334%12<<endl;
    cout << format( "%1%, %2%, %1%" ) % 1.23456 % 12 << endl;
    format fmt( "%1%, %2%" );
    fmt % 1.23456;
    fmt % 12;
    cout << fmt << endl;
}

/**
 * 产生字符串
 */
void main42(){
    string s=str(format("%s")%"hello world!");
    cout<<s<<endl;
}

int main_test4(){
    main42();
    return 0;
}