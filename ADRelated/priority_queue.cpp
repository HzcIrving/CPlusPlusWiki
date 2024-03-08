/*
- 规控常用优先级队列 (Hybrid A*) 
    https://mp.weixin.qq.com/s/7-i2RNIgNfWxPvXr7Eisaw 

- 会写重载的操作符()，知道底层实现原理  

1. 基本原理 
- std::priority_queue 在 C++ STL 中用于管理按优先级排序的元素，默认实现为最大堆，可以通过自定义比较函数修改排序方式
- 通常用二叉堆实现
  -- 插入和删除操作的时间复杂度为 O(log n)，访问顶部元素的时间复杂度为 O(1)，空间复杂度为 O(n) 
  
2. AD应用 
- 混合A*算法应用：在混合A*算法中，优先级队列用于按成本排序存储节点，以决定探索顺序，有效地找到最优路径。
*/ 

#include <iostream> 
#include <queue> 
#include <vector>