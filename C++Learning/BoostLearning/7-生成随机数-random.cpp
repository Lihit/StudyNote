#include <iostream>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

using namespace std;
using namespace boost;
/*
boost库为我们提供了许多的日常随机数生成器：

1.uniform_smallint：在小整数域内的均匀分布
2.uniform_int：在整数域上的均匀分布
3.uniform_01：在区间[0,1]上的实数连续均匀分布
4.uniform_real：在区间[min,max]上的实数连续均匀分布
5.bernoulli_distribution：伯努利分布
6.binomial_distribution：二项分布
7.cauchy_distribution：柯西（洛伦兹）分布
8.gamma_distribution：伽马分布
9.poisson_distribution：泊松分布
10.geometric_distribution：几何分布
11.triangle_distribution：三角分布
12.exponential_distribution：指数分布
13.normal_distribution：正态分布
14.lognormal_distribution：对数正态分布
15.uniform_on_sphere：球面均匀分布*/
boost::random::mt19937 gen;//随机数种子生成
void main71(){
    {
        //整数
        boost::uniform_int<> real(1, 999);
        std::cout << real(gen) << std::endl;
    }

    {
        //实数
        boost::uniform_real<double> real(1, 5);
        std::cout << real(gen) << std::endl;
    }

    {
        //0-1上的实数
        boost::uniform_01<boost::mt19937&> u01(gen);
        //正态分布，参数分别为均值、方差
        boost::normal_distribution<> nd(0, 1);
        std::cout << nd(u01) << std::endl;
    }
    boost::random::uniform_int_distribution<> dist(1, 1000);
    std::cout << dist(gen) << std::endl;
    std::cout << dist(gen) << std::endl;
    std::string chars(
            "abcdefghijklmnopqrstuvwxyz"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "1234567890"
                    "!@#$%^&*()"
                    "`~-_=+[{]{\\|;:'\",<.>/? ");
/*    boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
    for(int i = 0; i < 8; ++i) {
        std::cout << chars[index_dist(rng)];
    }*/
}
int main_test7(){
    main71();
    return 0;
}