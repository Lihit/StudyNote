#include <iostream>
#include <boost/thread.hpp>
#include <queue>
using namespace std;
/**
 * 互斥锁
 * 在编程中，引入了对象互斥锁的概念，来保证共享数据操作的完整性。
 * 每个对象都对应于一个可称为" 互斥锁" 的标记，
 * 这个标记用来保证在任一时刻，只能有一个线程访问该对象。
 */
int gnum=0;
boost::mutex mu;//定义互斥锁对象
int Func(int nCount){
    for(int i=0;i<nCount;i++){
        boost::mutex::scoped_lock lock(mu);//对共享数据进行操作前，先加上锁
        gnum++;
        cout<<__FUNCTION__<<": "<<gnum<<endl;
    }
    return gnum;
}
void main1(){
    boost::thread th1(Func, 1000);
    boost::thread th2(Func, 2000);
    th1.join();
    th2.join();
}

/**
 * 读写锁
 */
boost::shared_mutex rw_mu;   //定义读写锁
int g_num=0;
int Write(int nCount)
{
    for (int i = 0; i < nCount; i++)
    {
        boost::unique_lock<boost::shared_mutex> lock(rw_mu);   //加唯一锁
        g_num++;
        cout << __FUNCTION__ << ": " << g_num << endl;
        sleep(0.1);
    }
    return g_num;
}
void Read(int nCount)
{
    for (int i = 0; i < nCount; i++)
    {
        boost::shared_lock<boost::shared_mutex> lock(rw_mu);  //加共享锁
        cout << __FUNCTION__ << ": " << g_num << endl;
    }
}
void main2(){
    //boost::thread th0(write, 100);
    boost::thread th1(Write, 100);
    boost::thread th2(Read, 100);
    boost::thread th3(Read, 100);
    //th0.join();
    th1.join();
    th2.join();
    th3.join();
    //th4.join();
}

/*条件量
条件量相对于互斥锁和读写锁来说，并不是那么好理解，简单点说，
 条件变量就是用于等待某个条件被触发，但为什么要配合锁使用呢，
 因为我们的等待不能是干等，那样可能会出现死锁。
如线程A负责添加任务到队列，线程B负责处理队列中的任务，队列就是两个线程的共享资源，
使用前必须加锁，但如果B线程加锁后，发现队列中没有数据，然后等待，A线程准备添加任务时，发现
锁已经被占用，于是就没法添加任务，就形成了死锁。但如果我等待时，释放锁资源，
 A线程就能正常添加任务，完成后通知B线程可以处理了，那么整个流程就畅通无阻了，
 这就是条件量的作用。*/
boost::mutex g_ioMutex;    //输出控制锁
template<typename T>
class CMsgQueue
{
public:
    CMsgQueue(size_t n):m_nCapacity(n)
    {
    }
    void Push(const T& val)
    {
        {
            boost::mutex::scoped_lock lock(m_mu);              //加锁
            while(m_val.size() == m_nCapacity)                 //队列已满
            {
                {
                    boost::mutex::scoped_lock lock(g_ioMutex);
                    cout << "队列已满" << endl;
                }
                m_condPush.wait(m_mu);                         //等待，将暂时的解锁
            }
            m_val.push(val);                                   //添加数据到队列
        }
        m_condPop.notify_one();                                 //通知读线程
    }
    void Pop(T& val)
    {
        {
            boost::mutex::scoped_lock lock(m_mu);               //加锁
            while(m_val.size() == 0)                            //队列为空
            {
                {
                    boost::mutex::scoped_lock lock(g_ioMutex);
                    cout << "队列为空" << endl;
                }
                m_condPop.wait(m_mu);                           //等待可读，
            }
            val = m_val.front();                                 //读取数据
            m_val.pop();
        }
        m_condPush.notify_one();                                 //通知写线程
    }
private:
    queue<T> m_val;                            //队列
    int m_nCapacity;                           //队列最大容量
    boost::condition_variable_any m_condPush;  //写入条件量
    boost::condition_variable_any m_condPop;   //读取条件量
    boost::mutex m_mu;                         //互斥锁
};
CMsgQueue<int> g_numQueue(10);
void FuncA(int nCount)
{
    for (int i = 0; i < nCount; i++)
    {
        {
            boost::mutex::scoped_lock lock(g_ioMutex);
            cout << __FUNCTION__ << " Put " << i << endl;
        }
        g_numQueue.Push(i);

    }
}
void FuncB(int nCount)
{
    for (int i = 0; i < nCount; i++)
    {
        int val;
        g_numQueue.Pop(val);
        boost::mutex::scoped_lock lock(g_ioMutex);
        cout << __FUNCTION__ << " Get " << val << endl;
    }
}
void main3(){
    boost::thread th1(FuncA, 50);
    boost::thread th2(FuncB, 20);
    boost::thread th3(FuncB, 30);
    th1.join();
    th2.join();
    th3.join();
}
int main_test11_1(){
    main3();
    return 0;
}