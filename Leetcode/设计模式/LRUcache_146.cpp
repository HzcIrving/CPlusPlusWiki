/*
LRU缓存  146 
https://leetcode.cn/problems/lru-cache/solutions/259678/lruhuan-cun-ji-zhi-by-leetcode-solution/
*/ 

/*
解法: 双向链表+哈希表 
-------------------------------------------------
双向链表按照被使用的顺序存储了这些键值对，靠近头部的键值对是最近使用的，而靠近尾部的键值对是最久未使用的。
哈希表即为普通的哈希映射（HashMap），通过缓存数据的键映射到其在双向链表中的位置。 

利用Hash表定位，找到缓存项在双向链表中的位置，随后将其移动到双向链表头部，即可在O(1)时间内完成get或者put. 

*/
#include <iostream> 
#include <unordered_map>

struct DoubleLinkNode 
{
    // 写一个双向链表
    int key = 0;
    int value = 0; 
    DoubleLinkNode *prev = nullptr; 
    DoubleLinkNode *next = nullptr;
};

class LRUCache{
private: 
    // 哈希表 
    std::unordered_map<int, DoubleLinkNode*> cache;  
    // 头尾 
    DoubleLinkNode *head; 
    DoubleLinkNode *tail; 
    int _size; 
    int _capacity;   

public: 
    LRUCache(int capacity){
        // 使用Dummy头尾  
        
    }

}; 