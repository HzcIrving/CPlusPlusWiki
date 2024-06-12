#pragma once 

/*
- 前置知识：二叉搜索树  
    【..\DataStructure\binary_search_tree.cpp】 

AVL Tree: 自平衡二叉搜索树  
- 二叉搜索树 多次插入& 删除， 退化为链表，此时所有操作的时间复杂度O(logN)->O(N) 
- AVL节点平衡因子 
    f = height(left) - height(right) 
    - 若一棵AVL树是平衡二叉树，则任意一个节点的平衡因子都在[-1,1]之间  
- AVL树旋转 
    - 对称性（左旋、右旋情况是对称的） 
    - 旋转操作，能够在不影响二叉树中序遍历序列的前提下，使得节点重新恢复平衡（即f∈[-1,1]) 
    - |f| > 1为失衡节点，依据节点失衡情况不同，分为：
        [右旋]、[左旋]、[先右旋再左旋]、[先左旋再右旋] 
    -------------------------------------------------
    失衡节点的平衡因子 | 子节点的平衡因子 | 旋转方法
        >1 左偏树          ≥0               右
        >1 左偏树          <0            先左后右
        <-1 右偏树         ≤0               左 
        <-1 右偏树         >0            先右后左
    ------------------------------------------------- 
    右旋:       f(3) = 2 - 0 = 2 
        4       => 右旋           4
      3   5                    1    5
    1                        0  3
  0 
    -------------------------------------------------
    先左后右:    f(3) = 2 - 0 = 2  f(1) = 0-1=-1 < 0
        4       => 左旋(child)    4    => 右旋(3)    4
      3   5                     3  5              2   5  
    1                         2                 1  3
      2                     1
-----------------------------
【应用】
    1. 组织和存储大型数据（高频查找、低频增删场景）  
    2. 构建数据库索引系统 
    3. 红黑树在许多应用中比AVL数更受欢迎，红黑树中插入和删除节点旋转操作更少，节点增删平均效率更高

*/
#include <iostream> 
#include <memory>  
#include <queue> 

using namespace std; 


struct AVLTreeNode{
    int val;   

    /*
    【节点高度height】 
    - 该节点，到最远叶子节点的距离，所需要经过“edge”的数量。 
    - 叶子节点高度为0 
    - 空节点高度为-1
    */
    int height; // 高度参数，AVL的特点，平衡判据  

    // 智能指针存放左右节点  
    shared_ptr<AVLTreeNode> left;  
    shared_ptr<AVLTreeNode> right;  

    // 默认构造 
    AVLTreeNode(): val(0), height(0), left(nullptr), right(nullptr){}  
    // 参数构造 
    AVLTreeNode(int val): val(val), height(0), left(nullptr), right(nullptr){} 
    // 拷贝构造 
    AVLTreeNode(const AVLTreeNode& node){
        this->val = node.val; 
        this->height = node.height; 
        this->left = node.left;
        this->right = node.right;
    }  

    // 构造重载 = 
    AVLTreeNode& operator=(const AVLTreeNode& node){
        this->val = node.val; 
        this->height = node.height; 
        this->left = node.left;
        this->right = node.right;
        return *this; 
    }
};   


// 设定命名空间 
// ADS: Advanced Data Structure
namespace ADS{ 
    class AVLTree{
        private:   
        shared_ptr<AVLTreeNode> root;
        


        public: 
            // 构造 
            AVLTree(int val){
                this->root = make_shared<AVLTreeNode>(val);
            }  

            AVLTree(){
                this->root = make_shared<AVLTreeNode>(); 
            }

            shared_ptr<AVLTreeNode> getAvlTree(); 

            // 工具函数，打印二叉树 
            static void printTree(const shared_ptr<AVLTreeNode> &root);  

            // 获取AVLTreeNode的height 
            int getHeight(const shared_ptr<AVLTreeNode> &node);  

            void printHeight(const shared_ptr<AVLTreeNode> &root); 

            // 更新AVLTreeNode的height --- update height  
            void updateHeight(const shared_ptr<AVLTreeNode> &node); 

            // 获取平衡因子 
            int getBalanceFactor(const shared_ptr<AVLTreeNode> &node);  

            // 右旋 
            shared_ptr<AVLTreeNode> rightRotate(shared_ptr<AVLTreeNode> &node); 

            // 左旋 
            shared_ptr<AVLTreeNode> leftRotate(shared_ptr<AVLTreeNode> &node);
            
            // 旋转恢复平衡二叉树  
            shared_ptr<AVLTreeNode> rotate(shared_ptr<AVLTreeNode> &node);


            /*-----------------------基础功能-------------------------*/ 
            // 增、删、改、查  
            // 查找节点  
            shared_ptr<AVLTreeNode> search(int val); 

            // 插入节点  
            void insert(int val);  
            shared_ptr<AVLTreeNode> insertHelper(shared_ptr<AVLTreeNode> &node,  int val); 
            
            // 删除节点  
            void remove(int val); 
            shared_ptr<AVLTreeNode> removeHelper(shared_ptr<AVLTreeNode> &node, int val);


    }; 
     
}





