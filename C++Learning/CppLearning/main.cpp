#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct MyStruct {
    string str1, str2, str3;
    double db;
    int num;
    char ch;
};

/**
 * istringstream
 */
void main1() {
    string mystring("china-google-microsoft-12.9-123-A");
    replace(mystring.begin(),mystring.end(),'-',' ');
    //mystring.replace(mystring.begin(),mystring.end(),'-',' ');
    cout<<mystring<<endl;
    MyStruct mys1;
    istringstream ss(mystring);
    ss >> mys1.str1  >> mys1.str2  >> mys1.str3  >> mys1.db  >> mys1.num  >> mys1.ch;
    cout << mys1.str1 <<endl;
}

void main2(){
    ostringstream myout;
    char str[100]="sdhasudh";
    myout<<"sda"<<123<<234.22<<'h'<<str;
    cout<<myout.str()<<endl;
    myout.str().copy(str,myout.str().size());
    cout<<str<<endl;
}
int main() {
    main1();
    return 0;
}