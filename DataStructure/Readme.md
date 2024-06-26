## 1. 数组vs.链表 

|| 数组 | 链表 |
|:-----------:|:-----------:|:-----------:|
|存储方式| 连续内存空间 | 分散内存空间| 
|容量扩展| 长度不可变 | 可灵活扩展 |
|内存效率| 元素占用内存少|元素占用内存多(val和ptr)| 
|访问元素| $\mathcal{O}(1)$ |  $\mathcal{O}(n)$ | 
|添加元素| $\mathcal{O}(n)$ |  $\mathcal{O}(1)$ | 
|删除元素| $\mathcal{O}(n)$ |  $\mathcal{O}(1)$ | 
|||

数组可提供更高的内存空间效率，而链表则在内存使用上更加灵活。

### 1.1 重点 
- 数组和链表是两种基本的数据结构，分别代表数据在计算机内存中的两种存储方式：连续空间存储和分散空间存储。
- 两者的特点呈现出互补的特性。 
- 数组支持随机访问、占用内存较少；但插入和删除元素效率低，且初始化后长度不可变。 
- 链表通过更改引用（指针）实现高效的节点插入与删除，且可以灵活调整长度；但节点访问效率低、占用内存较多。
- 常见的链表类型包括单向链表、环形链表、双向链表。 
- 列表是一种支持增删查改的元素有序集合，通常基于动态数组实现。它保留了数组的优势，同时可以灵活调整长度。 
- 列表的出现大幅提高了数组的实用性，但可能导致部分内存空间浪费。 
- 程序运行时，数据主要存储在内存中。数组可提供更高的内存空间效率，而链表则在内存使用上更加灵活。 
- 缓存通过缓存行、预取机制以及空间局部性和时间局部性等数据加载机制，为 CPU 提供快速数据访问，显著提升程序的执行效率。 
- 由于数组具有更高的缓存命中率，因此它通常比链表更高效。在选择数据结构时，应根据具体需求和场 景做出恰当选择。 

## 2. 二叉树的最佳结构与最差结构
- 完美二叉树是理想情况，可以充分发挥二叉树“分治”的优势。
- 链表则是另一个极端，各项操作都变为线性操作，时间复杂度退化至$\mathcal{O}_n$ 

| | 完美二叉树 | 链表 |
|:-----------:|:-----------:|:-----------:|
|第$i$层节点数| $2^{i-1}$(第一层为1) | 1| 
|高度为$h$的树的叶节点总数| $2^h$ | 1 |
|高度为$h$的树的节点总数| $2^{h+1}-1$$|$h+1$| 
|节点数为$n$的树的高度| $log_2(n+1)-1$ |  $n-1$ | 
||| 

- 二叉树的数组表示  
  - 数组存储在连续的内存空间中，对**缓存友好**，访问与遍历速度较快。
  - 不需要存储指针，比较节省空间。
  - 允许随机访问节点。

- 数组表示也存在一些局限性。
  - 数组存储需要连续内存空间，因此不适合存储数据量过大的树。
  - 增删节点需要通过数组插入与删除操作实现，效率较低。
  - 当二叉树中存在大量 None 时，数组中包含的节点数据比重较低，空间利用率较低。 


## 3. 图
- `graph_basic.cpp` 
- `graph_common_algo.cpp`  


``` 
1) 图由顶点和边组成，可以表示为一组顶点和一组边构成的集合。
2) 相较于线性关系（链表）和分治关系（树），网络关系（图）具有更高的自由度，因而更为复杂。
3) 有向图的边具有方向性，连通图中的任意顶点均可达，有权图的每条边都包含权重变量。
4) 邻接矩阵利用矩阵来表示图，每一行（列）代表一个顶点，矩阵元素代表边，用1或0表示两个顶点之间有边或无边。邻接矩阵在增删查改操作上效率很高，但空间占用较多。
5) 邻接表使用多个链表来表示图，第i个链表对应顶点i，其中存储了该顶点的所有邻接顶点。邻接表相对于邻接矩阵更加节省空间，但由于需要遍历链表来查找边，因此时间效率较低。
6) 当邻接表中的链表过长时，可以将其转换为红黑树或哈希表，从而提升查询效率。
7) 从算法思想的角度分析，邻接矩阵体现了“以空间换时间”，邻接表体现了“以时间换空间”。
8) 图可用于建模各类现实系统，如社交网络、地铁线路等。
9) 树是图的一种特例，树的遍历也是图的遍历的一种特例。
10) 图的广度优先遍历是一种由近及远、层层扩张的搜索方式，通常借助队列实现。
11) 图的深度优先遍历是一种优先走到底、无路可走时再回溯的搜索方式，常基于递归来实现。
```

`Q：路径的定义是顶点序列还是边序列？`

- 维基百科上不同语言版本的定义不一致：英文版是“路径是一个边序列”，而中文版是“路径是一个顶点序列”。以下是英文版原文：In graph theory, a path in a graph is a finite or infinite sequence of edges which joins a sequence of vertices.

- 这里路径被视为一个边序列，而不是一个顶点序列。这是因为两个顶点之间可能存在多条边连接，此时每条边都对应一条路径。

`Q：非连通图中是否会有无法遍历到的点？`

在非连通图中，从某个顶点出发，至少有一个顶点无法到达。遍历非连通图需要设置多个起点，以遍历到图的所有连通分量。

`Q：在邻接表中，“与该顶点相连的所有顶点”的顶点顺序是否有要求？`

可以是任意顺序。但在实际应用中，可能需要按照指定规则来排序，比如按照顶点添加的次序，或者按照顶点值大小的顺序等，这样有助于快速查找“带有某种极值”的顶点。