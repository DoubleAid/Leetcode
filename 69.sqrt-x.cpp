/*
 * @lc app=leetcode id=69 lang=cpp
 *
 * [69] Sqrt(x)
 *
 * https://leetcode.com/problems/sqrtx/description/
 *
 * algorithms
 * Easy (38.71%)
 * Likes:    8048
 * Dislikes: 4480
 * Total Accepted:    2M
 * Total Submissions: 5.1M
 * Testcase Example:  '4'
 *
 * Given a non-negative integer x, return the square root of x rounded down to
 * the nearest integer. The returned integer should be non-negative as well.
 * 
 * You must not use any built-in exponent function or operator.
 * 
 * 
 * For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: x = 4
 * Output: 2
 * Explanation: The square root of 4 is 2, so we return 2.
 * 
 * 
 * Example 2:
 * 
 * Input: x = 8
 * Output: 2
 * Explanation: The square root of 8 is 2.82842..., and since we round it down
 * to the nearest integer, 2 is returned.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= x <= 2^31 - 1
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int mySqrt(int x) {
        if (x < 2) return x;  // 处理 x 是 0 或 1 的情况

        int left = 0, right = x / 2 + 1;  // 对于大于 4 的 x，sqrt(x) 不会大于 x/2+1
        while (left < right - 1) {  // 保证至少有两个元素
            int mid = left + (right - left) / 2;  // 防止溢出
            long long val = (long long)mid * mid;  // 使用 long long 防止乘法溢出
            if (val == x) return mid;
            if (val < x) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return left;  // 返回 left，因为我们需要向下取整
    }
};
// @lc code=end

// 1017/1017 cases passed (5 ms)
// Your runtime beats 35.62 % of cpp submissions
// Your memory usage beats 80.33 % of cpp submissions (7.4 MB)