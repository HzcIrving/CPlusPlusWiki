#include <iostream> 
#include <queue> 
#include <math.h> 
#include <chrono> 
#include <ctime>

using namespace std;  

/*
二叉树 -- 非线性数据结构 
- 代表“祖先”与“后代”之间的派生关系，体现了“一分为二”的分治逻辑。
- 二叉树的基本单元是节点，每个节点包含值、左子节点引用和右子节点引用。 

二叉树 -- 常见术语 
- 「根节点 root node」：位于二叉树顶层的节点，没有父节点。
- 「叶节点 leaf node」：没有子节点的节点，其两个指针均指向 None 。
- 「边 edge」：连接两个节点的线段，即节点引用（指针）。
- 节点所在的「层 level」：从顶至底递增，根节点所在层为 1 。-----------------------（起始level是1)
- 节点的「度 degree」：节点的子节点的数量。在二叉树中，度的取值范围是 0、1、2 。----（类比Graph的degree度的定义）
- 二叉树的「高度 height」：从根节点到最远叶节点所经过的边的数量。 
- 节点的「深度 depth」：从根节点到该节点所经过的边的数量。root to ...
- 节点的「高度 height」：从距离该节点最远的叶节点到该节点所经过的边的数量。... to leaf node 
-------------------------------------------------------------------
若深度/高度定义是节点数，则需要 + 1 

二叉树 -- 常见类型 
- 「完美二叉树/满二叉树 perfect binary tree」所有层的节点都被完全填满  （细胞分裂) 
    --  叶子节点的degree度 0 
    --  其余节点的degree度 2 
    --  若树的高度是h，则节点总数是2^(h+1)-1  
-  [完全二叉树 complete binary tree] 只有最底层的节点未被填满，且最底层节点尽量靠左填充。
-  [完满二叉树 full binary tree] 除了叶节点之外，其余所有节点都有两个子节点。   
- 「平衡二叉树 balanced binary tree」中任意节点的左子树和右子树的高度之差的绝对值不超过 1 。 
    -- Leetcode 110: https://leetcode.cn/problems/balanced-binary-tree/  

二叉树遍历
    - 「层序遍历 level-order traversal」从顶部到底部逐层遍历二叉树，并在每一层按照从左到右的顺序访问节点。
        
    - 
*/ 

/* 1. 二叉树节点结构体 */
struct TreeNode{
    int val; 
    TreeNode *left; 
    TreeNode *right; 

    // 构造形式 
    TreeNode(int x):val(x), left(nullptr), right(nullptr){}
    TreeNode(): val(0), left(nullptr), right(nullptr) {} // 默认构造 
    TreeNode(int x, TreeNode *left, TreeNode *right):val(x), left(left), right(right){}
};  

void PrintTreeByLevel(TreeNode *root);   

/* 2. 判断是否是平衡二叉树 https://leetcode.cn/problems/balanced-binary-tree/description/ 
中任意节点的左子树和右子树的深度之差的绝对值不超过 1  

TODO O(N)的方法，自底向下？
*/  
class isBalancedTreeSolve1{
    public: 
        /*
        思路：先序遍历 + 深度判断（自顶到底） 
        思路是构造一个获取当前子树的深度的函数 depth(root) ，通过比较某子树的左右子树的深度差 abs(depth(root.left) - depth(root.right)) <= 1 是否成立，
        来判断某子树是否是二叉平衡树。若所有子树都平衡，则此树平衡。 
        -------------------------------------
        此方法容易想到，但会产生大量重复计算，时间复杂度较高。

        - 时间复杂度O(NlogN) 
            1. 满二叉树高度复杂度O(logN) (因为满二叉树节点数N=2^h-1 ， 所以h=log(N+1))， 这将满二叉树分为log(N+1)层;   
            2. 调用depth，判断二叉树各层节点对应子树的层数
                    1 -- 第一层 , 遍历Nx1 
                  2  3 -- 第二层 ,  遍历 N-1/2 x 2个节点
                4  56  7 -- 第三层， 遍历 (N-1/2)-1 / 2 x 4 = N-3/4 x 4个节点 
                ........ -- 第H层  
               各层执行depth(root)复杂度 O(N) 
            3.时间复杂度 === 每层执行复杂度 ×\times× 层数复杂度 O(NlogN)
        */
        bool isBalanced(TreeNode *root){ 
            if(root == nullptr) return true; 
            return abs(this->depth(root->left) - this->depth(root->right)) <= 1 && this->isBalanced(root->left) && this->isBalanced(root->right);
        } 

        int depth(TreeNode *root){ 
            if(root == nullptr) return 0; 
            return max(depth(root->left), depth(root->right)) + 1; 
        } 
};   


/* 3. 二叉树遍历 ================================================================== */  
template<typename VectorType> 
class TreeNodeTraversal{
    // TreeNodeTraversal(){}; 

public:
    // 层序遍历C++ template，返回vector<T> 
    vector<VectorType> levelOrderTravelsal(TreeNode *root){ 
        /*
        层序遍历本质上属于「广度优先遍历 breadth-first traversal」，\
        也称「广度优先搜索 breadth-first search, BFS」 

        时间复杂度O(N)
        空间复杂度O(N) --- 最差满二叉树 
        */ 
        vector<VectorType> res; 
        // 初始化队列 
        queue<TreeNode*> que; 
        que.push(root); // 根节点  
        while(!que.empty()){
            TreeNode *node = que.front(); 
            que.pop();  
            res.emplace_back(node->val);  
            if(node->left != nullptr) que.emplace(node->left); 
            if(node->right != nullptr) que.emplace(node->right); 
        } 

        // print 
        cout << "levelOrderTravelsal: "; 
        for(auto &v: res) cout << v << " "; 
        cout << endl; 
        return res;    
    }

    /* 前序遍历 */
    void preOrder(TreeNode *root) { 

        if (root == nullptr)
            return;
        // 访问优先级：根节点 -> 左子树 -> 右子树
        vec.push_back(root->val);
        preOrder(root->left);
        preOrder(root->right); 
    }

    /* 中序遍历 */
    void inOrder(TreeNode *root) {
        if (root == nullptr)
            return;
        // 访问优先级：左子树 -> 根节点 -> 右子树
        inOrder(root->left);
        vec.push_back(root->val);
        inOrder(root->right);
    }

    /* 后序遍历 */
    void postOrder(TreeNode *root) {
        if (root == nullptr)
            return;
        // 访问优先级：左子树 -> 右子树 -> 根节点
        postOrder(root->left);
        postOrder(root->right);
        vec.push_back(root->val);
    }
    

private:
    vector<VectorType> vec; 

    
};

/* 2. 二叉树初始化 */ 
TreeNode* TreeNodeInit(){
    // 初始化节点 
    TreeNode *n1 = new TreeNode(1); 
    TreeNode *n2 = new TreeNode(2); 
    TreeNode *n3 = new TreeNode(3); 
    TreeNode *n4 = new TreeNode(4); 
    TreeNode *n5 = new TreeNode(5); 

    // 构建节点之间的引用（指针）
    n1->left = n2; 
    n1->right = n3; 
    n2->left = n4; 
    n2->right = n5;   
    PrintTreeByLevel(n1); 

    /* 3. 二叉树的插入与删除 
    与链表类似，在二叉树中插入与删除节点可以通过修改指针来实现。
    -----------------------------------------------------
    插入节点可能会改变二叉树的原有逻辑结构，而删除节点通常意味着删除该节点及其所有子树。 
    在二叉树中，插入与删除通常是由一套操作配合完成的，以实现有实际意义的操作。 
        1           1
       2 3   =>    p 3 
      4 5         2
                 4 5 
    */ 
    TreeNode *p = new TreeNode(666); 
    // n1,n2之间插入 p 
    n1->left = p; 
    p->left = n2; 
    PrintTreeByLevel(n1);  

    /* 4. 平衡二叉树判断 */
    // 实例化isBalancedTreeSolve1 
    isBalancedTreeSolve1 isBalancedTree; 
    cout << "isBalancedTree: " << isBalancedTree.isBalanced(n1) << endl; // 插入后False 


    // n1,n2之间删除p 
    n1->left = n2;  
    PrintTreeByLevel(n1);   
    cout << "isBalancedTree: " << isBalancedTree.isBalanced(n1) << endl; // 删除后True 

    /* 5. 层序遍历 */   
    TreeNodeTraversal<int> traversal;   
    clock_t start = clock(); 
    auto res_levelOrd = traversal.levelOrderTravelsal(n1);   
    clock_t end = clock();  
    cout << "levelOrder timeTest: " << ((double)(end - start) / CLOCKS_PER_SEC)*1000 << " /ms"<< endl;

    
    return n1; 
}

/* 3. 案例分析：基于数组写一个完全二叉树表示方法 ==================================================================
    - 完全二叉树非常适合使用数组来表示。 
    - 回顾完全二叉树的定义，None 只出现在最底层且靠右的位置，因此所有 None 一定出现在层序遍历序列的末尾。
功能1 
    - 给定某节点，获取它的值、左(右)子节点、父节点
功能2 
    - 前序
    - 中序
    - 后序
    - 层序 
*/ 
template <typename T> 
class ArrayBinaryTree{
    public: 
        /*构造*/ 
        ArrayBinaryTree(vector<T> arr){
            this->_tree = arr; 
        } 
        
        /*拷贝构造*/ 
        ArrayBinaryTree(const ArrayBinaryTree &other){
            this->_tree = other._tree; 
        } 

        /*功能1，获取索引值，左右节点*/ 
        auto val(int index){
            // 检测是否越界 , 抛出越界异常
            if(index < 0 || index >= this->_size()) return INT_MAX;  
            return this->_tree[index];  
        }  

        /*功能2， 获取index左右节点索引*/  
        int left(int index){
            return 2*index + 1;  
        } 

        int right(int index){
            return 2*index + 2; 
        } 

        /* 功能3：获取索引为i的父节点的索引 */  
        int parent(int index){
            return (index-1)/2; 
        }

        /* 功能4：层序遍历*/ 
        vector<T> levelOrder(){
            vector<T> res;  
            for(int i = 0; i<this->_tree.size(); i++){
                if(val(i) != INT_MAX){
                    res.push_back(val(i)); 
                }
            }

            return res;  
        } 

        /* 功能5, DFS多种遍历，前-中-后*/ 
        vector<T> preOrder(){
            vector<T> res; 
            _DFS(0, "pre", res); 
        } 
        vector<T> inOrder(){
            vector<T> res;
            _DFS(0, "in", res); 
        } 
        vector<T> postOrder(){
            vector<T> res; 
            _DFS(0, "post", res); 
        }

        void printTree(){
            for(int i = 0; i < _size(); i++){ 
                if(val(i) == INT_MAX){
                    cout << "None" << " ";  
                    continue;
                }
                cout << val(i) << " "; 
            }cout << endl; 
        }

    private:  
        vector<T> _tree;  

        /*列表容量*/
        int _size(){
            return _tree.size(); 
        }  

        /*DFS*/
        void _DFS(int i, string order, vector<T> &res){
            // 为空  
            if(val(i) == INT_MAX){
                return; 
            } 
            // 前序 中-左-右
            if(order == "pre"){
                res.emplace_back(val(i));  
            }  
            _DFS(left(i), order, res); 
            // 中序 左-中-右  
            if(order == "in"){
                res.emplace_back(val(i)); 
            }
            _DFS(right(i), order,res(i));
            if(order == "post"){
                // 后序 
                res.emplace_back(val(i));
            }
        }       
};






int main(){ 
    TreeNode *root = TreeNodeInit(); 
    
    // 测试ArrayBinaryTree各项功能  
    vector<int> arr = {1,2,3,4,INT_MAX,5,6}; 
    ArrayBinaryTree<int> arrTree(arr);   
    arrTree.printTree();


    // 释放二叉树内存 
    delete root; 
    
    return 0;  

     
}


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
