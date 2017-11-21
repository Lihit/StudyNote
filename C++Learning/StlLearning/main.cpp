#include <iostream>
#include <set>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <hash_set>
#include <hash_map>

using namespace std;
using namespace __gnu_cxx;

/*
 * set
 */
struct strless {
    bool operator()(const char *str1, const char *str2) {
        return strcmp(str1, str2) < 0;
    }
};

//红黑树处理纯数字的特别少，主要用来处理字符串和对象
void main1() {
    //set<char*,strless> myset(strless());//默认构造
    const char *cmd[] = {"abc", "calc", "notepad", "const"};
    set<const char *, strless> myset(cmd, cmd + 4);

    for (auto ib = myset.begin(); ib != myset.end(); ib++) {
        cout << *ib << endl;
    }
    myset.insert("hello");
    myset.insert("world");
    for (auto i:myset) {
        cout << i << endl;
    }

    set<const char *, strless>::iterator pfind=myset.find("calc");
    cout<<*pfind<<endl;

    //pair起到获取插入返回值，第一个是类型，类型比大小的方式
    pair<set<const char *>::iterator, bool> p=myset.insert("hello");
    if(p.second){
        cout<<"successfully insert!"<<*p.first<<endl;
    }
    else{
        cout<<"error"<<endl;
    }

}

/**
 * multiset
 */
struct student{
    int id;
    char name[30];
};

struct stuless{
    bool operator()(const student& s1, const student& s2){
        return s1.id<s2.id;
    }
};
//multiset每个节点都是链表
void main2(){
    student stuArray[]={{12,"wen"},{11,"liu"},{13,"zhang"}};
    multiset<student,stuless> myset(stuArray,stuArray+3);
    for(auto p:myset){
        cout<<p.id<<" "<<p.name<<endl;
    }
    student s1={122,"hello"};
    student s2={12,"wen"};
    myset.insert(s1);
    myset.insert(s2);
    for(auto p:myset){
        cout<<p.id<<" "<<p.name<<endl;
    }
}
/**
 * map映射
 */
struct teacher{
    int age;
    char name[30];
};
struct teaInfo{
    int id;
    teacher t;
};
void main3(){
    map<const char*,int> mymap;
    mymap["wen"]=100;//对等的映射来查找
    cout<<mymap["wen"]<<endl;

    teaInfo stuArray[]={{1,{12,"wen"}},{2,{11,"liu"}},{3,{13,"zhang"}}};
    map<int,teacher> mymap1;
    for(int i=0;i<3;i++){
        mymap1[stuArray[i].id]=stuArray[i].t;
    }
    for(auto s:mymap1){
        cout<<s.first<<" "<<s.second.name<<":"<<s.second.age<<endl;
    }
}

/**
 * multimap
 */
void main4(){
    multimap<const char *,int> mymap;
    mymap.insert(make_pair("nihao",10));
    mymap.insert(make_pair("nihao",10));
    mymap.insert(make_pair("nihao",10));
    mymap.insert(make_pair("nihao",10));
    for(auto s:mymap){
        cout<<s.first<<" "<<s.second<<endl;
    }
}

/**
 * hashset
 */

struct strd{
    bool operator()(const char* str1, const char* str2){
        return strcmp(str1,str2)==0;
    }
};
void main5(){
    hash_set<int> hs;
    hs.insert(91);
    hs.insert(11);
    hs.insert(11);
    hs.insert(32);
    hs.insert(32);
    for(auto h:hs){
        cout<<h<<endl;
    }

    auto pfind=hs.find(11);
    if(pfind==hs.begin()){
        cout<<*pfind<<endl;
    }else{
        cout<<"not found"<<endl;
    }
}
void main6(){
    hash_set<const char*> hs;
    hs.insert("nihao");
    hs.insert("nihao1");
    hs.insert("nihao2");
    hs.insert("nihao3");
    auto pfind=hs.find("nihao2");
    if(pfind==hs.begin()){
        cout<<*pfind<<endl;
    }else{
        cout<<"not found"<<endl;
    }
}

/**
 * hash_map
 * @return
 */

void main7(){
    hash_map<const char*,int> mymap;
    mymap["wen"]=100;//对等的映射来查找
    cout<<mymap["wen"]<<endl;

    teaInfo stuArray[]={{1,{12,"wen"}},{2,{11,"liu"}},{3,{13,"zhang"}}};
    map<int,teacher> mymap1;
    for(int i=0;i<3;i++){
        mymap1[stuArray[i].id]=stuArray[i].t;
    }
    for(auto s:mymap1){
        cout<<s.first<<" "<<s.second.name<<":"<<s.second.age<<endl;
    }
}
int main() {
    main7();
    return 0;
}