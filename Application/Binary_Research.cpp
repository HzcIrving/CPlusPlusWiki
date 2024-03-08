#include <iostream> 
#include <vector> 
using namespace std;  

/*
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。
*/

class Solution {
public:
    int searchInsert(vector<int>& sums, int target) {
        // 寻找大于等于某个数的第一个位置 
        // nums 单调增  
        int L = 0;
        int R = sums.size()-1; 
        int ans = sums.size(); 

        while (L <= R){
            // int mid = ((R - L) >> 1) + L;  
            int mid = round((R-L)*0.5 + L);
            if (target <= sums[mid]){
                ans = mid; 
                R = mid - 1; 
            }else{
                L = mid + 1; 
            }
        }
        return ans;
    }
}; 


int main(){
    int target = 4;
    vector<int> nums = {1,3,5,6}; 
    Solution sol;
    auto ans = sol.searchInsert(nums, target);   
    cout << "答案:" << ans << endl; 
    return 0; 

}