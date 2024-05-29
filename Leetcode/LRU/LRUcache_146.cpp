/*
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。 
----------------------------------------------------------
实现 LRUCache 类：
1. LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
2. int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
3. void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。

注意：【函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。】
---------------------------------------------------------
解题关键：双链表 +  Hash 
1. 双链表用来实现缓存的顺序，Hash表用来快速定位节点。 
2. 双链表需要建立dummy head与dummy head, 插入时，需要将节点插入到dummy head后面，删除时，需要将节点从双链表中删除。 
3. 访问Hash时间复杂度O(1) 
4. 双链表头部添加节点、尾部删除节点复杂度O(1)   
---------------------------------------------------------
*/ 

/* Python Version 
class BiNode:   
    # 使用双向List的原因，是因为LRU需要移出最久未使用的那个节点 
    def __init__(self, key=0, value=0):
        self.key = key 
        self.value = value 
        self.prev = None 
        self.next = None  


class LRUCache:
    """ 
    双向链表 + Hashmap  
    在 Python 语言中，有一种结合了哈希表与双向链表的数据结构 OrderedDict，只需要短短的几行代码就可以完成本题
    """
    def __init__(self, capacity: int): 

        self.cache = dict() # 用于定位，即找到key对应的Node在双向链表中的位置  
        self.size = 0  
        self.max_size = capacity    
        self.head = BiNode()  # dummy head 
        self.tail = BiNode() # dummy tail  
        self.head.next = self.tail  # 双向链表 
        self.tail.prev = self.head  


    def get(self, key: int) -> int:

        if key in self.cache:
            # 若key存在，通过Hash定位，再将其移到链表头部，表明这个node是最近被使用的node
            node = self.cache[key] 
            self._move_to_head(node) 
            return node.value 
        else:
            return -1 

    def put(self, key: int, value: int) -> None: 
        if key not in self.cache:
            # 不存在，插入链表头 
            node = BiNode(key, value) 
            self.cache[key] = node 
            self._add_node_to_head(node) 
            self.size += 1 
            # 判断是否超限
            if self.size > self.max_size:
                # 删除尾部 
                removed = self._remove_tail() 
                # 删除Hash中对应的项  
                self.cache.pop(removed.key) 
                self.size -= 1 
        else:
            # 如果key存在，Hash定位，修改value，并移到头部  
            # 存在
            node = self.cache[key] 
            node.value = value 
            self._move_to_head(node)

    def _move_to_head(self,node):
        # 先移出节点，再插入节点 
        # O(1) 
        self._remove_node(node)   
        self._add_node_to_head(node) 
    
    def _remove_node(self,node): 
        # print(node)
        node.prev.next = node.next 
        node.next.prev = node.prev 
    
    def _add_node_to_head(self,node):
        node.prev = self.head 
        node.next = self.head.next 
        self.head.next.prev = node 
        self.head.next = node 

    def _remove_tail(self):
        # 若超过capacity，则移出tail 
        node = self.tail.prev 
        self._remove_node(node) 
        return node 
    
# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)

*/

#include <iostream> 
#include <unordered_map> 
#include <memory>

using namespace std; 

struct DLinkedNode{
    int key; 
    int value;   

    std::shared_ptr<DLinkedNode> prev; 
    std::shared_ptr<DLinkedNode> next;

    // DLinkedNode *prev; 
    // DLinkedNode *next; 
    // 默认构造
    DLinkedNode():key(0),value(0),prev(nullptr),next(nullptr){}  
    // 有参构造
    DLinkedNode(int _key, int _value):key(_key),value(_value),prev(nullptr),next(nullptr){}
    // 拷贝构造
    DLinkedNode(const DLinkedNode &node):key(node.key),value(node.value),prev(node.prev),next(node.next){}
}; 


class LRUCache{
    public:
    LRUCache(int capacity):_capacity(capacity){ 
        _head = make_shared<DLinkedNode>();  // 默认  
        _tail = make_shared<DLinkedNode>(); 
        _head->next = _tail; 
        _tail->prev = _head;  
        _size = 0; 
        _capacity = capacity; 
    } 

    /*
    get访问 
    @params key: int   
    */ 
    int get(int key);  

    /*
    put功能
    @params: key 
    @params: value  
    @brief: 额外注意，需要考虑容量是否超限 
    */
    void put(int key, int value); 

    /*
    打印hashmap 
    */

    private: 
    int _size = 0; 
    int _capacity = 0;  
    unordered_map<int, shared_ptr<DLinkedNode>> _cache; 
    // 智能指针维护 
    shared_ptr<DLinkedNode> _head;
    shared_ptr<DLinkedNode> _tail; 

    /*
    moveToHead，将node移到链表头 
    @params node: 智能指针 DLinkedNode
    */ 
    // void _moveToHead(std::shared_ptr<DLinkedNode> node);  
    void _moveToHead(std::shared_ptr<DLinkedNode> &node){  
        this->_removeNode(node);    
        this->_addNodeToHead(node); 
    } 

    /*
    removeNode，移除Node  
    @params node: 智能指针 DLinkedNode 
    */ 
    // void _removeNode(std::shared_ptr<DLinkedNode> node);  
    void _removeNode(std::shared_ptr<DLinkedNode> &node){
        node->prev->next = node->next; 
        node->next->prev = node->prev; 
    }

    /* 
    removeTail, 移除链表尾结点
    @params: None 
        - 当capacity溢出时，需要移除尾节点  
        - 返回尾节点，因为要删除hashmap中对应的node 
    */ 
    // auto _removeTail();  
    auto _removeTail(){
        // 超过capacity  
        auto node = this->_tail->prev; 
        this->_removeNode(node); 
        return node;  
    } 

    /*
    addNodeToHead, 将Node添加到链表头 
    */
    // void _addNodeToHead(std::shared_ptr<DLinkedNode> node);   
    void _addNodeToHead(std::shared_ptr<DLinkedNode> &node){
        node->prev = this->_head; 
        node->next = this->_head->next;  
        this->_head->next->prev = node; 
        this->_head->next = node;   
    } 
}; 

int LRUCache::get(int key){ 
    
    // 存在
    if(_cache.count(key)){
        // 先通过hash定位  
        auto node = _cache[key];  
        // 将node移到链表头，表示最新访问过 
        this->_moveToHead(node);  
        return node->value;  
    }else{
        return -1;
    }
}   

void LRUCache::put(int key, int value){
    // 检测是否存在
    if(_cache.count(key)){
        // 存在
        std::shared_ptr<DLinkedNode> node = _cache[key]; 
        node->value = value;  
        this->_moveToHead(node); 
    }else{
        // 创建node 
        shared_ptr<DLinkedNode> node = make_shared<DLinkedNode>(key, value); 
        // 放到表头  
        this->_size += 1;
        this->_addNodeToHead(node);  
        this->_cache[key] = node;  
        if(this->_size > this->_capacity){
            // 超出容量，移除尾部 
            auto removed = this->_removeTail(); 
            // 删除hash中对应的项 
            this->_cache.erase(removed->key); 
            this->_size -= 1; 
        }
    }
}




int main(){
    LRUCache* cache = new LRUCache(2); 
    cache->put(1, 1);
    cache->put(2, 2); // 缓存是 {1=1, 2=2}
    int a = cache->get(1);    // 返回 1 
    cout << "输出1-" << a << endl;
    cache->put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    int b = cache->get(2);    // 返回 -1 (未找到) 
    cout << "输出2-" << b << endl;
    cache->put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    int c = cache->get(1);    // 返回 -1 (未找到)
    cout << "输出1-" << c << endl;
    int d = cache->get(3);    // 返回 3
    cout << "输出3-" << d << endl;
    int e = cache->get(4);    // 返回 4
    cout << "输出4-" << e << endl;

    // 释放cache 
    delete cache;

    return 0; 
}