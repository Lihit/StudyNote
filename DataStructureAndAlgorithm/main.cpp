#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>
using namespace std;

bool wordBreak(string s, unordered_set<string> &dict) {
    int begin = 0, end = 0;
    string word;
    bool words[s.size()+1] = {0};
    words[0] = true;

    for (int i = 1; i < s.size() + 1; i++) {
        words[i] = false;
        for (end = 0; end < s.size(); end++) {
            for(begin = 0; begin <= end; begin++)
                if (words[begin] && dict.find( s.substr(begin, end-begin+1) )
                                    != dict.end()) {
                    words[end + 1] = true;
                    break;
                }
        }
    }

    return words[s.size()];
}
int main(int argc, char const *argv[])
{
    string s="iloveapplephone";
    unordered_set<string> dict={"apple","phone","i","love","hello","world"};
    bool ret=wordBreak(s,dict);
    cout<<ret<<endl;
    return 0;
}