#include <iostream>
#include <iomanip>//控制输出流

using namespace std;

/**
 * 文件重定向
 */
void main1() {
    char str[30] = {0};
    cin >> str;
    cout << str;
    system(str);
    cerr << "this is a error\n";
}

void main2() {
    char ch;
    //cin>>ch;
    ch = cin.get();
    cout.put(ch);
    //cout<<ch<<endl;
    //cout<<(char)(ch-32);
}

void main3() {
    //cin也会把换行符放进输入缓冲区
    char ch = cin.get();
    cout.put(ch);
    //cin.get();
    while (ch != '\t') {
        ch = cin.get();
        //cin.get();
        cout.put(ch);
    }
}

void main4() {
    char str[30] = {0};
    cin.getline(str, 10);
    cout << str << endl;
}

/**
 * 输出流操作
 */
void main5() {
    cout.put('a').put('b').put('\n');
    char str[] = "ashdujahsa2312312hb3j2h3b";
    cout.write(str, 10);
}

void main6() {
    int num = 01070;//八进制
    cout << num << endl;//输出是十进制
    //默认是十进制
    //endl是流结束的标志
    cout << hex;//oct和hex是一种强制标志，ｅｎｄｌ结束不了
    cout << num << endl;
    cout << oct << num << endl;

}

void main7() {
    double db = 1.98232222222222222;
    cout << db << endl;//默认小数点后面六位
    cout << setprecision(15) << db;//设置精确度
    cout.width(40);
    cout.fill('*');
    cout.setf(ios::right, ios::left);
    cout << "hello world" << endl;
    cout.width(20);
    cout.fill('*');


}

void main8() {
    int num;
    cin.setf(ios::hex, ios::basefield);//设置成输入是十六进制
    cin >> num;
    cout << num;
}

void main9() {
    double db = 100 / 7.0;
    cout.setf(ios::fixed | ios::showpoint);//定点
    cout << db << endl;
    cout.setf(ios::scientific, ios::fixed | ios::showpoint);//实数，根据方便自动选择指数或是定点小数
    cout << db << endl;
}

void main10(){
    const int num=15;
    cout<<setw(10)<<setfill('*')<<setiosflags(ios::left)<<num<<endl;
    cout<<setw(10)<<setfill('*')<<setiosflags(ios::right )<<num<<endl;
    cout<<resetiosflags(ios::right)<<setw(10)<<setbase(16)<<setfill('X')<<setiosflags(ios::left)<<num<<endl;

}
int main_test1() {
    main10();
    return 0;
}