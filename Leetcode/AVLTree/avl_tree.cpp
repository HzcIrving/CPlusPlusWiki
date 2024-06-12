#include "avl_tree.h" 
#include <queue> 
using namespace std; 

namespace ADS{

    shared_ptr<AVLTreeNode> AVLTree::getAvlTree(){
        return root; 
    }

    // 工具函数 PrintTree 
    // BFS层序打印
    // 若没有left node或者right node，打印"nan" 
    void AVLTree::printTree(const shared_ptr<AVLTreeNode> &root){
        if(root == nullptr){
            return;  
        } 
        queue<shared_ptr<AVLTreeNode>> q;  // FIFO    
        q.push(root); 
        while(!q.empty()){
            auto cur = q.front(); // FIFO 
            q.pop();   

            if (cur->val == 0){
                cout << "nan "; 
                continue;
            
            }
            cout << cur->val << " ";  

            if(cur->left != nullptr){
                q.push(cur->left); 
            } 

            if(cur->right != nullptr){
                q.push(cur->right);
            }
        
        } cout << endl;  
    } 

    // 获取节点高度 
    int AVLTree::getHeight(const shared_ptr<AVLTreeNode> &node){
        if(node == nullptr){
            return -1; 
        } 

        return node->height; 
    }   


    void AVLTree::printHeight(const shared_ptr<AVLTreeNode> &root){  

        if(root==nullptr){
            // cout << "[None]:[-1]" <<endl; 
            return; 
        }

        // 中序遍历打印 
        this->printHeight(root->left); 
        cout << "[" << root->val << "]:[" << this->getHeight(root) << "]"<< endl;  
        this->printHeight(root->right);   

        return; 
    }

    // 更新节点的高度 
    void AVLTree::updateHeight(const shared_ptr<AVLTreeNode> &node){
        if(node == nullptr){
            return; 
        }  
        node->height = max(this->getHeight(node->left), this->getHeight(node->right))+1; 

    }

    // 平衡因子
    int AVLTree::getBalanceFactor(const shared_ptr<AVLTreeNode> &node){ 
        if(node == nullptr){
            return 0; 
        }  

        // 节点平衡因子 = 左子树高度 - 右子树高度 
        return this->getHeight(node->left) - this->getHeight(node->right);
    } 

    // 旋转恢复平衡二叉树（不影响中序遍历序列）  
    // 1. 右旋函数  
    /*
    右旋需要判断是否有grand_child 
    (1) 没有grand_child 
        右旋:       f(3) = 2 - 0 = 2 
        4       => 右旋           4
      3   5                    1    5
    1                        0  3
  0  

    (2) 有grand_child 
         5    失效节点是f(5)=3-1=2   
       3  6    =>  右旋         3 
     1  4                     1  5
   0                        0    4 6
    */
    shared_ptr<AVLTreeNode> AVLTree::rightRotate(shared_ptr<AVLTreeNode> &node){
        shared_ptr<AVLTreeNode> child = node->left;   
        shared_ptr<AVLTreeNode> grand_child = child->right; 

        // 以child为原点，将node右旋 
        child->right = node;  
        node->left = grand_child; // 若为None也无所谓了   

        // 更新节点高度  
        this->updateHeight(node); 
        this->updateHeight(child);  

        // 无论是否有grad_child，最后都会以child代替node
        return child;
    }

    // 2. 左旋函数类似 
    shared_ptr<AVLTreeNode> AVLTree::leftRotate(shared_ptr<AVLTreeNode> &node){
        shared_ptr<AVLTreeNode> child = node->right;
        shared_ptr<AVLTreeNode> grand_child = child->left;
        child->left = node;
        node->right = grand_child; 
        this->updateHeight(node); 
        this->updateHeight(child);  
        return child; 
    }

    shared_ptr<AVLTreeNode> AVLTree::rotate(shared_ptr<AVLTreeNode> &node){ 
        /*旋转，使得子树恢复平衡*/ 
        // step1:获取节点node的平衡因子 
        int balanceFactor = this->getBalanceFactor(node);  

        // step2:判断非平衡状态 
        if(balanceFactor > 1){ // 左偏树
            if(this->getBalanceFactor(node->left)>=0){
                // 右旋 
                return this->rightRotate(node); 
            }else{
                // f(child) < 0, 先左旋在右旋 
                node->left = this->leftRotate(node->left); 
                return this->rightRotate(node); 
            } 
        }else if(balanceFactor < -1) // 右偏树
        {
            if(this->getBalanceFactor(node->right) <= 0){
                // 左旋 
                return this->leftRotate(node);
            }else{
                // f(child) > 0, 先右旋在左旋 
                node->right = this->rightRotate(node->right); 
                return this->leftRotate(node);
            }
        }

        // step3：若未进入上述流程，说明已经是平衡数，无需旋转，直接返回即可  
        return node; 
    } 

    /*-----------------------基础功能-------------------------*/ 
    // 增、删、改、查  
    // 查找节点   
    shared_ptr<AVLTreeNode> AVLTree::search(int val){
        shared_ptr<AVLTreeNode> cur = this->root; 
        while(cur != nullptr){
            if(cur->val == val){
                return cur;  
            }else if(cur->val > val){
                cur = cur->left; 
            }else{
                cur = cur->right; 
            }
        } 

        cout << "节点不存在" << endl; 
        return nullptr; 
    }  

    // 插入节点 
    void AVLTree::insert(int val){ 
        cout << "Before Insert: " << endl;  
        this->printTree(this->root);   
        this->root = this->insertHelper(this->root, val);  
        cout << "After Insert: " << endl;   
        this->printTree(this->root);   
        cout << "-------------------" << endl; 
    } 

    // 插入辅助 -> 递归插入 
    // 插入节点可能会出现失衡节点 
    // 需要从插入节点开始，自底向上进行旋转，使得失衡节点平衡  
    shared_ptr<AVLTreeNode> AVLTree::insertHelper(shared_ptr<AVLTreeNode> &node, int val){
        if(node == nullptr){
            return make_shared<AVLTreeNode>(val);
        } 

        // 1. 查找插入位置 
        if(val<node->val){
            node->left = this->insertHelper(node->left, val);
        }else if(val>node->val){
            node->right = this->insertHelper(node->right, val);  
        }else{
            // 重复节点，直接返回 
            return node; 
        } 

        // 2. 更新节点高度
        this->updateHeight(node); 
        // 3. 旋转恢复平衡
        return this->rotate(node);
    
    }  

    // 删除节点
    // 基于二叉搜索树的删除节点方法基础上进行优化：
    // --- 检查节点，并旋转失衡节点   
    void AVLTree::remove(int val){
        this->removeHelper(root, val);
    } 

    shared_ptr<AVLTreeNode> AVLTree::removeHelper(shared_ptr<AVLTreeNode> &node, int val){
        // 空? 
        if(node == nullptr){
            cout << "空树" << endl; 
            return nullptr; 
        }  

        if(val < node->val){
            node->left = this->removeHelper(node->left, val);
        } 
        else if(val > node->val){
            node->right = this->removeHelper(node->right, val); 
        }else{
            // 二叉搜索树 分情况讨论  
            //子节点度为0/1  
            if(node->left == nullptr || node->right == nullptr){  
                shared_ptr<AVLTreeNode> child = node->left != nullptr ? node->left : node->right;

                // 空，度为0
                if(child==nullptr){
                    return nullptr; 
                }
                else{
                    node = child;  // 用node->left替换当前node 
                }
            }
            // 度为2  
            // 中序遍历下个节点删除，并用该节点替换当前节点  
            /*
            https://www.hello-algo.com/chapter_tree/binary_search_tree/#743                 
            */
            else{
                shared_ptr<AVLTreeNode> suc = node->right; 
                while(suc->left!=nullptr){
                    suc = suc->left; 
                }
                int sucVal = suc->val; 
                // 递归删除后继节点   
                node->right = this->removeHelper(node->right, sucVal);  
                node->val = sucVal;
            }    
        }

        // 更新节点高度 
        this->updateHeight(node); 
        // 递归旋转，平衡  
        node = this->rotate(node); 

        // 返回子树根节点
        return node; 
    }

} // namespace ADS(Advanced Data Structure)


void TestPrint(){ 
    // 构建一个eval树  
    /*
            4
          2   6 
        1  nan   5  7   
    
    */
    shared_ptr<AVLTreeNode> tree = make_shared<AVLTreeNode>(4); // 不考虑height  
    tree->left = make_shared<AVLTreeNode>(2); 
    tree->right = make_shared<AVLTreeNode>(6); 

    tree->left->left = make_shared<AVLTreeNode>(1);  
    tree->left->right = make_shared<AVLTreeNode>(); // 空
    tree->right->left = make_shared<AVLTreeNode>(5); 
    tree->right->right = make_shared<AVLTreeNode>(7); 
    
    // 实例化 s
    ADS::AVLTree::printTree(tree); 

    return; 
}

void TestHeight(){ 

    // 基于插入构造AVLTree 
    ADS::AVLTree avlTree(5); 
    avlTree.insert(4);   
    avlTree.insert(6);
    avlTree.insert(1); 
    avlTree.insert(2); 
    // avlTree
    shared_ptr<AVLTreeNode> root = avlTree.getAvlTree(); 
    avlTree.printHeight(root);

    return; 
}  

void TestRotate(){
    return; 
};  

void TestBasicFunc(){
    // 测试增删改查  
    return; 
}

int main(){
    // TestPrint(); 
    TestHeight();
    return 0; 
}