/* 
给定一个共有𝑛阶的楼梯，你每步可以上 1阶或者2阶，请问有多少种方案可以爬到楼顶？ 

step by step 
*/ 
#include <iostream> 
#include <vector>  
#include <string>

using namespace std;  

class StairSolver {
public: 
    StairSolver(vector<int> acts, int start_state, int tar, const string& type){ 
        _acts = acts; 
        _state = start_state;  
        _target = tar;   
        _type = type;

        if(type == "DP" || type == "DFS"){ 
            for(int i=0; i<=tar; i++){
                _res_dp.push_back(-1); 
            }   

            // dp[1] = 1; dp[2] = 2  
            _res_dp[0] = 1;  
            _res_dp[1] = 2;  

            // 初始化dp数组打印 
            for(auto & res: _res_dp){
                cout << res << " "; 
            } cout << endl; 
        }

    }  

    /*Solve1 回溯 
    并不显式地对问题进行拆解，而是将求解问题看作一系列决策步骤
    通过试探和剪枝，搜索所有可能的解。 
    时间复杂度O(2^n) (action_dim=2)
    */ 
    void solve1Backtrack(int state){ 
        if(state == _target){
            _res[0]++;   // 只记录起始 
            return; 
        } 
        // 遍历所有走楼梯的action 
        for(auto &act : _acts){
            // 剪枝 ------------------------------
            if(state + act > _target){
                continue; 
            }
            // 做出选择 更新状态 
            solve1Backtrack(state + act); 
        }
    } 

    /*Solve2 DFS暴力搜索 
    回溯不显示对问题求解，将求解问题看成一系列决策动作。 可以尝试从问题分解的角度分析这道题。 
    - 设爬到i阶有dp[i]种方案, dp[i]就是原问题: 
       - 子问题: dp[i-1], dp[i-2], ..., dp[2], d[1]  
    - act = {1,2}，因此: 
       - dp[i] = dp[i-1] + dp[i-2] 
    这意味着在爬楼梯问题中，各个子问题之间存在递推关系。
    原问题的解可以由子问题的解构建得来。      
    -----------------------------------------
    以dp[n]为起点，拆解成两个子问题和； 递归终止条件是到达dp[1], dp[2];  

    时间复杂度:对于dp[n]，递归深度n, 时间复杂度O(2^n) 
    -----------------------------------------
    */ 
    int solve2DFS(int n){
        //递归终止 
        if(n==1 || n==2){
            return n; 
        } 
        int res = solve2DFS(n-1) + solve2DFS(n-2); 
        return res; 
    } 

    /*重复: O(9) = O(8) + O(7); O(8) = O(7) + O(6); O(7)重复计算了 
    - 我们声明一个数组 mem 来记录每个子问题的解，并在搜索过程中将重叠子问题剪枝。
    - 时间复杂度近似为O(n); 
    */  
    int solve2DFSMem(int n){
        if (n == 1||n==2){
            return n; 
        } 
        // 判断是否已经存过  
        if (_res_dp[n] != -1){
            return _res_dp[n]; // 避免重复计算 
        }
        _res_dp[n] = solve2DFSMem(n-1)+solve2DFSMem(n-2);    
        return _res_dp[n]; 
    }


    void solve2(int n){  
        // 判断_res_dp是否初始化  
        if (_type == "DFS"){
            cout << "DFS搜方案数:" << solve2DFS(n) << endl;  
        }
        else
        {
            cout << "DFS搜空间优化:" << solve2DFSMem(n) << endl;  
            for(auto & res: _res_dp){
                res = -1; 
            }
        }
    }

    /*DP自底向上
    状态转移: dp[n] = dp[n-1] + dp[n-2] 
    空间优化,每次存两个数,并交换; 
    */  
    int solveDP(int n){
        int dp_pre = 2;  // dp[2]
        int dp_pre_pre = 1; // dp[1]  
        int res = 0;  
        for(int i = 3; i<=n; i++){
            res = dp_pre + dp_pre_pre; 
            dp_pre_pre = dp_pre; 
            dp_pre = res; 
        } 
        cout << "DP解方案数:" << res << endl; 
        return res; 
    }


    void printRes(int n){ 
        cout << "方案数:" << _res[n] << endl;   
        _res = {0};
    } 

private: 
    vector<int> _acts; 
    int _state; // 当前所在楼梯树   
    int _target; // 目标
    vector<int> _res = {0};  // 每一阶到顶层的楼梯树   
    vector<int> _res_dp;   
    string _type;  

    void _swap(int &a, int &b){
        int tmp = a; 
        a = b; 
        b = tmp;
    }
}; 

int main(){
    vector<int> actions = {1, 2}; 
    int start_state = 0;  
    int tar = 8;  // 4级台阶 

    // 1. 回溯求解 --- 自顶向下
    StairSolver solverBacktrack(actions, start_state, tar, "Backtrack"); 
    solverBacktrack.solve1Backtrack(start_state);
    solverBacktrack.printRes(0);   

    // 2. DFS暴力搜索  --- 自顶向下
    StairSolver solverDFS(actions, start_state, tar, "DFS");  
    StairSolver solverDFSMem(actions, start_state, tar, "DP");
    solverDFS.solve2(tar); 
    solverDFSMem.solve2(tar); 

    // 3. DP --- 自低向上  
    StairSolver solverDP(actions, start_state, tar, "DP"); 
    solverDP.solveDP(tar);


    return 0; 
}