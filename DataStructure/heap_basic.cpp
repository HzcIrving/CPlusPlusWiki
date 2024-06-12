/*
堆 HEAP  
- 一种满足特定条件的完全二叉树  
-  1) 小顶堆 (Min Heap)： 任意节点的值 ≤ 其子节点的值 
-  2) 大顶堆 (Max Heap)： 任意节点的值 ≥ 其子节点的值  

【特性1】 
- 完全二叉树的特例 
- i. 最底层节点靠左填充，其他层的节点被填满 
- ii. root -> “堆顶” 
- iii. 最底层靠右的leaf -> "堆底"  
- iv. Min Heap：root最小 
- v. Max Heap：root最大 

【常用操作】 
- G:\CplusWorks\ADRelated\priority_queue.cpp 优先级队列  (STL实现: std::priority_queue)
- Max Heap： 大顶堆相当于元素按从大到小的顺序出队的优先队列。
    从使用角度来看，我们可以将“优先队列”和“堆”看作等价的数据结构

- push() 入堆 O(logN) 
- pop() 出堆 O(logN) 
- peek() 访问堆顶元素（对于大 / 小顶堆分别为最大 / 小值） O(1) 
- size() 获取堆的元素数量  O(1)
- isEmpty() 判断堆是否为空 O(1)

在实际应用中，我们可以直接使用编程语言提供的堆类（或优先队列类）。 
- 具体看：G:\CplusWorks\ADRelated\priority_queue.cpp 

【堆的实现】 
- 以max heap为例 
- 若要实现小顶堆，需要将所有大小逻辑判断进行旋转即可（即 ≥ -> ≤ ）  
- 完全二叉树适合用数组实现  ---- G:\CplusWorks\DataStructure\tree_node_basic.cpp Line233 
---------------------------------------------------------------------------------------
None 只出现在最底层且靠右的位置，因此所有 None 一定出现在层序遍历序列的末尾。
---------------------------------------------------------------------------------------
    给定索引i，其左子节点为2i+1,右子节点为2i+2； 
        - 需要判定索引是否越界  
    索引i对应的父节点: (i-1)/2 (若存在)  
- 难点1：入堆  √√√
  -------------------------------------------------------------------------------------
  给定元素 val ，我们首先将其添加到堆底。添加之后，由于 val 可能大于堆中其他元素，
  堆的成立条件可能已被破坏，因此需要修复从插入节点到根节点的路径上的各个节点，这个
  操作被称为堆化（heapify）。

  考虑从入堆节点开始，从底至顶执行堆化。我们比较插入节点与其父节点的值，如果插入节
  点更大，则将它们交换。然后继续执行此操作，从底至顶修复堆中的各个节点，直至越过根
  节点或遇到无须交换的节点时结束。
  -------------------------------------------------------------------------------------

- 难点2：栈顶出堆  √√√√ 
    堆顶元素是二叉树的根节点，即列表首元素。如果我们直接从列表中删除首元素，那么二叉树中所
    有节点的索引都会发生变化，这将使得后续使用堆化进行修复变得困难。
    
    为了尽量减少元素索引的变动，我们采用以下操作步骤。
    ----------------------------------------------------------------------------------
    1. 交换堆顶元素与堆底元素（交换根节点与最右叶节点）。
    2. 交换完成后，将堆底从列表中删除（注意，由于已经交换，因此实际上删除的是原来的堆顶元素）。
    3. 从根节点开始，从顶至底执行堆化。
    “从顶至底堆化”的操作方向与“从底至顶堆化”相反，我们将根节点的值与其两个子节点的值进行比较，
    将最大的子节点与根节点交换。然后循环执行此操作，直到越过叶节点或遇到无须交换的节点时结束。
    ----------------------------------------------------------------------------------
    堆化heapify完成以后，大顶堆性质被修复  

*/ 

/*
基于数组实现最大堆 
*/
#include <iostream> 
#include <vector>  
#include <stdexcept>  
using namespace std; 

template<typename T>
class MaxHeap{
    /*基于数组实现的最大堆*/  
    private:
        vector<T> maxHeap_; 
        int size_;  
        int getSize_(){
            return maxHeap_.size(); 
        }

    public: 

        int getSize(){
            return maxHeap_.size();
        }

        // 输出堆 （数组形式） 
        void print(){
            // 迭代器打印vector 
            // for(auto it = maxHeap_.begin(); it!=maxHeap_.end(); it++){ 
            //     cout << *it << " "; 
            // } 
            // cout << endl;  

            // auto新特性打印 
            for(auto it : maxHeap_){ 
                cout << it << " "; 
            } cout << endl; 
        }
        
        // 构造
        MaxHeap(vector<T> &arr){
            this->maxHeap_ = arr;  
            this->size_ = arr.size(); 
        } 

        // 拷贝构造
        MaxHeap(const MaxHeap &maxHeap){ 
            this->maxHeap_ = maxHeap.maxHeap_;  
            this->size_ = maxHeap.size_;
        }  

        // 默认构造 
        MaxHeap(){
            this->size_ = 0; 
        } 

        // 功能1（完美二叉树数组实现方法中） 
        /*根据索引获取值*/ 
        T val(int index){
            // 检测是否越界 
            if(index < 0 || index >= this->size_) throw "index out of range"; 
            return this->maxHeap_[index]; 
        } 

        /*获取堆中节点i的左右子节点索引, 
        or父节点索引*/ 
        T getLeft(int i){
            return 2*i + 1; 
        } 

        T getRight(int i){
            return 2*i + 2; 
        } 

        T getParent(int i){
            return (i-1)/2; 
        }

        /*访问堆顶元素*/ 
        T getPeek(){
            return this->maxHeap_[0]; 
        }



        /*元素入堆
        O(logN)
        */ 
        void push(T val); 
        void pushUpHeapify(int i); 

        /*栈顶元素出堆
        O(logN)
        */ 
        // pop出priority最大的那个  
        void pop();   
        void popDownHeapify(int i);  




};

template <typename T>
void MaxHeap<T>::push(T val){ 
    // Step1. 添加 
    this->maxHeap_.push_back(val);   

    // Step2. 堆化 (类似于重排, 子底向上)
    // 时间复杂度 O(logN) 
    // 为什么时间复杂度是 O(logN)  
    this->pushUpHeapify(this->maxHeap_.size() - 1);
}

template <typename T>
void MaxHeap<T>::pushUpHeapify(int i){
    while (true){
        // 获取i的父节点 
        int p = this->getParent(i);  
        // 当“越过根节点”或“节点无须修复”时，结束堆化 
        if(p < 0 || this->maxHeap_[p] >= this->maxHeap_[i]) break; 
        swap(this->maxHeap_[i], this->maxHeap_[p]); 
        // 向上Heapify 
        i = p; 
    }
} 

template <typename T>
void MaxHeap<T>::pop(){
    //Step1. 判空 
    if(this->getSize_() == 0) throw "heap is empty";  

    //Step2. 交换Root与最右元素 
    swap(this->maxHeap_[0], this->maxHeap_[this->getSize_() - 1]); 

    // Step3. 删除节点 
    this->maxHeap_.pop_back(); 

    // Step4. 从顶至底Heapify  
    this->popDownHeapify(0);
}  

template <typename T>
void MaxHeap<T>::popDownHeapify(int i){  
    while(true){
        int L = this->getLeft(i); 
        int R = this->getRight(i); 
        int M = i;  

        if(L < this->getSize_() && this->maxHeap_[L] > this->maxHeap_[M]) M = L;  
        if(R < this->getSize_() && this->maxHeap_[R] > this->maxHeap_[M]) M = R; 
        
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出  
        // 这一步的位置是为了保证最大堆的特性 
        if(M == i) break;   
        swap(this->maxHeap_[i], this->maxHeap_[M]); 
        i = M;  
    }
} 


void heapTest(){
    // 基于vector初始化堆 
    vector<int> arr = {9,8,6,6,7,5,2,1,4,3,6,2};  

    // 实例化堆 
    MaxHeap<int> maxHeap(arr);  

    // 属性打印 
    cout << "堆中元素："; 
    maxHeap.print(); 

    cout << "尺寸:" ; 
    cout << maxHeap.getSize() << endl;  

    cout << "Peek:"; 
    cout << maxHeap.getPeek() << endl; 

    cout << "7入堆-------------" << endl; 
    cout << "before:"; 
    maxHeap.print(); 
    maxHeap.push(7); 
    cout << "after:"; 
    maxHeap.print(); 

    cout << "Peek出堆测试---------------" << endl;  
    cout << "before:"; 
    maxHeap.print();
    maxHeap.pop();
    cout << "after:";
    maxHeap.print(); 


} 

int main(){
    heapTest();   
    return 0; 
}