/*
时间复杂度为O(logn)的搜索算法基于分治策略时间
- 比如：二分、树搜 

1. 基于分治实现二分查找   
------------------------------------------
- 注意是分治，而非之前的递推/迭代方法 
- 给定n的有序数组nums，其中所有元素都是唯一的，查找元素target 
- 搜索区间[i,j]对应的子问题记为f(i,j) 
- 原问题f(0, n-1)为起点：
    - 计算搜索区间[i,j]中点m，根据它排除一半搜索区间 
    - 递归求解规模: f(i,m-1) or f(m+1,j) 
    - 循环上述两步，直到target找到，or，区间为空 
------------------------------------------- 

现实中，基于递归函数dfs()求解问题f(i,j) 
*/

#include <iostream> 
#include <vector> 

using namespace std; 

/*二分查找子问题f(i,j)*/ 
int dfs(vector<int> &nums, int tar, int i, int j){
    // 递归终止，无目标元素
    if(i > j){
        return -1;
    } 

    // mid 
    int mid = (i+j) / 2; 

    if(nums[mid] < tar){
        // 子问题 , 右边
        return dfs(nums, tar, mid+1, j); 
    } else if(nums[mid] > tar){
        // 子问题，左边 
        return dfs(nums, tar, i, mid-1);  
    } else{
        return mid; 
    }
}

int binarySearch(vector<int> &nums, int tar){
    return dfs(nums, tar, 0, nums.size()-1); 
} 

int main(){
    vector<int> nums = {1,2,3,4,5,6,7,8,9,10}; 
    cout << binarySearch(nums, 11) << endl; 
    cout << binarySearch(nums, 5) << endl;
}

