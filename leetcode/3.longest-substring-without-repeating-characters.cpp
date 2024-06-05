/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 */

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        int left_position = 0;
        unordered_map<char, int> hash_map;
        for (int i = 0; i < s.length(); i++) {
            if (hash_map.find(s[i]) != hash_map.end()) {
                if (hash_map[s[i]] >= left_position) {
                    int tmp_len = i - left_position;
                    left_position = hash_map[s[i]] + 1;
                    if (tmp_len > res) {
                        res = tmp_len;
                    }
                }
            }
            hash_map[s[i]] = i;
        }
        if (s.length() - left_position > res) {
            res = s.length() - left_position;
        }
        return res;
    }
};
// @lc code=end


// 987/987 cases passed (13 ms)
// Your runtime beats 61.44 % of cpp submissions
// Your memory usage beats 62.49 % of cpp submissions (11.2 MB)

// 这种问题可以考虑使用递归来做，但是递归的效率不如迭代，所以不推荐使用递归来做这个问题。