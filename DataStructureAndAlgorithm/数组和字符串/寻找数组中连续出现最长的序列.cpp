//
// Created by wenshao on 18-1-10.
//

#include <iostream>
#include <bitset>
#include <unordered_map>
#include <vector>

using namespace std;

struct Bound{
    int low;
    int high;
    Bound(){low=0;high=0;}
};

int longestConsecutive(vector<int> &num) {
    unordered_map<int ,Bound> map;
    int local=0,maxlen=0;
    for(int i=0;i<num.size();i++){
        if(map.count(num[i])){
            continue;
        }
        local=num[i];
        int low=local,high=local;
        if(map.count(local-1)){
            low=map[local-1].low;
        }
        if(map.count(local+1)){
            high=map[local+1].high;
        }
        map[low].high=map[local].high=high;
        map[high].low=map[local].low=low;
        if(high-low+1>maxlen){
            maxlen=high-low+1;
        }
    }
    return maxlen;
}

int main(){

}