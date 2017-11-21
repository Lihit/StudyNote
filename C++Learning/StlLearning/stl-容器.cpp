#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>
#include <array>
#include <tuple>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

template<class T>
class myVetor {
public:
    void operator()(T &t) {
        cout << t << " ";
    }
};

void printV(int v, int num) {
    cout << v / num << " ";
}

void main1() {
    vector<int> v = {1, 2, 3, 4};
    for_each(v.begin(), v.end(), myVetor<int>());
    cout << endl;
    for_each(v.begin(), v.end(), boost::bind(printV, _1, 2));
    cout << endl;
    for_each(v.begin(), v.end(), bind2nd(ptr_fun(printV), 2));
    cout << endl;
    for_each(v.begin(), v.end(), [](int v) { cout << v << " "; });
}

/**
 * array
 */
//算法适用于任何容器
//简单线性数组容器
void main2() {
    array<int, 3> myArray = {1, 2, 3};
    for_each(myArray.begin(), myArray.end(), myVetor<int>());
    tuple<int, string, array<int, 3> > t1(1, "hello ", myArray);
    cout<<get<0>(t1)<<endl;
    cout<<get<1>(t1)<<endl;
    cout<<tuple_size<decltype(t1)>::value<<endl;
    tuple_element<0,decltype(t1)>::type i=get<0>(t1);
    cout<<i<<endl;
}

//链式容器

void main3(){
    //list适用于经常删除和经常插入
    list<int> mylist;
    mylist.push_back(1);
    mylist.push_back(2);
    mylist.push_back(3);
    mylist.push_back(4);
    mylist.push_back(5);
    for(list<int>::iterator it=mylist.begin();it!=mylist.end();it++){
        cout<<*it<<endl;
    }
    auto i=mylist.begin();
    i++;
    mylist.erase(i);
    for(list<int>::iterator it=mylist.begin();it!=mylist.end();it++){
        cout<<*it<<endl;
    }
    auto j=mylist.end();
    j--;
    mylist.erase(j);
    for(list<int>::iterator it=mylist.begin();it!=mylist.end();it++){
        cout<<*it<<endl;
    }
    mylist.clear();
}

void main4(){
    int a[5]={1,2,3,4,5};
    list<int> mylist(a,a+5);
    for(list<int>::iterator it=mylist.begin();it!=mylist.end();it++){
        cout<<*it<<endl;
    }

    auto rb=mylist.rbegin();
    auto re=mylist.rend();
    for(;rb!=re;rb++){
        cout<<*rb<<endl;
    }

}
//merge
//sort
//unique(需要先排序）
void main5(){
    int a[5]={1,12,1,4,5};
    list<int> mylist1(a,a+5);
    list<int> mylist2(a,a+5);
    mylist1.sort();
    mylist2.sort();

    mylist1.unique();
    mylist2.unique();
    mylist1.merge(mylist2);
    for(list<int>::iterator it=mylist1.begin();it!=mylist1.end();it++){
        cout<<*it<<endl;
    }
}

//红黑树容器
//set
void main7(){
    set<int> myset;
    myset.insert(1);
    myset.insert(11);
    myset.insert(111);
    myset.insert(1111);
    auto ib=myset.begin();
    auto ie=myset.end();
    for(;ib!=ie;ib++){
        cout<<*ib<<endl;
    }

    auto findpos=myset.find(11);
    if(findpos!=ie){
        cout<<"find"<<*findpos<<endl;
    }
}

//stack
void main8(){
    int num=100;
    stack<int> mystack;
    for(;num;num/2){
        mystack.push(num%2);
    }
    while(!mystack.empty()){
        cout<<mystack.top()<<" ";
        mystack.pop();
    }
}

//queue
void main9(){

    queue<char*> myq;
    myq.push("cacl");
    myq.push("note");
    myq.push("hello");
    myq.push("test");
    while(!myq.empty()){
        char* p=myq.front();
        cout<<p<<endl;
        myq.pop();
    }
}

//双端队列
//这是一个线性的队列
//可以直接用下表来做索引
//mydq1.swap(mydq2)
void main10(){
    deque<int> mydq;
    mydq.push_back(1);
    mydq.push_back(11);
    mydq.push_back(111);
    mydq.push_front(122);
    mydq.push_front(12);
    mydq.push_front(21);
    mydq.insert(mydq.begin()+3,1111);
    mydq.erase(mydq.begin());
    mydq.erase(mydq.end());
    for(int i=0;i<mydq.size();i++){
        cout<<mydq[i]<<endl;
    }
    for(deque<int>::iterator it=mydq.begin();it!=mydq.end();it++){
        cout<<*it<<endl;
    }
    cout<<mydq.max_size()<<endl;
}

//优先队列
void main11(){
    priority_queue<int> myq;
    myq.push(10);
    myq.push(11);
    myq.push(1);
    myq.push(210);
    while(!myq.empty()){
        cout<<myq.top()<<endl;
        myq.pop();
    }
}

//队列的高级用法
struct student{
    int age;
    string name;
    student(int num,string str){age=num;name=str;}
};
struct stuless{
    bool operator()(const student& s1, const student& s2){
        return s1.age<s2.age;
    }
};
void main12(){
    student s1(12,"hello");
    student s2(13,"hello");
    student s3(10,"hello");
    priority_queue<student,vector<student>,stuless> myq;
    myq.push(s1);
    myq.push(s2);
    myq.push(s3);
    while(!myq.empty()){
        cout<<myq.top().name<<" "<<myq.top().age<<endl;
        myq.pop();
    }

}
int main_test3() {
    main12();
    return 0;
}