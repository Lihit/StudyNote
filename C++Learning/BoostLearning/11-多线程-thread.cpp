#include <iostream>
#include <boost/thread.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

/**
 * 使用全局函数作为线程执行体
 * @param n
 */
void printA(int n){
    for(int i=0;i<n;i++){
        cout<<'A'<<i<<endl;
        sleep(1);
    }
}
void printB(int n){
    for(int i=0;i<n;i++){
        cout<<'B'<<i<<endl;
        sleep(1);
    }

}
void main1(){
    boost::thread thA(printA,10);
    boost::thread thB(printB,10);
    thA.join();
    thB.join();
}
/**
 * 使用成员函数作为线程执行体
 */
class A
{
public:
    void Func(int nCount)
    {
        for (int i = 0; i < nCount; i++)
        {
            cout <<  __FUNCTION__ << i << endl;
        }
    }
};
//线程参数都采用值传递，因此即使如下传入一个临时变量作为参数，线程照样可以正确运行
//如果需要传递引用，可通过ref库来实现
boost::thread *pth;
void main2(){
    A a;
    pth=new boost::thread(&A::Func,&a,10);
    pth->join();
}

/**
 * 仿函数作为线程执行体
 */
class  B
{
public:
    B(int n):nMem(n)
    {
    }
    void operator()()
    {
        for (int i = 0; i < nMem; i++)
        {
            cout <<  __FUNCTION__ << i << endl;
        }
    }
    int nMem;
};
//线程thread对象销毁时，会与线程执行体分离，线程执行体不受影响
void main3(){
    //创建临时线程对象
    boost::thread th(B(100));
    th.join();
}

/**
 * 创建一个线程，结合boost.bind库和lambda表达式
 */
void main4(){
    boost::thread th3([](int nCount){
        for (int i = 0; i < nCount; i++)
        {
            cout <<  __FUNCTION__ << i << endl;
        }
    }, 10);
    th3.join();
}
/*
线程不是在任意时刻都可以被中断，因此要实现中断，需要我们自己决定什么时候可以被中断，boost库定义了以下函数是可以被中断的：

boost::thread::join()
boost::thread::timed_join()
boost::boost::thread::try_join_for(),
        boost::boost::thread::try_join_until(),
        boost::condition_variable::wait()
boost::condition_variable::timed_wait()
boost::condition_variable::wait_for()
boost::condition_variable::wait_until()
boost::condition_variable_any::wait()
boost::condition_variable_any::timed_wait()
boost::condition_variable_any::wait_for()
boost::condition_variable_any::wait_until()
boost::thread::sleep()
boost::this_thread::sleep_for()
boost::this_thread::sleep_until()
boost::this_thread::interruption_point()
成员函数interrupt，运行正在执行的线程中断，被中断的线程会抛出异常类boost::thread_interrupted，程序应该自行处理该异常，以确保线程正确结束。
*/

void interrupt_thread(int nCount)
{
    try
    {
        for (int i = 0; i < nCount; i++)
        {
            //sleep函数允许中断
            boost::this_thread::sleep(boost::posix_time::seconds(1));
            cout <<  __FUNCTION__ << i << endl;
        }
    }
    catch(boost::thread_interrupted&)
    {
        cout << "thread interrupt" << endl;
    }
}
void main5(){
    boost::thread th2(interrupt_thread, 100);
    boost::this_thread::sleep(boost::posix_time::seconds(4));
    th2.interrupt();
}

/**
 * 线程组
 */
void main6(){
    boost::thread_group grp;
    grp.create_thread( boost::bind(printA, 10));
    A a;
    grp.add_thread(new boost::thread(&A::Func, &a, 10));
    grp.add_thread(new boost::thread(B(10)));
    grp.join_all();
}
int main_test11(){
    main6();
    return 0;
}