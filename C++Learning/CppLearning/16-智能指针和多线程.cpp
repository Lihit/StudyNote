//
// Created by wenshao on 2017/12/12.
//

#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
using namespace std;
/**
 * 智能指针
 */
void main1(){
    for (int i = 0; i < 10000; ++i) {
        std::unique_ptr<double> pdb(new double);
    }
}
/**
 * 多线程
 */
void msg(){
    MessageBoxA(0,"1234","5678",0);
}
void main2(){
    thread t1(msg);
    thread t2(msg);
    t1.join();
    t2.join();
}

void msgA(int num){
    cout<<get_id()<<": "<<num<<endl;
}
void main3(){
    vector<thread *> thv;
    for (int i = 0; i <10 ; ++i) {
        thv.push_back(new thread(msgA,i));
    }
    for (auto th:thv){
        th->join();
    }
}
int main(){
    main2();
    return 0;
}