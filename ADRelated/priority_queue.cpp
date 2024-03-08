/*
- 规控常用优先级队列 (Hybrid A*) 
    https://mp.weixin.qq.com/s/7-i2RNIgNfWxPvXr7Eisaw 

- 会写重载的操作符()，知道底层实现原理  

1. 基本原理 
- std::priority_queue 在 C++ STL 中用于管理按优先级排序的元素，默认实现为最大堆，可以通过自定义比较函数修改排序方式
- 优先级队列通过堆这一数据结构提供了高效的元素管理能力，特别是对于需要频繁进行插入和删除最值操作的场景。它的主要优势在于能够在对数时间内完成插入和删除最值操作，以及在常数时间内访问最值元素，使其成为许多算法（如Dijkstra算法、Huffman编码等）中不可或缺的组成部分。 
  
2. AD应用 
- 混合A*算法应用：在混合A*算法中，优先级队列用于按成本排序存储节点，以决定探索顺序，有效地找到最优路径。 

3. 优先级队列的实现和效率分析 
- 它的每个元素都有一个优先级与之关联，元素的出队顺序是根据优先级来决定的，而不是它们进入队列的顺序。 
- 堆（Heap）的基本概念
    1) 堆是一种特殊的完全二叉树，它满足以下性质：
    2) 堆性质：对于最大堆，任意节点的值都大于或等于其子节点的值；对于最小堆，任意节点的值都小于或等于其子节点的值。
    3) 结构性质：除最后一层外，堆是完全填满的，且最后一层从左到右填充。 

4. 时间复杂度 
- 插入push O(log n)  
  插入操作首先将新元素添加到堆的末尾（即完全二叉树的最后一个位置），然后通过一系列的上浮（或称为上滤、堆化向上）操作，将其移动到正确的位置以保持堆的性质。这个过程的时间复杂度为O(log n)，其中n是堆中元素的数量。 
- 删除最大元（或最小元，pop）O(log n)   
  在最大堆中删除最大元素，或在最小堆中删除最小元素，通常是删除堆顶元素。删除后，将堆的最后一个元素移动到堆顶，然后通过一系列的下沉（或称为下滤、堆化向下）操作，将其移动到正确的位置以保持堆的性质。这个过程的时间复杂度也是O(log n)。 
- 查找最大元（最小元, top) O(1)
  由于堆的性质，最大元素（在最大堆中）或最小元素（在最小堆中）总是位于堆顶，因此这个操作的时间复杂度是O(1)。 

5. 空间复杂度 O(n) 
*/ 

#include <iostream> 
#include <string>
#include <queue> 
#include <vector>  

using namespace std;

// 1. 优先级队列的比较对象<int,float,double,etc> 
struct NormalMinHeapComparator { 
    template <typename T> 
    bool operator()(const T& a, const T& b) { 
        return a < b; 
    } 
}; 

// 2. 自定义类型， 自己有一个类，将这个类作为优先级队列的元素 
class Task{
public: 
    Task(double priority, string description): priority(priority), description(description){};
    double priority; 
    string description;
};  

struct TaskComparator{
    bool operator()(const Task& a, const Task &b){
        return a.priority > b.priority; 
    }
};

int main(){  
    // 1 ---------------------------------------------- 
    std::priority_queue<int, std::vector<int>, NormalMinHeapComparator> pInt; 
    std::priority_queue<float, std::vector<float>, NormalMinHeapComparator> pFloat; 
    std::priority_queue<Task, std::vector<Task>, TaskComparator> pTask;

    // 比较Int
    pInt.push(10); 
    pInt.push(2);
    pInt.push(5);  

    // 比较float 
    pFloat.push(10.0);
    pFloat.push(2.5);
    pFloat.push(0.2);
    pFloat.push(20.3);  

    // 遍历pInt，并移除顶部
    // for(auto& i : pInt){
    //     std::cout << i << " "; 
    // } std::cout << std::endl;  
    while(!pInt.empty()){
        std::cout << pInt.top() << " ";  // 10, 5, 2
        pInt.pop();
    } std::cout << std::endl;
    
    while(!pFloat.empty()){
        
        std::cout << pFloat.top() << " "; // 20.3 10 2.5 0.2
        pFloat.pop();
    } std::cout << std::endl;

    // 2. --------------------------------------------------
    pTask.emplace(10, "Low"); 
    pTask.emplace(20, "Mid"); 
    pTask.emplace(30, "High");  

    while(!pTask.empty()){
        std::cout << pTask.top().priority << " " << pTask.top().description << std::endl; 
        pTask.pop(); 
    } // 10, 20, 30 

    return 0; 
}