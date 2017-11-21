#include <iostream>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

/**
 * 完全匹配
 */
void main61(){
    string str("abcd");
    regex reg( "a\\w*d" );
    if (regex_match(str, reg))
    {
        cout << str << " is match" << endl;
    }
    else
    {
        cout << str << " is not match" << endl;
    }
}

/**
 * 完全匹配并获取子字符串
 */
void main62(){
    const char* mail = "tengxun@qq.com";
    boost::cmatch res;
    //建立3个子表达式
    boost::regex reg("(\\w+)@(\\w+).(\\w+)");
    if (boost::regex_match(mail,res, reg))
    {
        //既可以通过迭代器获取数据， 也可以通过数组方式获取数据
        for (boost::cmatch::iterator pos = res.begin(); pos != res.end(); ++pos)
        {
            std::cout << *pos << std::endl;
        }
        //res[0]存放匹配到的完整字符串
        std::cout << "name:" << res[1] << std::endl;
    }
}

/**
 * 查找， 当你不需要匹配整个字符串的时候，可以选择查找
 */
void main63(){
    const char* mail = "tengxun@qq.com.cn";
    boost::cmatch res;
    //建立3个子表达式
    boost::regex reg("(\\w+)@(\\w+).(\\w+)");
    if (boost::regex_search(mail,res, reg))
    {
        std::cout <<"**************************************" << std::endl;
        //既可以通过迭代器获取数据， 也可以通过数组方式获取数据
        for (boost::cmatch::iterator pos = res.begin(); pos != res.end(); ++pos)
        {
            std::cout << *pos << std::endl;
        }
        //res[0]存放匹配到的完整字符串
        std::cout << "match :" << res[0] << std::endl << "name:" << res[1] << std::endl;
    }
}

/**
 * 替换
 * 替换匹配到的子字符串， 可以通过$N 引用第N个匹配到的值、$&  引用全匹配
 */
void main64(){
    //将tengxun@qq.com.cn 替换成tengxun@139.com.cn
    std::string mail("tengxun@qq.com.cn");
    //建立3个子表达式
    boost::regex reg("(\\w+)@(\\w+).(\\w+)");
    std::cout << boost::regex_replace(mail, reg, "$1@139.$3") << std::endl;
    std::cout << boost::regex_replace(mail, reg, "my$1@$2.$3") << std::endl;
    string s=boost::regex_replace(mail, reg, "my$1@$2.$3");
    cout<<s<<endl;
}
/**
 * 迭代
 * 当需要从字符串中提取多个表达式时，可以采用迭代进行提取
 */
void main65(){
    std::string str("tengxun@qq.com, aa@tt.com, bb@qq.com");
    boost::regex reg("(\\w+)@(\\w+).(\\w+)");
    boost::sregex_iterator pos(str.begin(), str.end(), reg);
    boost::sregex_iterator end;
    while(pos != end)
    {
        std::cout << "[" << (*pos)[1] << "]";
        ++pos;
    }
}
int main_test6(){
    main65();
    return 0;
}