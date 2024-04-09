#include <iostream> 
#include <queue> 
#include <math.h> 
#include <chrono> 
#include <ctime>

using namespace std;   

struct TreeNode{
    int val; 
    TreeNode *left; 
    TreeNode *right; 

    // 构造形式 
    TreeNode(int x):val(x), left(nullptr), right(nullptr){}
    TreeNode(): val(0), left(nullptr), right(nullptr) {} // 默认构造 
    TreeNode(int x, TreeNode *left, TreeNode *right):val(x), left(left), right(right){}
};  

/* 
4. 二叉搜索树 Binary Search Tree 
    - 对于根节点，左子树中所有节点的值 < 根节点的值 < 右子树中所有节点的值。 
    - 任意节点的左、右子树也是二叉搜索树，满足上述条件   
    - 二叉搜索树中序遍历递增  
*/ 
template <class T>  
class BinarySearchTree{
public:  
    /*
    构造，构造二叉搜索树
    */
    BinarySearchTree(){}   

    /*【operation_1】搜
    查找节点，类似于二分法，每次可以排除一半的树，循环次数最多为二叉树深度，
    因此时间复杂度O(logN)
    */   
    TreeNode *Search(TreeNode *root, T val){
        TreeNode *cur = root; 
        // 检测非空
        while(cur != nullptr){
            // cur.val > val 目标节点在左子树 
            if(cur->val > val){
                cur = cur->left; 
            }else if(cur->val < val){
                cur = cur->right; 
            }else{
                return cur; 
            } 
        }   
        return nullptr; 
    } 

    /*【operation_2】插
    给定一个带插入元素，保持二叉搜索树"左子树<根节点<右子树"性质  
    1. 查找插入位置 
       根节点出发，根据当前节点值和num大小关系循环向下搜索，直到越过叶子节点时（遍
       历到None）跳出循环  O(logN)
    2. 插入节点 O(常数)   -> O(logN) 
    -----------------------------------------------------------------
    边界条件
    1. 不能够出现重复节点 , 存在树中，则直接break ，返回
    2. 为了实现插入节点，我们需要借助节点 pre 保存上一轮循环的节点。
       这样在遍历至 None 时，我们可以获取到其父节点，从而完成节点插入操作。
    3. 可以通过插入函数，来构造二叉搜索树 
    */
    void Insert(T num){
        cout << "插入前树结构:------------" << endl;     
        PrintBST(root); 

        // 检测节点是否为空  
        if (root == nullptr){ 
            // 初始化一个TreeNode 
            root = new TreeNode(num);
            return;
        }  
        // 循环检查  
        TreeNode *cur = root;   
        TreeNode *prev = nullptr;
        while(cur != nullptr){
            // 重复，直接return  
            if(cur->val == num){
                return; 
            }  
            prev = cur; 
            if(cur->val < num){
                // 位置在cur右边  
                cur = cur->right; 
            }else{
                // 位置在cul左边  
                cur = cur->left;
            }
        }

        // 此时cur已经到达合适位置 , 可以进行插入 
        TreeNode *node = new TreeNode(num); 
        if(prev->val < num){
            prev->right = node; 
        }else{
            prev->left = node;
        }
        
        cout << "插入后树结构:------------" << endl;     
        PrintBST(root); 

    }
    
    /*【operation_3】删
    先搜，在删，与插入类似，要保证 "左<中<右" 的特性  
    -------------------------------------------
    1. 删除节点度为0，叶节点，直接删去  
    2. 删除节点度为1，将待删除节点替换为子节点即可(只有一个子节点，无需维护顺序) 
    3. **** 最难: 当删除节点度为2，不能直接删除，需要使用后续节点替换该节点，因为“左<中<右” 
        1) 可以取右子树的最小节点
        2) 可以取左子树的最大节点 
    -------------------------------------------
    流程:(右子树最小准则)
    1. 找到待删除节点在“中序遍历序列”中的下一个节点，记为 tmp; 
    2. 用tmp值覆盖待删除节点，并在子树中递归删除节点 
    */ 
    void Remove(T num){
        cout << "删除前树结构:------------" << endl;    
        PrintBST(root);  

        // 检查是否为空 
        if(root == nullptr){
            cout << "空树" << endl; 
            return;  
        } 

        TreeNode *cur = root; // 拷贝构造  
        TreeNode *prev = nullptr; 

        while(cur != nullptr){
            if(cur->val == num){
                break;
            }  
            prev = cur; 
            if(cur->val < num){ // 待删除在右子树
                cur = cur->right; 
            }else{ // 待删除在左子树 
                cur = cur->left; 
            }
        }
        // 无待删除节点，直接返回
        if(cur == nullptr){
            return;
        }
        // 子节点度为0/1  
        if(cur->left == nullptr && cur->right == nullptr){
            TreeNode *child = cur->left != nullptr ? cur->left : cur->right;  
            if(cur!=root){ // 删除节点不为根节点 
                if(prev->left == cur){
                    prev->left = child; 
                }else{
                    prev->right = child;
                }
            }else{ 
                root = child; 
            }    // 删除节点为根节点
            
            // 释放内存 
            delete cur;  
        } else { // 子节点度为2 
            TreeNode *tmp = cur->right; 
            while(tmp->left != nullptr){
                tmp = tmp->left;
            } 
            int tmpVal = tmp->val;  
            // 递归删除节点tmp 
            Remove(tmp->val);   
            // 用tmp覆盖cur 
            cur->val = tmpVal; 
        }
    }

    /*中序遍历，并打印有序数组*/ 
    void InOrderPrint(vector<T> &res){ 
        InOrderPrint(root, res); 
        for(int i = 0; i < res.size(); i++){
            cout << res[i] << " "; 
        }
        cout << endl; 
    }

    /*按层打印树*/ 
    void PrintBST(TreeNode *root){ 
        queue<TreeNode*> q; 
        q.push(root); 
        while(!q.empty()){
            TreeNode *cur = q.front(); 
            q.pop(); 
            cout << cur->val << " "; 
            if(cur->left != nullptr){
                q.push(cur->left); 
            }
            if(cur->right != nullptr){
                q.push(cur->right); 
            }
        }
    }

private:   
    TreeNode *root = nullptr;
    

}; 

int main(){
    // 为BinarySearchTree写测试用例
    BinarySearchTree<int> bst; 
    bst.Insert(10); 
    bst.Insert(5);
    bst.Insert(15); 
    bst.Insert(7); 
    bst.Insert(11); 
    
    vector<int> res;
    bst.InOrderPrint(res); 


    return 0; 
}