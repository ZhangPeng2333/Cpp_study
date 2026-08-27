#include <iostream>
#include <string>
#include <regex>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        string temp = to_regex(p);
        std::regex pattern(temp);
        return regex_match(s, pattern);
    }
private:
    string to_regex(const string& text){
        string regex_str;
        for (char a: text)
        {
            if (a=='*')
            {
                regex_str += ".*";
            }
            else if (a=='?')
            {
                regex_str += ".";
            }else{
                regex_str+=a;
            }
        }
    }
};