//
// Created by wenshao on 18-1-10.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Permutation(const string s, vector<string> &ret, int layer) {
    if (s.size() == 0) return;
    layer--;
    for (int i = 0; i < s.size(); i++) {
        string stmp = s;
        string ctmp = stmp.substr(i, 1);
        stmp.erase(i, 1);
        Permutation(stmp, ret, layer);
        int flag=0;
        for (int j = 0; j < ret.size(); j++) {
            if(ret[j].size()==layer){
                ret[j] = ctmp + ret[j];
                flag=1;
            }
        }
        if(flag==0){
            ret.push_back(ctmp);
        }
    }
}

void Permutation_c(char* pStr,char* pBegin){
    if(*pBegin=='\0'){
        printf("%s\n",pStr);
    } else{
        for(char* pCh=pBegin;*pCh!='\0';pCh++){
            swap(*pBegin,*pCh);
            Permutation_c(pStr,pBegin+1);
            swap(*pBegin,*pCh);
        }
    }
}
int main11() {
    vector<string> ret;
    const string s = "abcde";
    Permutation(s, ret, s.size());
    for_each(ret.begin(), ret.end(), [](string ss) { cout << ss << endl; });
    return 0;
}
int main(){
    char* pStr="abc";
    char* pBegin="";
    return 0;
}
