/*
 * @lc app=leetcode id=30 lang=cpp
 *
 * [30] Substring with Concatenation of All Words
 */

#include <vector>
#include <string>

using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int total_size = 0;
        for (int i = 0; i < words.size(); i++) {
            total_size += words[i].size();
        }
        for (int i = 0; i < s.size() - total_size + 1; i++) {
            vector<bool> used(words.size(), false);
            int current_p = i;
            bool found = true;
            while (found) {
                found = false;
                for (int j = 0; j < words.size(); j++) {
                    if (used[j]) continue;
                    for( int k = 0; k < words[j].size()) {
                        
                    }
                }
        }
    }

    
};
// @lc code=end

