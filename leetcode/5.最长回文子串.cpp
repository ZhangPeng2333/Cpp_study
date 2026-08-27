/*给你一个字符串 s，找到 s 中最长的 回文 子串。

 

示例 1：

输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
示例 2：

输入：s = "cbbd"
输出："bb"
 

提示：

1 <= s.length <= 1000
s 仅由数字和英文字母组成*/

// abcbadddd

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int start = 0, maxLen = 1;  // 记录最长子串的起始位置和长度

        // 中心扩展函数：返回以 left 和 right 为中心的最长回文长度
        auto expandAroundCenter = [&](int left, int right) {
            while (left >= 0 && right < s.size() && s[left] == s[right]) {
                left--;
                right++;
            }
            return right - left - 1;  // 实际回文长度
        };

        for (int i = 0; i < s.size(); ++i) {
            // 奇数长度回文，中心为 i
            int len1 = expandAroundCenter(i, i);
            // 偶数长度回文，中心为 i 和 i+1
            int len2 = expandAroundCenter(i, i + 1);

            int len = max(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;  // 计算起始位置（对应奇数/偶数中心）
            }
        }
        return s.substr(start, maxLen);
    }
};