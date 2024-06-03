/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 *
 * https://leetcode.com/problems/group-anagrams/description/
 *
 * algorithms
 * Medium (68.48%)
 * Likes:    18977
 * Dislikes: 608
 * Total Accepted:    2.9M
 * Total Submissions: 4.2M
 * Testcase Example:  '["eat","tea","tan","ate","nat","bat"]'
 *
 * Given an array of strings strs, group the anagrams together. You can return
 * the answer in any order.
 * 
 * An Anagram is a word or phrase formed by rearranging the letters of a
 * different word or phrase, typically using all the original letters exactly
 * once.
 * 
 * 
 * Example 1:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 * Example 2:
 * Input: strs = [""]
 * Output: [[""]]
 * Example 3:
 * Input: strs = ["a"]
 * Output: [["a"]]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= strs.length <= 10^4
 * 0 <= strs[i].length <= 100
 * strs[i] consists of lowercase English letters.
 * 
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 哈希表，键是排序后的字符串，值是原字符串的列表
        std::unordered_map<std::string, std::vector<std::string>> map;

        // 遍历所有字符串
        for (std::string& str : strs) {
            std::string key = str;
            std::sort(key.begin(), key.end());
            map[key].push_back(str);
        }

        // 收集结果
        std::vector<std::vector<std::string>> result;
        for (auto& pair : map) {
            result.push_back(pair.second);
        }

        return result;
    }
};
// @lc code=end

// 126/126 cases passed (24 ms)
// Your runtime beats 78.44 % of cpp submissions
// Your memory usage beats 89.37 % of cpp submissions (23.6 MB)
