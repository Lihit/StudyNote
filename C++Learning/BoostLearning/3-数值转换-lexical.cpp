#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;
using namespace boost::filesystem;
/**
 * 字符串变数值
 */
void main31(){

    string s="100";
    int tmp=lexical_cast<int>(s);
    cout<<tmp<<endl;
    string s1="100.11";
    float tmp1=lexical_cast<float>(s1);
    cout<<tmp1<<endl;
    //为了防止类型转换错误 应该使用try
    try {
        string s2="10d0";
        int tmp2=lexical_cast<int>(s2);
        cout<<tmp2<<endl;
    }
    catch (bad_lexical_cast &e){
        printf("%s",e.what());
    }

}
/**
 * 数值变字符串
 */
void main32(){
    double tmp=1.222;
    try {
        string s=lexical_cast<string>(tmp);
        cout<<s<<endl;
        //printf("%s",str(tmp));
    }
    catch (bad_lexical_cast &e){
        cout<<e.what()<<endl;
    }
}
int main_test3(){
    main32();
    return 0;
}