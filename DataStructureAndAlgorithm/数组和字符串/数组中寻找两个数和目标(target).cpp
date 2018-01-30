//
// Created by wenshao on 18-1-10.
//

#include <iostream>
#include <bitset>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> addsToTarget(vector<int> &numbers,int target){
    unordered_map<int,int> numToIndex;
    vector<int> vi(2);
    for(auto it=numbers.begin();it!=numbers.end();it++){
        if(numToIndex.count(target-*it)){
            vi[0]=numToIndex[target-*it]+1;
            vi[1]=(int)(it-numbers.begin())+1;
            return vi;
        }
        numToIndex[*it]=(int)(it-numbers.begin());
    }
    return vi;
}

int main(){

}