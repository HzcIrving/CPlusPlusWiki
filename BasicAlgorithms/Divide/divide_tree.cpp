/*
构建二叉树问题
-------------------------------------------
- 给定一棵二叉树的前序遍历 preorder 和中序遍历 inorder ，请从中构建二叉树，返回二叉树的根节点。

- 前序preorder：中左右 3-9-8-2-1-7
- 中序inorder：左中右 8-9-3-1-2-7

原问题定义为从 preorder 和 inorder 构建二叉树，是一个典型的分治问题。
---------------------------------------------
- 问题可以分解：从分治的角度切入，我们可以将原问题划分为两个子问题：构建左子树、构建右子树，加上一步操作：初始化根节点。而对于每棵子树（子问题），我们仍然可以复用以上划分方法，将其划分为更小的子树（子问题），直至达到最小子问题（空子树）时终止。
----------------------------------------------
- 子问题是独立的：左子树和右子树是相互独立的，它们之间没有交集。在构建左子树时，我们只需关注中序遍历和前序遍历中与左子树对应的部分。右子树同理。
----------------------------------------------
- 子问题的解可以合并：一旦得到了左子树和右子树（子问题的解），我们就可以将它们链接到根节点上，得到原问题的解。

分治解决方法：
- 根节点在preorder中索引记为i
- 根节点在inorder中索引记为m 
- 当前树在inorder中索引区间记为[L,r] 
- 根节点在preorder中索引（子问题）i+1，子树inorder中索引区间[L, m-1] 
- 根节点在preorder中索引（子问题）i+1+(m-L), 子树inorder中索引区间[m+1, r]
m-L的含义：左子树的节点数量
-------------------------------------------------------
- i, [L,r]  
- 左 i+1, [L, m-1]  
- 右 i+1+(m-L), [m+1, r]
以 preorder 3-9-8-2-1-7, inorder 8-9-3-1-2-7为例:  
- r1: root 3, left 9-8, right 2-1-7 (preorder) 
- r2: root 9, left 8, right null (preorder) 
-     root 2, left 1, right 7 
*/ 
#include <iostream> 
#include <unordered_map>  
#include <vector>  
#include <memory> 
#include <queue> 

using namespace std; 

/* 二叉树 */ 
struct TreeNode{
    int val; 
    TreeNode *left; // 左 
    TreeNode *right; // 右 

    // 构造1 
    TreeNode(int x): val(x), left(nullptr), right(nullptr){}  

    // 默认构造 
    TreeNode(): val(0), left(nullptr), right(nullptr){}  

    // 拷贝构造  
    TreeNode(int x, TreeNode *left, TreeNode *right): val(x), left(left), right(right){}

}; 


/* 分层打印二叉树，没有用"null"代替 */ 
/* 工具函数：
    按层打印二叉树 --- BFS 
    打印成二叉树形状
*/
void PrintTreeByLevel(TreeNode *root){
    if(root == nullptr) return; 
    std::queue<TreeNode*> q; 
    q.push(root);
    while(!q.empty()){
        int size = q.size(); 
        for(int i = 0; i < size; i++){
            TreeNode *node = q.front(); 
            q.pop(); 
            std::cout << node->val << " "; 
            if(node->left != nullptr) q.emplace(node->left); 
            if(node->right != nullptr) q.emplace(node->right); 
        } cout << endl;
    }
}


// 智能指针版本 
// // Definition for a binary tree node.
// struct TreeNode {
//     int val;
//     std::unique_ptr<TreeNode> left;
//     std::unique_ptr<TreeNode> right;
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };

/*删除TreeNode，避免内存泄漏*/
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/* 构建二叉树：分治法 */ 
TreeNode *dfs(vector<int> &preorder, unordered_map<int, int> &inorderMap, int i, int L, int R){ 
    /*
    @param i: 根节点在preorder中索引记为i  
    @param m: 根节点在inorder中索引记为m 
    @param L,r : 当前树在inorder中索引区间记为[L,r]
    */
    // 递归终止  
    if(R - L < 0){
        return NULL; 
    }   

    // 基于初始化根节点
    TreeNode *root = new TreeNode(preorder[i]); 

    // 初始化m
    // int m;  
    // for(int i = 0; i<inorder.size(); i++){
    //     if(preorder[0]==inorder[i]){
    //         m = i; 
    //         break; 
    //     }
    // }   
    int m = inorderMap[preorder[i]];

    // 左子树 
    root->left = dfs(preorder, inorderMap, i+1, L, m-1); 
    // 右子树 
    root->right = dfs(preorder, inorderMap, i+1+(m-L), m+1, R);   
    return root; 
} 

/* 构建二叉树: 分治 */  
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder){ 
    if(preorder.size() == 0 || inorder.size() == 0){
        return nullptr; 
    } 

    // 初始化m
    // int m;  
    // for(int i = 0; i<inorder.size(); i++){
    //     if(preorder[0]==inorder[i]){
    //         m = i; 
    //         break; 
    //     }
    // }   
    
    // int m = 0; 
    // 基于Hashmap来存储m，方便基于i来更新m；
    unordered_map<int, int> pre2inRootMap; 
    for(int i = 0; i<inorder.size(); i++){ 
        // inorder value -> i 
        pre2inRootMap[inorder[i]] = i; 
    }

    TreeNode *root = dfs(preorder, pre2inRootMap, 0, 0, inorder.size()-1);  

    return root; 
}

int main(){
    vector<int> preorder = {3,9,8,2,1,7}; 
    vector<int> inorder = {8,9,3,1,2,7}; 
    TreeNode *root = buildTree(preorder, inorder); 
    // cout << root->val << endl; 

    PrintTreeByLevel(root); 

    deleteTree(root);

    // 内存泄漏防止 
    return 0; 
}