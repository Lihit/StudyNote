#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <set>
using namespace std;

/**
 * find
 * find_if
 * find_if_not
 */
void main1(){
    vector<int> myv={12,3,31,11,2,44};
    for_each(myv.begin(),myv.end(),[](int v){cout<<v<<endl;});
    auto i=find(myv.begin(),myv.end(),31);
    if(i==myv.end()){
        cout<<"31 can not be found"<<endl;
    } else{
        cout<<"found"<<endl;
    }

    auto j =find_if(myv.begin(),myv.end(),[](int v)->bool{return v>10;});
    cout<<*j<<endl;

    auto k =find_if_not(myv.begin(),myv.end(),[](int v)->bool{return v>10;});
    cout<<*k<<endl;
}

/**
 * sort
 * fill
 */
template <class T>
class show{
public:
    void operator()(T& t){
        cout<<t<<" ";
    }
};
void main2(){
    /*sort*/
    list<int> l1={11,2,31,4};
    //for_each(l1.begin(),l1.end(),show<int>());
    vector<int> v1={43,21,1,2};
    //排序
    //sort(l1.begin(),l1.end());
    sort(v1.begin(),v1.end());//排序，简单的排序
    //算法依赖于数据结构（链式和线性），不同的数据结构，算法不一样
    for_each(v1.begin(),v1.end(),show<int>());
    for_each(l1.begin(),l1.end(),show<int>());
    /*fill*/
    fill(v1.begin(),v1.end(),10);//对指定位置数据进行初始化
    for_each(v1.begin(),v1.end(),show<int>());
}

void main3(){
    multiset<int> myset;
    myset.insert(11);
    myset.insert(21);
    myset.insert(1);
    myset.insert(211);
    myset.insert(1);
    myset.insert(1);
    myset.insert(21);
    for_each(myset.begin(),myset.end(),show<const int>());
    int i=0;
    for(auto ib=myset.begin();ib!=myset.end();ib++,i++);
    cout<<i<<endl;

    int num=count(myset.begin(),myset.end(),1);
    cout<<num<<endl;
    //找到第一组相同的元素
    auto it=adjacent_find(myset.begin(),myset.end());
    cout<<*it<<endl;
    //寻找第二组相同的元素
    it++;
    it++;
    it++;
    //对于链式迭代器只能用++或是--，而不能用it=it+3
    it=adjacent_find(it,myset.end());
    cout<<*it<<endl;
}

/**
 * 随机打乱random_shuffle
 */
void main4(){
    vector<int> v1;
    for (int i = 0; i <10 ; ++i) {
        v1.push_back(i+1);
    }
    for_each(v1.begin(),v1.end(),show<const int>());
    cout<<endl;
    random_shuffle(v1.begin(),v1.end());
    for_each(v1.begin(),v1.end(),show<const int>());
}

/**
 * partition
 * rotate
 */
bool isok(int num){
    return (num>5);
}
void main5(){
    srand((unsigned)time(0));
    vector<int> v1;
    for (int i = 0; i <10 ; ++i) {
        v1.push_back(rand()%10);
    }
    for_each(v1.begin(),v1.end(),show<const int>());
    cout<<endl;
    partition(v1.begin(),v1.end(),isok);//服务于快速排序
    for_each(v1.begin(),v1.end(),show<const int>());
    /*rotate(v1.begin(),v1.begin()+3,v1.end());//将begin(),v1.begin()+3之间的数据移动到end后边
    for_each(v1.begin(),v1.end(),show<const int>());
    cout<<endl;*/
}

void main6(){
    int a[3]={2,1,3};
    do{
        cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<endl;
    }while (prev_permutation(a,a+3));
}

void main7(){
    vector<char> one={'B','A','C','Y','X','Z'};
    for_each(one.begin(),one.end(),show<char>());
    cout<<endl;
    sort(one.begin(),one.begin()+3);
    for_each(one.begin(),one.end(),show<char>());
}

class student{
public:
    string name;
    int score;
public:
    student(string str,int num){
        name=str;
        score=num;
    }
    bool operator<(const student s1)const{
        return this->score<s1.score;
    }
};
void main8(){
    vector<student> sv;
    student s1("john",10);
    sv.push_back(s1);
    student s2("john2",20);
    sv.push_back(s2);
    student s3("john3",13);
    sv.push_back(s3);
    student s4("john",4);
    sv.push_back(s4);
    partial_sort(sv.begin(),sv.begin()+3,sv.end());
    for(int i=0;i<4;i++){
        cout<<sv[i].name<<" "<<sv[i].score<<endl;
    }
}
int main_test2(){
    main8();
    return 0;
}