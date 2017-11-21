#include <iostream>
#include <boost/algorithm/string.hpp> //需要加上这个
#include <string>
#include <vector>

using namespace std;
using namespace boost;

/**
 * split
 */
void main1(){
    string s="test1,test2,test3";
    vector<string> v1;
    boost::algorithm::split(v1,s,boost::algorithm::is_any_of(","));
    for(int i=0;i<v1.size();i++){
        cout<<v1[i]<<endl;
    }
}
/**
 * join
 */
void main2(){
    vector<string> s={"test1","test2","test3"};
    cout<<boost::algorithm::join(s,"_")<<endl;
    string s1[]={"test1","test2","test3"};
    cout<<boost::algorithm::join(s1,"_")<<endl;
}

/**
 * 转换 case conversion
 */
void main3(){
    //大小写转换
    cout<<boost::algorithm::to_upper_copy(string("hello"))<<endl;
    cout<<boost::algorithm::to_lower_copy(string("hello"))<<endl;
}

/**
 * 去掉空格
 */
void main4(){
    cout<<boost::algorithm::trim_copy(string(" dsdas "))<<endl;
    cout<<boost::algorithm::trim_left_copy(string(" dsdas"))<<endl;
    cout<<boost::algorithm::trim_right_copy(string("dsdas "))<<endl;

}
/**
 * 预测判断函数
 */
void main5(){
    cout<< (boost::algorithm::ends_with(string("hello world"),"world")?"true":"false") <<endl;
    cout<< (boost::algorithm::starts_with(string("hello world"),"hello")?"true":"false") <<endl;
    cout<< (boost::algorithm::contains(string("hello world"),"llo")?"true":"false") <<endl;

}

/**
 * 替换
 */
void main6(){
    cout<<boost::algorithm::replace_all_copy(string("test1,test2,test3"),"test","hello")<<endl;
    cout<<boost::algorithm::replace_first_copy(string("test1,test2,test3"),"test","hello")<<endl;
    cout<<boost::algorithm::replace_last_copy(string("test1,test2,test3"),"test","hello")<<endl;

}
int main_test8(){
    main6();
    return 0;
}