#include <iostream>
using namespace std;

void main1(){
    int num=10;
    int *p=new int;
    *p=10;
    cout<<*p<<" "<<p<<endl;
    delete p;
    //delete p; 只能释放一次
    cout<<*p<<" "<<p<<endl;
}
void main2(){
    int *p=new int[10];
    cout<<p<<endl;
    for(int i=0;i<10;i++){
        p[i]=i+1;
        cout<<p[i]<<endl;
    }
    delete []p;//删除数组的空间
    cout<<p<<endl;
}

class test{
public:
    static int count;
    int *p;
    int length;
public:
    test(){
        cout<<"test create~"<<endl;
    }
    ~test(){
        cout<<"test destroy~"<<endl;
    }
    static void *operator new(size_t size){
        count++;
        cout<<"test1 create~"<<endl;
        test *ttmp=::new test;//劫持
        return ttmp;
    }
    static void operator delete(void *p){
        count--;
        cout<<"test1 destroy~"<<endl;
        ::delete p;
    }
};

int test::count=0;
void main3(){
    test *t=new test[10];
    delete []t;
}

/**
 * 创建二维数组
 */
void main4(){
    int *p=new int[66];//new只能分配线性
    int(*px)[10]=(int(*)[10])p;
    int data=0;
    for(int i=0;i<6;i++){
        for(int j=0;j<10;j++){
            px[i][j]=data++;
            cout<<px[i][j]<<endl;
        }
    }
}

void main5(){
    test *t1=new test;
    test *t2=new test;
    test *t3=new test;
    delete t1;
    cout<<test::count<<endl;
}
int main(){
    main5();
    return 0;
}