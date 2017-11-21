#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace std;

/**
 * 线程获取结果
 * boost::packaged_task 包装一个可调用的对象，并且允许异步获取该可调用对象产生的结果
 * unique_future 用于保存异步计算得到的结果
 */
int Fibonacci(int n) {
    if (n == 1 || n == 2) return 1;
    else return Fibonacci(n - 1) + Fibonacci(n - 2);
}

void main1() {
    boost::packaged_task<int> pt(boost::bind(Fibonacci, 10));
    boost::unique_future<int> uf = pt.get_future();
    //启动线程，必须使用move，packaged_task是不可拷贝的
    boost::thread th(boost::move(pt));
    uf.wait();
    int nVal = uf.get();
    cout << "Fibonacci " << nVal << endl;
}

/*uf.wait等待线程结束，当然future类也提供了很多种等待函数，如timed_wait等待一段时间。

当然，我们更多的时候是等待一组线程的结束，这是可以用wait_for_all等待所有future对象，wait_for_any 等待任意一个对象接收。*/

void main2()
{
    boost::packaged_task<int> pt1(boost::bind(Fibonacci, 10));
    boost::packaged_task<int> pt2(boost::bind(Fibonacci, 20));
    boost::unique_future<int> uf1 = pt1.get_future();
    boost::unique_future<int> uf2 = pt2.get_future();
    boost::thread(boost::move(pt1));
    boost::thread(boost::move(pt2));
    boost::wait_for_all(uf1, uf2);
    cout << "Fibonacci " << uf1.get() << " ," << uf2.get() << endl;
}

/**
 * 护栏barrier
 * 护栏就是说要等待所有的线程到达同一个点，才继续往下执行。
 */
boost::barrier br(3);
void BarrierFunc()
{
    cout << "begin" << endl;
    br.wait();
    cout << "end " << endl;
}
void main3(){
    boost::thread_group grp;
    grp.create_thread(BarrierFunc);
    grp.create_thread(BarrierFunc);
    grp.create_thread(BarrierFunc);
    grp.join_all();
}

/**
 * 线程本地存储
*程序中使用全局变量或局部静态变量，这是非常常见的，但这样的函数对多线程程序来说，
*很难保证程序的正确性，这时我们希望，
*这些全局变量和局部静态变量，是线程独立拥有的，多个线程之间不会造成干扰，
*那么使用thread_specific_ptr就能轻松解决。
 */
int Add(int n)
{
    static boost::thread_specific_ptr<int> sp;  //该变量是线程独立拥有的
    if (!sp.get())
    {
        sp.reset(new int(0));
    }
    *sp = n + *sp;
    return *sp;
}
void  Sum()
{
    cout <<  Add(5) + Add(10) << endl;           //得到的结果20
}
void main4(){
    boost::thread_group threads;
    for (int i=0; i<5; ++i)
        threads.create_thread(&Sum);             //所有线程输出的结果是一样的
    threads.join_all();

}
int main_test11_2() {
    main4();
    return 0;
}