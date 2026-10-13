#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// CLIMBING STAIRS: ways(n) = ways(n - 1) + ways(n - 2)
// ============================================================

// 1. Plain recursion
// Time: O(2^n) upper bound | Auxiliary space: O(n)
int climbStairsRecursive(int n) {
    if (n <= 2) return n;
    return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
}

// 2. Memoization: top-down recursion + cached answers
// Time: O(n) | Auxiliary space: O(n), including recursion stack
int climbStairsMemoHelper(int n, vector<int>& dp) {
    if (n <= 2) return n;
    if (dp[n] != -1) return dp[n];
    dp[n] = climbStairsMemoHelper(n - 1, dp)
          + climbStairsMemoHelper(n - 2, dp);
    return dp[n];
}
int climbStairsMemoization(int n) {
    if (n <= 2) return n;
    vector<int> dp(n + 1, -1);
    return climbStairsMemoHelper(n, dp);
}

// 3. Tabulation: bottom-up iterative DP
// dp[i] = number of ways to reach step i
// Time: O(n) | Auxiliary space: O(n)
int climbStairsTabulation(int n) {
    if (n <= 2) return n;
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

// 4. Space-optimized DP: only the previous two states are retained
// Time: O(n) | Auxiliary space: O(1)
int climbStairsOptimized(int n) {
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; ++i) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


// ============================================================
// HOUSE ROBBER: at each house, choose to rob it or skip it.
// ============================================================

// 1. Plain recursion
// Time: O(2^n) upper bound | Auxiliary space: O(n)
int houseRobberRecursiveHelper(const vector<int>& nums, int i) {
    if (i >= static_cast<int>(nums.size())) return 0;
    int skip = houseRobberRecursiveHelper(nums, i + 1);
    int take = nums[i] + houseRobberRecursiveHelper(nums, i + 2);
    return max(skip, take);
}
int houseRobberRecursive(const vector<int>& nums) {
    return houseRobberRecursiveHelper(nums, 0);
}

// 2. Memoization: top-down recursion + cached answers
// Time: O(n) | Auxiliary space: O(n), including recursion stack
int houseRobberMemoHelper(const vector<int>& nums, int i, vector<int>& dp) {
    if (i >= static_cast<int>(nums.size())) return 0;
    if (dp[i] != -1) return dp[i];
    int skip = houseRobberMemoHelper(nums, i + 1, dp);
    int take = nums[i] + houseRobberMemoHelper(nums, i + 2, dp);
    dp[i] = max(skip, take);
    return dp[i];
}
int houseRobberMemoization(const vector<int>& nums) {
    vector<int> dp(nums.size(), -1);
    return houseRobberMemoHelper(nums, 0, dp);
}

// 3. Tabulation: dp[i] = best amount from the first i houses
// Time: O(n) | Auxiliary space: O(n)
int houseRobberTabulation(const vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    if (n == 0) return 0;
    vector<int> dp(n + 1, 0);
    dp[0] = 0;
    dp[1] = nums[0];
    for (int i = 2; i <= n; ++i) {
        int skip = dp[i - 1];
        int take = nums[i - 1] + dp[i - 2];
        dp[i] = max(skip, take);
    }
    return dp[n];
}

// 4. Space-optimized DP: retain only the previous two states
// Time: O(n) | Auxiliary space: O(1)
int houseRobberOptimized(const vector<int>& nums) {
    int prev2 = 0, prev1 = 0;
    for (int money : nums) {
        int curr = max(prev1, money + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


// ============================================================
// MAXIMUM DEPTH OF BINARY TREE (LeetCode 104)
// Depth is counted in nodes along the longest root-to-leaf path.
// ============================================================

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

// Time: O(N) | Auxiliary space: O(H) recursion stack
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;  // Empty tree has depth 0.
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    return 1 + max(leftDepth, rightDepth);
}


// ============================================================
// DEMO MAIN: expected answers are 8, 12, and 3.
// Remove main() when copying functions into LeetCode.
// ============================================================

int main() {
    int n = 5;
    cout << "CLIMBING STAIRS, n = 5\n";
    cout << "Recursion:       " << climbStairsRecursive(n) << '\n';
    cout << "Memoization:     " << climbStairsMemoization(n) << '\n';
    cout << "Tabulation:      " << climbStairsTabulation(n) << '\n';
    cout << "Space optimized: " << climbStairsOptimized(n) << "\n\n";

    vector<int> nums = {2, 7, 9, 3, 1};
    cout << "HOUSE ROBBER, [2, 7, 9, 3, 1]\n";
    cout << "Recursion:       " << houseRobberRecursive(nums) << '\n';
    cout << "Memoization:     " << houseRobberMemoization(nums) << '\n';
    cout << "Tabulation:      " << houseRobberTabulation(nums) << '\n';
    cout << "Space optimized: " << houseRobberOptimized(nums) << "\n\n";

    // Tree: [3, 9, 20, null, null, 15, 7]
    TreeNode* root = new TreeNode(
        3, new TreeNode(9),
        new TreeNode(20, new TreeNode(15), new TreeNode(7))
    );
    cout << "MAXIMUM DEPTH OF BINARY TREE\n";
    cout << "Maximum depth:   " << maxDepth(root) << '\n';

    // Free the nodes allocated for the example tree.
    delete root->left;
    delete root->right->left;
    delete root->right->right;
    delete root->right;
    delete root;
    return 0;
}
