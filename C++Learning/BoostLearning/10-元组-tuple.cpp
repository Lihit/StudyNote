#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <boost/math/common_factor.hpp>
#include "boost/tuple/tuple_io.hpp"
using namespace std;
using namespace boost;

/**
 * tuple的构造和访问
 */
void main1() {
    boost::tuple<int, double, string> triple(12, 3.4, "hello world");
    int i = tuples::get<0>(triple);
    cout<<i<<endl;
    double d = triple.get<1>();
    cout<<d<<endl;
    string s = get<2>(triple);
    cout<<s<<endl;
}

/**
 * tuple的赋值和复制构造
 */
class base {
public:
    virtual ~base() {};
    virtual void test() {
        std::cout << "base::test()\n";
    }
};

class derived : public base {
public:
    virtual void test() {
        std::cout << "derived::test()\n";
    }
};

void main2(){
    boost::tuple<int,std::string,derived> tup1(-5,"Tuples");
    boost::tuple<unsigned int,std::string,base> tup2;
    tup2=tup1;

    tup2.get<2>().test();
    std::cout << "Interesting value: "
              << tup2.get<0>() << '\n';

    boost::tuple<double,std::string,base> tup3(tup2);
    tup3.get<0>()=3.14;
    cout<<tup3.get<0>()<<endl;
}

/**
 * 绑定tuple元素到变量
 */
boost::tuple<int,int> gcd_lcm(int val1,int val2) {
    return boost::make_tuple(
            boost::math::gcd(val1,val2),
            boost::math::lcm(val1,val2));
}
void main3(){
    boost::tuple<int,int> tup;
    tup=gcd_lcm(12,18);
    int gcd=tup.get<0>();  // 译注：原文为 int gcd=tup.get<0>()); 明显有误
    int lcm=tup.get<1>();  // 译注：原文为 int gcd=tup.get<1>()); 明显有误

    std::cout << "Greatest common divisor: " << gcd << '\n';
    std::cout << "Least common multiple: " << lcm << '\n';

    //"新"方法
    boost::tie(gcd,lcm)=gcd_lcm(15,20);

    std::cout << "Greatest common divisor: " << gcd << '\n';
    std::cout << "Least common multiple: " << lcm << '\n';

    //有时我们并不是对返回的 tuple 中所有的元素感兴趣，tie 也可以支持这种情况。
    // 有一个特殊的对象，boost:: tuples::ignore，它忽略一个 tuple 元素的值。
    // 如果前例中我们只对最大公约数感兴趣，我们可以这样写
    boost::tie(gcd,boost::tuples::ignore)=gcd_lcm(15,20);
    std::cout << "Greatest common divisor: " << gcd << '\n';
}

/**
 * tuple的流操作
 */
void main4(){
    boost::tuple<int,double> tup1;
    boost::tuple<long,long,long> tup2;

    std::cout << "Enter an int and a double as (1 2.3):\n";
    std::cin >> tup1;

    std::cout << "Enter three ints as |1.2.3|:\n";
    std::cin >> boost::tuples::set_open('|') >>
             boost::tuples::set_close('|') >>
             boost::tuples::set_delimiter('.') >> tup2;

    std::cout << "Here they are:\n"
              << tup1 << '\n'
              << boost::tuples::set_open('\"') <<
              boost::tuples::set_close('\"') <<
              boost::tuples::set_delimiter('-');

    std::cout << tup2 << '\n';
}
int main_test10() {
    main4();
    return 0;
}