/*
拓展: 
- LRU的进阶版本 --- LFU缓存 
- Leetcode 460 困难
https://leetcode.cn/problems/lfu-cache/solutions/210980/chao-xiang-xi-tu-jie-dong-tu-yan-shi-460-lfuhuan-c 
*/

/*展开看Python Version 实现（P-code作用)*/ 
/*
from  collections import defaultdict 

""" 
default_dict：当插入不存在的键时，会依据默认类型，创建一个空列表
"""

class BListNode:
    def __init__(self, key=0, value=0): 
        self.key = key 
        self.value = value 
        self.cnt = 1   # Freq 
        self.next = None 
        self.prev = None  

# 用于Freq-to-List
def new_list() -> BListNode:
    dummy = BListNode() 
    dummy.prev = dummy 
    dummy.next = dummy
    return dummy 

class LFUCache:
    def __init__(self, capacity: int):
        # Hash1：Key to Node 
        # 这个Hash的作用是定位 
        self.cache = dict()  

        # Hash2: Freq-to-List 
        # 这个Hash的作用是进行访问频率的修改操作
        # 其每个Key都对应一个BList
        # 当其中某个频率对应的BList中的node被“操作”时
        #  - 将其从Freq的BList中删去，并插入到对应的Freq中（此时cnt+=1） 
        #  - 若不存在这个Freq，则基于defaultdict(), 创建一个dummyList并插入  
        self.Freq2dummy = defaultdict(new_list)

        self.size = 0 
        self.max_size = capacity

        # min_Freq
        # 这个Threshold用于在capacity满时，去除最久未使用的dummyBList 
        self.minFreq = 0 

    def get(self, key: int) -> int: 
        # print(self.cache.keys()) 
        node = self._get_node(key) 
        return node.value if node else -1 

    def put(self, key: int, value: int) -> None:  
        node = self._get_node(key) 
        if node: # 查到这本书了
            node.value = value # 更新value 
            return 
        
        # 检测当前capacity 
        # print("current put node:", key, "|| current size:", self.size, "||", len(self.cache.keys()))
        if self.size == self.max_size: 
            # 书太多，需要删除最不常用的
            # --- Freq最小的dummyBList的tail  
            dummy = self.Freq2dummy[self.minFreq] 
            # 删除掉dummy的tail  
            last_node = dummy.prev 
            
            # 删除1: 删除Key2Node中对应的Node 
            # 删除2: 删除Freq2Node中minFreq对应的BList的Tail Node 
            del self.cache[last_node.key] 
            self.size -= 1 
            self._del_node(last_node) 

            # 检测是否是空 
            # 若为空，直接将这个dummyBList删掉
            if self._check_dummy_empty(dummy):
                del self.Freq2dummy[self.minFreq]

        # 未查到这本书，是新书, 且容量不满 
        node = BListNode(key, value) 
        self.cache[key] = node 
        self.size += 1 

        # 新书，肯定是第一次 
        self._add_node_to_dummyBList_head(node, self.Freq2dummy[node.cnt]) 

        # 千万别忘记更新minFreq
        # 因为此时插入了new Node, 所以minFreq肯定是1  
        self.minFreq = 1 
    
    # checkempty 
    def _check_dummy_empty(self, dummy):
        if dummy.prev == dummy:
            return True 
        else:
            return False 
    
    # 从某个BList中删除
    def _del_node(self, node):
        node.prev.next = node.next 
        node.next.prev = node.prev   
    
    # 添加到某个Freq对应的dummy中 
    def _add_node_to_dummyBList_head(self, node, dummy):
        node.prev = dummy 
        node.next = dummy.next 
        node.prev.next = node 
        node.next.prev = node   

    def _get_node(self, key: int): 
        if key not in self.cache:
            return None 

        # 1. 先通过key-to-node定位
        node = self.cache[key]

        # 2. 从对应的Freq下的dummy中抽出 
        self._del_node(node)

        # 3. 在通过node_to_dummy找到这个node之前的Freq对应的dummyBList 
        dummy = self.Freq2dummy[node.cnt] 
        if dummy.prev == dummy: 
            # 说明删除这个node后，这个freq对应的dummyBList是空了 
            del self.Freq2dummy[node.cnt]   

            # 此时，若这个被删掉的dummy的Freq是minFreq,则需要更新minFreq 
            if self.minFreq == node.cnt:
                self.minFreq += 1 

        node.cnt += 1   # Node的访问Freq更新 
        # 添加到对应Freq的Dummy中 
        self._add_node_to_dummyBList_head(node, self.Freq2dummy[node.cnt]) 
        return node 
*/ 


#include <iostream> 
#include <unordered_map> 
#include <memory> 

/*
LRU(Least Recently Used) 最近最少使用算法，它是根据时间维度来选择将要淘汰的元素，即删除掉最长时间没被访问的元素。
LFU(Least Frequently Used) 最近最不常用算法，它是根据频率维度来选择将要淘汰的元素，即删除访问频率最低的元素。如果两个元素的访问频率相同，则淘汰最久没被访问的元素。
    - 也就是说LFU淘汰的时候会选择两个维度，先比较频率，选择访问频率最小的元素；如果频率相同，则按时间维度淘汰掉最久远的那个元素。
*/
using namespace std; 

struct DLinkedNode{
    int key; 
    int value; 
    int freq; 

    std::shared_ptr<DLinkedNode> prev;
    std::shared_ptr<DLinkedNode> next; 

    // 默认构造 
    DLinkedNode(int key = 0, int value = 0, int freq = 1): key(key), value(value), freq(freq){}

    // 有参构造  
    DLinkedNode(int key, int value, int freq, std::shared_ptr<DLinkedNode> &prev, std::shared_ptr<DLinkedNode> &next): 
        key(key), value(value), freq(freq), prev(prev), next(next){} 

    // 拷贝构造 
    DLinkedNode(const DLinkedNode &node): key(node.key), value(node.value), freq(node.freq), prev(node.prev), next(node.next){}

}; 

class LFUCache{
    public: 
        // 默认构造
        LFUCache(int capacity): maxSize(capacity){
            size = 0; 
            minFreq = 0; 
            dummyNode = make_shared<DLinkedNode>(); 
            dummyNode->prev = dummyNode;  
            dummyNode->next = dummyNode; 
        }

        /*
        Main API1: get方法
        */
        int get(int key);  

        /*
        Main API2: put方法
        */ 
        void put(int key, int value); 

        /*--------------------------------------------------------------*/
        /*
        get node
        */
        shared_ptr<DLinkedNode> get_node(int key);   

        /*
        从BiList抽出Node 
        */
        void del_node(std::shared_ptr<DLinkedNode> &node); 

        /* 
        将Node放到DummyBiList的最前方/上方
        */ 
        void add_node_to_head(std::shared_ptr<DLinkedNode> &node); 

    private: 

        int size; 
        int maxSize; 
        int minFreq; 

        // KeyToNode，帮助定位Node 
        unordered_map<int, std::shared_ptr<DLinkedNode>> Cache; 
        // FreqToDummy，帮助定位双向链表DummyBiList, 索引是Freq访问频率 
        unordered_map<int, std::shared_ptr<DLinkedNode>> Freq2dummy;

        // dummy指针 
        shared_ptr<DLinkedNode> dummyNode;  

        // 创建dummyNode 
        shared_ptr<DLinkedNode> _create_dummyNode(){ 
            shared_ptr<DLinkedNode> dummy = make_shared<DLinkedNode>(); 
            dummy->prev = dummy; 
            dummy->next = dummy; 
            return dummy; 
        } 
};

int LFUCache::get(int key){ 
    auto node = this->get_node(key); 
    if(node){
        return node->value; 
    }else{
        return -1; 
    }
} 

void LFUCache::put(int key, int value){
    auto Node = this->get_node(key); 

    if(Node){
        /*已经找到了这个Node，无需添加*/  
        Node->value = value; 
        return; 
    } 

    /*没有这个Node时的工作流
    1. 检测容量是否超
    2. 若容量超过，则删除最少使用的node
    3. 若容量未超过，直接插入到minFreq等于1的那个 
    */  

    // cout << "Size:" << this->size << endl;  

    if(this->size == this->maxSize){ 
        shared_ptr<DLinkedNode> tmpDummy =  this->Freq2dummy[this->minFreq]; 
        /*找到最不常用的tail node*/ 
        auto lastNode = tmpDummy->prev;   
        this->del_node(lastNode); 

        /*cache也要删除对应的node*/  
        this->Cache.erase(lastNode->key); 
        
        this->size -= 1;  

        /*释放内存*/ 
        lastNode.reset();  

        /*若这个tmpDummy是空*/ 
        if(tmpDummy->prev == tmpDummy){
            this->Freq2dummy.erase(this->minFreq); 
            tmpDummy.reset(); 
        }
    } 

    // 容量未超过，直接插入freq为1的dummyBiList的最前方 
    // 新的Node 
    shared_ptr<DLinkedNode> newNode = make_shared<DLinkedNode>(key, value, 1); 
    this->Cache.emplace(key, newNode);
    this->add_node_to_head(newNode); 
    this->minFreq = 1;  

    this->size += 1; 
}

shared_ptr<DLinkedNode> LFUCache::get_node(int key){ 
    if(this->Cache.find(key) == this->Cache.end()){
        return nullptr; 
    }

    /*1.通过Cache定位*/ 
    shared_ptr<DLinkedNode> tmpNode = this->Cache[key]; 

    /*2.从对应Freq下的dummyBiList抽出*/ 
    this->del_node(tmpNode);  

    /*3.在通过Freq2Node找到这个node之前的DummyBList，判断其是否为空，若为空，则删去，并更新minFreq*/   
    shared_ptr<DLinkedNode> tmpDummy = this->Freq2dummy[tmpNode->freq]; 
    if (tmpDummy->prev == tmpDummy){
        /*此时说明删去的这个tmpNode为该Freq对应的dummyBList的tail*/ 
        this->Freq2dummy.erase(tmpNode->freq);    
        /*释放内存*/
        tmpDummy.reset();  

        /*判断是否需要更新此时的minFreq, 此时这个node属于Freq2Dummy中最不常访问的一类*/ 
        if(this->minFreq == tmpNode->freq){
            this->minFreq += 1; 
        }
    } 

    /*更新访问频率*/
    tmpNode->freq += 1; 

    /*TODO 添加到Freq对应的DummyBiList中, 并放在最上方，表示这个BList最新访问的Node*/  
    this->add_node_to_head(tmpNode);  

    return tmpNode; 
} 


void LFUCache::del_node(std::shared_ptr<DLinkedNode> &node){ 
    node->prev->next = node->next; 
    node->next->prev = node->prev; 
} 


void LFUCache::add_node_to_head(std::shared_ptr<DLinkedNode> &node){  

    // 首先检测是否有这个Freq对应的DummyBiList 
    // 默认freq是1 
    if(this->Freq2dummy.find(node->freq) == this->Freq2dummy.end()){
        // 新建一个dummy，并添加key为这个Freq 
        this->Freq2dummy.emplace(node->freq, this->_create_dummyNode()); 
    }

    std::shared_ptr<DLinkedNode> dummy = this->Freq2dummy.find(node->freq)->second; 

    // node->prev = dummy; 
    // node->next = dummy->next; 
    // dummy->next->prev = node; 
    // dummy->next = node; 
    // node->prev = dummy; 
    // node->next = dummy->next; 
    // node->prev->next = node; 
    // node->next->prev = node;    

    node->prev = dummy; 
    node->next = dummy->next; 
    dummy->next->prev = node; 
    dummy->next = node;
} 


int main(){
    LFUCache* lfu = new LFUCache(2);
    lfu->put(1, 1);   // cache=[1,_], cnt(1)=1 
    lfu->put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    cout << lfu->get(1)<<  endl;      // 返回 1
                    // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu->put(3, 3);   // 去除键 2 ，因为 cnt(2)=1 ，使用计数最小
                    // cache=[3,1], cnt(3)=1, cnt(1)=2
    cout << lfu->get(2) << endl ;      // 返回 -1（未找到）
    cout << lfu->get(3) << endl ;      // 返回 3 
                    // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu->put(4, 4);   // 去除键 1 ，1 和 3 的 cnt 相同，但 1 最久未使用
                    // cache=[4,3], cnt(4)=1, cnt(3)=2
    cout << lfu->get(1) << endl ;      // 返回 -1（未找到）
    cout << lfu->get(3) << endl;      // 返回 3
                    // cache=[3,4], cnt(4)=1, cnt(3)=3
    cout << lfu->get(4) << endl;      // 返回 4
                    // cache=[3,4], cnt(4)=2, cnt(3)=3 


    /*
    答案:[null,null,null,1,null,-1,3,null,-1,3,4] 
    */
    

    delete lfu; 

    return 0; 
}