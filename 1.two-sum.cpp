/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash_map;
        for (int i = 0; i < nums.size(); i++) {
            if (hash_map.find(target - nums[i]) != hash_map.end()) {
                return {hash_map[target - nums[i]], i};
            } else {
                hash_map[nums[i]] = i;
            }
        }
        return {};
    }
};
// @lc code=end

/**
 * @brief 
 * 63/63 cases passed (12 ms)
 * Your runtime beats 61.13 % of cpp submissions
 * Your memory usage beats 16.99 % of cpp submissions (14.1 MB)
 * 
 */