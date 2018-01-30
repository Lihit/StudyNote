#include <iostream>
#include <bitset>

using namespace std;

bool isUnique(string input){
    bitset<256> hashMap;
    for(int i=0;i<input.size();i++){
        if(hashMap[static_cast<int>(input[i])]){
            return false;
        }
        hashMap[static_cast<int>(input[i])]=1;
    }
    return true;
}
int main(){
    cout<<isUnique("hello");
}