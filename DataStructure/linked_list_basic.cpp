/*
链表
1. 内存空间是所有程序的公共资源，在一个复杂的系统运行环境下，空闲的内存空间可能散落在内存各处。 
2. 我们知道，存储数组的内存空间必须是连续的，而当数组非常大时，内存可能无法提供如此大的连续空间。此时链表的灵活性优势就体现出来了。 

基本特性 
1. 「链表 linked list」是一种线性数据结构，其中的每个元素都是一个节点对象，各个节点通过“引用”相连接。
2.  引用记录了下一个节点的内存地址，通过它可以从当前节点访问到下一个节点。 
3.  链表的设计使得各个节点可以分散存储在内存各处，它们的内存地址无须连续。 
4.  总结
    - 逻辑结构 -- 线性
    - 物理结构 -- 无需连续内存空间  

组成单元 
链表的组成单位是「节点 node」对象。每个节点都包含两项数据：节点的“值”和指向下一节点的“引用”。 
1. C++中 “引用”应被替换为“指针” 
2. 尾节点指向的是“空”，它在 C++ 和 Python 中分别被记为nullptr 和 None   
链表节点除了val还需要额外保存一个引用（指针），因此相同数据量下，链表比数组占用更多的内存空间。

常见链表类型  
1. 单向链表：即前面介绍的普通链表。单向链表的节点包含值和指向下一节点的引用两项数据。我们将首个节点称为头节点，将最后一个节点称为尾节点，尾节点指向空 None 。
2. 环形链表：如果我们令单向链表的尾节点指向头节点（首尾相接），则得到一个环形链表。在环形链表中，任意节点都可以视作头节点。
3. 双向链表：与单向链表相比，双向链表记录了两个方向的引用。双向链表的节点定义同时包含指向后继节点（下一个节点）和前驱节点（上一个节点）的引用（指针）。相较于单向链表，双向链表更具灵活性，可以朝两个方向遍历链表，但相应地也需要占用更多的内存空间。 
 
链表典型应用 
[单向链表]
    1. 栈与队列 
    2. 哈希表: 链式地址是解决哈希冲突的主流方案之一，在该方案中，所有冲突的元素都会被放到一个链表中。
    3. 图: 邻接表是表示图的一种常用方式，其中图的每个顶点都与一个链表相关联，链表中的每个元素都代表与该顶点相连的其他顶点。 
[双向链表] 
    1. 需要快速查找前一个和后一个元素的场景 
    2. 高级数据结构：比如在红黑树、B 树中，我们需要访问节点的父节点，这可以通过在节点中保存一个指向父节点的引用来实现，类似于双向链表。 
    3. 浏览器历史：在网页浏览器中，当用户点击前进或后退按钮时,浏览器需要知道用户访问过的前一个和后一个网页。双向链表的特性使得这种操作变得简单。 
    4. LRU 算法：在缓存淘汰（LRU）算法中，我们需要快速找到最近最少使用的数据，以及支持快速添加和删除节点。这时候使用双向链表就非常合适。
[环形链表]
    1. 时间片轮转调度算法：在操作系统中，时间片轮转调度算法是一种常见的 CPU 调度算法，它需要对一组进程进行循环。每个进程被赋予一个时间片，当时间片用完时，CPU 将切换到下一个进程。这种循环操作可以通过环形链表来实现。
    2. 数据缓冲区：在某些数据缓冲区的实现中，也可能会使用环形链表。比如在音频、视频播放器中，数据流可能会被分成多个缓冲块并放入一个环形链表，以便实现无缝播放。

*/
#include <iostream> 
#include <memory>

using namespace std; 


/* 链表节点结构体 */ 
struct ListNode{
    int val; // 节点值 
    ListNode *next; // 指向下一节点的指针  
    ListNode(int x): val(x), next(nullptr) {}; // 构造函数 
}; 

/* 扩展：双向链表结构体 */ 
struct TwinListNode{
    int val; 
    TwinListNode *next; 
    TwinListNode *prev; 
    TwinListNode(int x): val(x), next(nullptr), prev(nullptr) {};
};

/* 工具：打印链表*/ 
void printListNodes(ListNode *head){ 
    while(head != nullptr){ 
        cout << head->val << "=>"; 
        head = head->next; 
    } 
    cout << endl; 
}

/* 插入节点 
e.g. 在n0和n1之间插入新节点，则只需改变两个节点引用（指针）即可，时间复杂度为O(1)
    [对比数组，数组插入元素时间复杂度为O(n)，大数据量下效率低] 
*/ 
void ListNodeInsert(ListNode *n0, ListNode *P){ 
    ListNode *n1 = n0->next; 
    P->next = n1; 
    n0->next = P;
} 

/* 删除节点 
e.g. 删除链表的节点 n0 之后的首个节点 --- O(1) 比数组高效 
*/
void ListNodeDelete(ListNode *n0){
    // check是否是尾
    if(n0->next == nullptr){
        return; 
    } 
    ListNode *p = n0->next; 
    ListNode *n1 = p->next; 
    n0->next = n1; 

    // 释放内存  
    // 注意删除完成后，P仍然指向n1，但遍历链表已经无法访问p，需要释放p的内存
    delete p; 
}

/* 访问节点 
 - 链表的劣势，低效... 
 - 如上一节所述，我们可以在O(1)时间下访问数组中的任意元素。
   链表则不然，程序需要从头节点出发，逐个向后遍历，直至找到目标节点 

 - 访问链表第i个节点需要循环i-1轮，时间复杂度为O(n) 
*/
ListNode *ListNodeAccess(ListNode *head, int index){
    for(int i = 0; i<index; i++){
        if(head == nullptr){
            return nullptr;    
        }
        head = head->next; 
    }
    return head; 
} 

/* 查找节点 
遍历链表，查找其中值为 target 的节点，输出该节点在链表中的索引。此过程也属于线性查找。  
*/ 
int find(ListNode *head, int target){
    int i = 0; 
    while(head!=nullptr){
        if(head->val == target){
            return i  ; 
        } 
        head = head->next; 
        i++; 
    }
    return -1; 
}


int main(){
    /* 初始化链表 */ 
    // 1->3->2->5->4 
    ListNode* n0 = new ListNode(1);  
    ListNode* n1 = new ListNode(3);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(5);
    ListNode* n4 = new ListNode(4); 
    n0->next = n1; 
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;  
    printListNodes(n0);

    /* 插入节点 */ 
    ListNode *p = new ListNode(666); 
    ListNodeInsert(n0, p);    
    printListNodes(n0);

    /* 删除节点 */
    ListNodeDelete(n0); 
    printListNodes(n0);

    /* 访问节点 */ 
    // 1->3->2->5->4 
    ListNode *n = ListNodeAccess(n0, 2); 
    cout << n->val << endl; 
    printListNodes(n0);

    /* 查找节点 */ 
    cout << find(n0, 4) << endl;

    /* 释放上述链表内存 */ 
    delete n0;
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete p;  
}