/*
数组array
 - 逻辑结构 -- 线性
 - 物理结构 -- 连续空间存储（连续内存块） 

Pros & Cons 
数组存储在连续的内存空间内，且元素类型相同。这种做法包含丰富的先验信息，系统可以利用这些信息来优化数据结构的操作效率。 
1. 空间效率高：数组为数据分配了连续的内存块，无须额外的结构开销。 
2. 支持随机访问：数组允许在 𝑂(1) 时间内访问任何元素。 
3. 缓存局部性：当访问数组元素时，计算机不仅会加载它，还会缓存其周围的其他数据，从而借助高速缓存来提升后续操作的执行速度。 

连续空间存储是一把双刃剑，其存在以下局限性。 
1. 插入与删除效率低：当数组中元素较多时，插入与删除操作需要移动大量的元素。 
2. 长度不可变：数组在初始化后长度就固定了，扩容数组需要将所有数据复制到新数组，开销很大。 
3. 空间浪费：如果数组分配的大小超过实际所需，那么多余的空间就被浪费了。
*/ 

#include <iostream>  
using namespace std;  

// 打印数组
void printArray(const int *nums, int size){ 
    // nums数组 首地址
    for(auto i = 0; i<size; i++){
        cout << nums[i] << " ";
    }cout << endl;      
}


/* 随机访问元素 */
int randomAccess(int *nums, int size) {
    // 在区间 [0, size) 中随机抽取一个数字
    int randomIndex = rand() % size;
    // 获取并返回随机元素
    int randomNum = nums[randomIndex];
    return randomNum;
}   

/* 在数组的索引 index 处插入元素 num  -- O(N)*/  
void insert(int *nums, int size, int index, int num){ 
    // 把索引 index 以及之后的所有元素向后移动一位
    for(auto i = size-1; i>index; i--){
        nums[i] = nums[i-1]; 
    } 
    // 将 num 赋给 index 处的元素
    nums[index] = num;  
    printArray(nums, size); 
} 

/* 删除索引 index 处的元素 */
void remove(int *nums, int size, int index) {
    // 把索引 index 之后的所有元素向前移动一位
    for (int i = index; i < size - 1; i++) {
        nums[i] = nums[i + 1];
    } 
    printArray(nums, size);
}

/* 扩展数组长度 */
int *extend(int *nums, int size, int enlarge) {
    // 初始化一个扩展长度后的数组
    int *res = new int[size + enlarge];
    // 将原数组中的所有元素复制到新数组
    for (int i = 0; i < size; i++) {
        res[i] = nums[i];
    }
    // 释放内存
    delete[] nums;
    // 返回扩展后的新数组首地址
    return res; 
}

int main(){
    /* 初始化数组 */
    // 存储在栈上
    int arr[5];
    int nums[5] = { 1, 3, 2, 5, 4 };
    printArray(nums, sizeof(nums)/sizeof(nums[0]));
    // 存储在堆上（需要手动释放空间）
    int* arr1 = new int[5];
    int* nums_test = new int[5] { 1, 3, 2, 5, 4 }; 

    /*随机访问O(1)*/ 
    cout << randomAccess(nums, 3) << endl;  // 0~3  
    
    /*插入元素*/
    insert(nums, sizeof(nums)/sizeof(nums[0]), 2, 666);  // 1 3 666 2 5 

    /*删除元素*/ 
    remove(nums, sizeof(nums)/sizeof(nums[0]), 2);// 1 3 2 5 | 5 
    remove(nums, sizeof(nums)/sizeof(nums[0]), 2); // 1 3 5 | 5 5 
    remove(nums, sizeof(nums)/sizeof(nums[0]), 1); // 1 5 5  5 5  

    /*扩容*/  
    int *new_arr = new int[10];
    printArray(new_arr, 10);
    new_arr = extend(nums_test,5,5);   
    printArray(new_arr, 10);
    // cout << "new size:" << sizeof(new_arr)/sizeof(new_arr[0]) << endl; 
    


    // 释放
    delete[] arr1; 
    delete[] nums_test;   
    delete[] new_arr; 
    
    return 0; 
}