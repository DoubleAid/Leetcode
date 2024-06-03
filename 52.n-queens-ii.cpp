/*
 * @lc app=leetcode id=52 lang=cpp
 *
 * [52] N-Queens II
 *
 * https://leetcode.com/problems/n-queens-ii/description/
 *
 * algorithms
 * Hard (73.82%)
 * Likes:    3807
 * Dislikes: 261
 * Total Accepted:    388.4K
 * Total Submissions: 524.4K
 * Testcase Example:  '4'
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n
 * chessboard such that no two queens attack each other.
 * 
 * Given an integer n, return the number of distinct solutions to the n-queens
 * puzzle.
 * 
 * 
 * Example 1:
 * 
 * Input: n = 4
 * Output: 2
 * Explanation: There are two distinct solutions to the 4-queens puzzle as
 * shown.
 * 
 * 
 * Example 2:
 * 
 * Input: n = 1
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 9
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        vector<int> cols(n, 0);  // 列的标记
        vector<int> diag1(2 * n - 1, 0); // 主对角线标记
        vector<int> diag2(2 * n - 1, 0); // 副对角线标记
        backtrack(0, n, cols, diag1, diag2, count);
        return count;
    }

    void backtrack(int row, int n, vector<int>& cols, vector<int>& diag1, vector<int>& diag2, int& count) {
        if (row == n) {
            // 找到一个有效的解决方案
            count++;
            return;
        }

        for (int col = 0; col < n; col++) {
            if (cols[col] || diag1[row + col] || diag2[row - col + n - 1]) {
                continue; // 如果当前列或对角线已被占用，跳过
            }

            // 放置皇后
            cols[col] = 1;
            diag1[row + col] = 1;
            diag2[row - col + n - 1] = 1;

            // 递归到下一行
            backtrack(row + 1, n, cols, diag1, diag2, count);

            // 撤销放置
            cols[col] = 0;
            diag1[row + col] = 0;
            diag2[row - col + n - 1] = 0;
        }
    }
};
// @lc code=end

// 9/9 cases passed (0 ms)
// Your runtime beats 100 % of cpp submissions
// Your memory usage beats 80.8 % of cpp submissions (7.2 MB)