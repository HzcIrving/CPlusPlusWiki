#include <iostream> 
#include <time.h>

/* 
单向链表定义: 
链表是一种常见的基础数据结构，它由一系列节点组成，每个节点都包含数据部分和一个或多个指向其他节点的指针。
在这个类中，每个节点包含一个整数值 val 和一个指向下一个节点的指针 next。 

struct ListNode：这是一个结构体声明，struct 是 C++ 中用于定义自定义数据类型的关键字，ListNode 是这个结构体的名称。 
int val：这是一个成员变量，用于存储链表节点的值，类型为 int（整数）。
ListNode *next：这是另一个成员变量，是一个指针，指向下一个 ListNode 类型的节点。nullptr 是 C++11 引入的关键字，用于表示空指针。
ListNode() : val(0), next(nullptr) {}：这是结构体的默认构造函数。当创建一个 ListNode 类型的对象而不提供任何初始值时，这个构造函数会被调用，它将 val 初始化为 0，将 next 指针初始化为 nullptr。
ListNode(int x) : val(x), next(nullptr) {}：这是一个接受一个整数参数 x 的构造函数。它将 val 设置为传入的值 x，将 next 指针初始化为 nullptr。
ListNode(int x, ListNode *next) : val(x), next(next) {}：这是一个接受一个整数参数 x 和一个 ListNode 指针 next 的构造函数。它将 val 设置为传入的值 x，将 next 指针设置为传入的 next 指针。 
-------------------------------------
创建和初始化链表节点：  在 C++ 中，链表通常通过指针来实现，这是因为链表的特点决定了它需要动态地分配和操作内存。
> ListNode* node1 = new ListNode(1);
> ListNode* node2 = new ListNode(2);
> ListNode* node3 = new ListNode(3);
> node1->next = node2; 
> node2->next = node3; 

> delete node1;
> delete node2; 
> delete node3; 
在链表的操作中，通常需要动态地创建和销毁节点，因为链表的长度在运行时可能会变化。
因此，使用 new 关键字在堆上分配内存是非常常见的。这样，你可以在需要时创建新的节点，并在不需要它们时释放内存，从而更有效地管理内存资源。 
-------------------------------------
补充知识点，why ListNode* node1 = new ... 为什么用指针

在 C++ 中，链表通常通过指针来实现，这是因为链表的特点决定了它需要动态地分配和操作内存。使用指针来实现链表的原因包括：
1) 动态内存分配：链表的大小通常在运行时才会知道，因此需要动态地分配和释放节点。指针允许我们在堆上分配内存，这样节点就可以在创建后独立于栈上的局部变量存在。
灵活性：链表需要频繁地插入和删除节点。使用指针可以轻松地修改节点间的引用（即 next 指针），而不需要移动大量数据，这样可以提高操作的效率。
性能：在大多数操作中，我们只需要操作指针，而不需要复制整个节点。因为指针的大小通常小于节点本身的大小，所以在复制指针时，性能开销较小。
简化操作：通过指针可以简化链表的操作，例如，插入一个新节点只需要改变几个指针的指向，而不需要重新分配或移动其他节点。
链表的结构：链表是由节点组成的，每个节点包含数据和指向下一个节点的指针。这种结构本身就要求使用指针来连接节点。
递归性：链表的操作往往具有递归性质，例如，遍历链表或搜索特定节点。指针天然适合用于递归操作，因为它们可以指向下一个节点，而不需要知道链表的确切大小。
避免复制开销：如果链表节点存储在栈上或作为值传递，那么每次添加或移动节点时，都需要复制节点，这可能会导致不必要的性能开销。使用指针可以避免这种复制。
因此，使用指针来创建和操作链表是 C++ 中的一种常见做法，它提供了必要的灵活性和效率，以支持链表动态和高效的操作。

*/ 
struct ListNode{
    int val; 
    ListNode* next; 
    ListNode(): val(0), next(nullptr){}; 
    ListNode(int x): val(x), next(nullptr){}; 
    ListNode(int x, ListNode *next): val(x), next(next){}; 
};  

class Solution{
    public:  
        ~Solution(){
            delete _predhead; 
            std::cout << "析构调用，正确删除..."  << std::endl; 
        }
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) { 
        /*
        递归方法 
        list1[0] + merge(list[1:], list2) list1[0] < list2[0] 
        list2[0] + merge(list1, list[2:]) otherwise   
        时间复杂度O(m+n)
        空间复杂度O(m+n), 递归调用mergeTwoLists函数需要消耗栈空间，栈空间大小取决于递归调用的深度
        */  
        if(list1 == nullptr){
            return list2; // l1到头
        } else if(list2 == nullptr){
            return list1; // l2先到头
        } else if(list1->val < list2->val){ 
            list1->next = mergeTwoLists(list1->next, list2); 
            return list1; 
        } else{
            list2->next = mergeTwoLists(list1, list2->next);  
            return list2; 
        }
        
        // ListNode* mergeTwoLists2()
    } 
    
    ListNode* mergeTwoLists2(ListNode* l1, ListNode* l2) { 
        /*
        迭代法，构造新链表
        设定一个哨兵节点 prehead， 方便直接return prehead->next  
        时间复杂度O(m+n) 
        空间复杂度O(1)
        */  
        // ListNode* prehead = new ListNode(-1);  // 哨兵节点
        ListNode* prev = _predhead; 
        while (l1!=nullptr && l2!=nullptr){
            if(l1->val < l2->val){
                prev->next = l1; 
                l1 = l1->next; 
            } else{
                prev->next = l2; 
                l2 = l2->next; 
            }

            prev = prev->next; //移动prev指针 
        }

        // 合并后，检测l1,l2是否为空，并合并剩余内容
        prev->next = l1 == nullptr? l2:l1;  

        return _predhead->next; // dummy节点方便return 
    } 

    private: 
        ListNode* _predhead = new ListNode(-1); 
}; 




int main(){ 
    // 初始化链表List1 = [1,2,4] 
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(2); 
    list1->next->next = new ListNode(4); 
    // ListNode* list1 = new ListNode(1, ListNode(2, ListNode(4)));

    // 初始化链表List2 = [1,3,4]  
    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);  

    Solution solution;  
    // 写一个用于记时的方法
    clock_t start = clock();
    // ListNode* mergedList = solution.mergeTwoLists(list1, list2);  
    ListNode* mergedList = solution.mergeTwoLists2(list1, list2); 
    clock_t end = clock(); 
    // std::cout << "用时:" << (end-start)*1000000 << "us" << std::endl;

    // 打印合并后的链表
    while(mergedList != nullptr){ 
        std::cout << mergedList->val << " "; 
        mergedList = mergedList->next; 
    }  std::cout << std::endl; 



    delete list1; 
    delete list2;  
    delete mergedList; 

    return 0; 
}