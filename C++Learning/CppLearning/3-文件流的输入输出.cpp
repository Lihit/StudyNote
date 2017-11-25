#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

/**
 * 文件的写入
 */
void main1() {
    ofstream fout;
    fout.open("../test.txt");
    fout << "hello world";
    fout.close();
}

/**
 * 文件读取
 */
void main2() {
    ifstream fin("../test.txt");
    char str[50] = {0};
    fin.getline(str, 50);
    cout << str;
    fin.close();
}

/*
 * fstream
 */
void main3() {
    fstream fout("../test.txt", ios::in | ios::out | ios::app);
    fout << "hello world";
    //fout.seekg(ios::beg);
    fout << "hello world11";
    fout.close();
}

/*
 * 循环读取文件
 */
void main4() {
    vector<string> ret;
    ifstream fin("../test.txt");
    char tmp[1024] = {0};
    while (true) {
        fin.getline(tmp, 1024);
        if (strlen(tmp) == 0) break;
        ret.push_back(string(tmp));
    }
    fin.close();
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i] << endl;
    }
}

void main5() {
    ifstream fin("../test.txt");
    ofstream fout("../newtest.txt");
    if (!fin || !fout) {
        cout << "文件打开失败" << endl;
        return;
    }
    char ch = 0;
    while (fin.get(ch)) {
        fout.put(ch);
    }
    fin.close();
    fout.close();
    cout << "copy完成" << endl;
}

void main6() {
    char str[80] = {0};
    cin.getline(str, 80);//逐行读取
    cout << str << endl;
    cin.getline(str, 80);//逐行读取
    cout << str << endl;
    cin.get(str, 40, 'n');//一次性读取，以ｘ结束
    cout << str << endl;
    cin.getline(str, 80);//逐行读取

}

void main7() {
    char str[80];
    cin.getline(str, 80, ',');//逐行读取
    cout << str << endl;
    cin.getline(str, 80, ',');//逐行读取
    cout << str << endl;
    cin.getline(str, 80);//逐行读取
    cout << str << endl;
}

//在ｃｐｐ中可以直接赋值
struct MyStruct {
    //char str[30];
    char *p = "北京是帝都";
    int num = 20;
    double db = 1.2;
    char ch = 'a';
};

void main8() {
    ofstream fout("../wenben.txt", ios::out);
    ifstream fin("../wenben.txt");
    MyStruct my1;
    fout << my1.p << my1.num << my1.db << my1.ch << endl;
    char str[100] = {0};
    fin.getline(str, 100, 0);
    cout << str << endl;
    fin.close();
    fout.close();
}

/**
 * 文本和二进制
 */
void main9() {
    MyStruct my1;
    my1.p = "hello world";
    ofstream fout("../bin.txt", ios::binary);
    fout.write((char *) &my1, sizeof(my1));
    fout.close();
    ifstream fin("../bin.txt", ios::binary);
    MyStruct newMys;
    fin.read((char *) &newMys, sizeof(newMys));
    cout << newMys.p << endl;
    fin.close();
}

int main() {
    main9();
    return 0;
}