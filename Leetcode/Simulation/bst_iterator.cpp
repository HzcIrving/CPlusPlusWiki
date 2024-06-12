/*
Leetcode LCR 055. 二叉搜索树迭代器 
利用G:\CplusWorks\DataStructure\binary_search_tree.cpp的知识  
https://leetcode.cn/problems/kTOapQ/description/ 
--------------------------------------------------------------
方法1： 
- 先在构造函数中序遍历数组，然后直接基于数组索引进行调用 
    时间复杂度: O(n) 
    空间复杂度: O(n) 

方法2：
- 基于栈实现 
    时间复杂度:O(1) 
    空间复杂度:O(n) (退化链表)
*/ 

#include <iostream>
#include <vector>  
#include <stack> 

using namespace std; 

/*二叉树*/ 
class TreeNode{
public: 
    int val; 
    TreeNode *left; 
    TreeNode *right; 

    TreeNode(int x): val(x), left(nullptr), right(nullptr){} 
    TreeNode():val(0), left(nullptr), right(nullptr){} 
    // 拷贝构造
    TreeNode(int x, TreeNode *left, TreeNode *right): val(x), left(left), right(right){} 
};

/*方法1,数组法*/
class BSTIteratorVector{
private: 
    vector<int> _arr; 
    int _idx;   

    // 中序遍历，存在res中 
    void _inorder(TreeNode *root, vector<int> &res){
        if(root==nullptr){
            return;
        }  
        // 左
        _inorder(root->left, res);  
        // 中 
        res.push_back(root->val); 
        // 右 
        _inorder(root->right, res); 
    } 

    vector<int> _inorderTravel(TreeNode *root) {
        vector<int> res; 
        _inorder(root, res); 
        return res; 
    }


public: 
    BSTIteratorVector(TreeNode *root): _idx(0) {
        _arr = _inorderTravel(root);
    }

    int next(){
        return _arr[_idx++]; 
    }

    bool hasNext(){
        return(_idx<_arr.size()); 
    } 

};  

/*方法2: 栈法迭代 
- 通过迭代的方式对二叉树做中序遍历。此时，我们无需预先计算出中序遍历的全部结果，只需要实时维护当前栈的情况即可。 
*/
class BSTIteratorStack{
    private: 
    TreeNode* cur; 
    stack<TreeNode*> stk; 

    public:  
    BSTIteratorStack(TreeNode* root): cur(root){} 

    int next(){
        while(cur!=nullptr){
            // 中序遍历找到最左侧 
            stk.push(cur); 
            cur=cur->left; 
        } 

        // 中序遍历: 左-中-右 
        cur = stk.top();  
        stk.pop(); 
        int res = cur->val; 
        cur = cur->right; 
        return res; // 总能return出值 
    }

    bool hasNext(){
        return !stk.empty() || cur!=nullptr; 
    }
    

};



// 写一个初始化TreeNode的脚本 
// 初始化 （层序） [7, 3, 15, null, null, 9, 20]  
// 使用数组存放 
TreeNode* initTreeNode(){
    TreeNode *root = new TreeNode(7); 
    TreeNode *node1 = new TreeNode(3); 
    TreeNode *node2 = new TreeNode(15); 
    TreeNode *node3 = new TreeNode(9); 
    TreeNode *node4 = new TreeNode(20);  

    root->left = node1; 
    root->right = node2; 
    node2->left = node3; 
    node2->right = node4;  

    return root; 
}
    
void test01_BSTIVec(){  
    // vector<int> nums = {7, 3, 15, null, null, 9, 20};  
    TreeNode *root = new TreeNode(7); 
    TreeNode *node1 = new TreeNode(3); 
    TreeNode *node2 = new TreeNode(15); 
    TreeNode *node3 = new TreeNode(9); 
    TreeNode *node4 = new TreeNode(20);  

    root->left = node1; 
    root->right = node2; 
    node2->left = node3; 
    node2->right = node4;   


    BSTIteratorVector bSTIterator(root);   

    cout << bSTIterator.next() << endl;    // 返回 3
    cout << bSTIterator.next() << endl;    // 返回 7
    cout << bSTIterator.hasNext() << endl; // 返回 True
    cout << bSTIterator.next() << endl;    // 返回 9
    cout << bSTIterator.hasNext() << endl;// 返回 True
    cout << bSTIterator.next() << endl;     // 返回 15
    cout << bSTIterator.hasNext() << endl; // 返回 True
    cout << bSTIterator.next() << endl;    // 返回 20
    cout << bSTIterator.hasNext() << endl; // 返回 False  

    // delete ; 
    delete root; 
    delete node1;
    delete node2;
    delete node3; 
    delete node4; 
} 


void test02_BSTIStk(){  
    // vector<int> nums = {7, 3, 15, null, null, 9, 20};  
    TreeNode *root = new TreeNode(7); 
    TreeNode *node1 = new TreeNode(3); 
    TreeNode *node2 = new TreeNode(15); 
    TreeNode *node3 = new TreeNode(9); 
    TreeNode *node4 = new TreeNode(20);  

    root->left = node1; 
    root->right = node2; 
    node2->left = node3; 
    node2->right = node4;   


    // BSTIteratorVector bSTIterator(root);   
    BSTIteratorStack bSTIterator(root);

    cout << bSTIterator.next() << endl;    // 返回 3
    cout << bSTIterator.next() << endl;    // 返回 7
    cout << bSTIterator.hasNext() << endl; // 返回 True
    cout << bSTIterator.next() << endl;    // 返回 9
    cout << bSTIterator.hasNext() << endl;// 返回 True
    cout << bSTIterator.next() << endl;     // 返回 15
    cout << bSTIterator.hasNext() << endl; // 返回 True
    cout << bSTIterator.next() << endl;    // 返回 20
    cout << bSTIterator.hasNext() << endl; // 返回 False  

    // delete ; 
    delete root; 
    delete node1;
    delete node2;
    delete node3; 
    delete node4; 
}


int main(){
    // test01_BSTIVec(); 
    test02_BSTIStk(); 
    return 0; 
}

