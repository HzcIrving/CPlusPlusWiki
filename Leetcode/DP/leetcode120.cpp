/*
https://leetcode.cn/problems/triangle/description/ 
120. 三角形最小路径和 
给定一个三角形 triangle ，找出自顶向下的最小路径和。
每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。  

输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
输出：11
解释：如下面简图所示：
2
3 4
6 5 7
4 1 8 3
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。
*/
#include <algorithm> 
#include <vector> 
#include <iostream> 

using namespace std; 

class Solution{
public: 
    int Solve1(vector<vector<int>> &triangle){
        /*
        普通做法: DP --- 自顶向下  
        DP in NxN --- 表示从三角形顶部 -> (i,j)的最小路径和 
        // 基于DP 
        // 若 j = 0 , f[i][0] = f[i-1][0] + c[i][0]  不存在j-1 
        // 若 j = i ,(最后一个) f[i][i] = f[i-1][j-1] + c[i][i]
        // 若 j != 0,  f[i][j] = min(f[i-1][j-1], f[i-1][j]) +c[i][j] 
        空间复杂度 --- O(N^2) 
        时间复杂度 --- O(N^2)    
        */    
        int n = triangle.size();  
        vector<vector<int>> f(n, vector<int>(n)); // N*N  
        f[0][0] = triangle[0][0]; 

        for(int i = 1; i < n; i++){
            f[i][0] = f[i-1][0] + triangle[i][0];    // j = 0 
            for(int j = 1; j < i; j++){
                f[i][j] = min(f[i-1][j-1], f[i-1][j]) + triangle[i][j]; // otherwise 
            } 
            f[i][i] = f[i-1][i-1] + triangle[i][i]; // j = i 
        }  

        // 最后一行 0 ~ n-1中的最小值 
        return *min_element(f[n-1].begin(), f[n-1].end());
    } 

    int Solve2(vector<vector<int>> &triangle){
        /*
        自底到顶，直接返回，无需查找最小值  
        时间复杂度 O(n^2) 
        空间复杂度 O(n)
        2 
        3 4 
        6 5 7 
        4 1 8 3 
        ----------
        dp(n) -> 7 6 10 3
        dp(n) -> 9 10 10 3 
        dp(n) -> 11 10 10 3  -> min 11 
        */  
        vector<int> dp(triangle.back()); // 最后一行    
        for(int i = triangle.size() - 2; i>=0; i--){ 
            for(int j = 0; j<=i; j++){
                dp[j] = min(dp[j], dp[j+1]) + triangle[i][j];  
            }
        }  

        return dp[0]; 
    }
};  

int main(){ 
    // 写一个vector<vector>的测试用例 
    vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};  

    Solution s; 
    cout << s.Solve1(triangle) << endl; 
    cout << s.Solve2(triangle) << endl;  
    return 0; 
}