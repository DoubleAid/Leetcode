/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 */
#include <vector>
#include <unordered_map>

using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        unordered_map<int, vector<vector<int>>> hash_map;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i+1; j < nums.size(); j++) {
                int key = -(nums[i] + nums[j]);
                hash_map[key].emplace_back(vector<int>{i, j});
                
            }
        }
    }
};
// @lc code=end

