#include <iostream>

using namespace std;

//自动变量，自动获取类型，输出，泛型
//自动变量，可以实现自动循环一维数组
//自动变量类型
void main1(){
    auto num1=10;
    auto num2=20/2.4;
    cout<<num1<<'\t'<<num2<<endl;
}
void main2(){
    int num[3]={1,2,3};
    int n[2][3]={{1,2,3},{4,5,6}};
    //二维数组无法用ａｕｔｏ来遍历
    for(auto i:num){
        cout<<i<<endl;
    }
    for(auto i:n){
        for(int j=0;j<3;j++){
            cout<<*(j+i)<<endl;
        }
    }
}
int main(){
    main2();
    return 0;
}