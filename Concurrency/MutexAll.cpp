/*
    互斥体  Mutex 
    -------------------------
    多线程编程中，防止多个线程对同一个共享数据同时访问形成资源竞争的同步原语
    （原语：执行过程中不可以被中断的语句）  
    操作系统特有概念，类似于“锁” 
    - 访问共享数据，给共享数据加锁，其他线程访问共享数据时，若共享数据是已经被加锁状态，保证了共享数据在同一时间只能有一个线程访问  

    为什么使用互斥体？
    ------------------------- 
    保证共享数据同一时间只有一个线程访问  => 缓存顺序的一致性  
    L1 Cache -> L2 Cache -> L3 Cache  
    CPU修改了值之后，存在一级缓存，在同步到内存中，可能导致最终写入内存的值不是期望值。 

    C++中使用互斥体 -> 访问共享数据，保证数据一致性
    ---------------------------- 
    std::mutex -- 提供 排他性 非递归所有权语义 
    1. 排他性：同一时间，只能有一个线程对一个互斥体加锁。
    2. 非递归所有权：同一线程中，若对一个线程重复加锁，会导致未定义行为 

    lock、try_lock、unlock 
    1. lock:上锁，阻塞当前线程
    2. try_lock: bool返回，是否上锁成功 
    3. unlock: 解锁互斥体

    ----------------------------
    std::timed_mutex -- 提供 排他性 非递归所有权语义  
    额外提供try_lock_for、 try_lock_until带时间类型的方法 
    1. try_lock_for: 在给定时间范围内对互斥体加锁, 成功true，失败超时false 
    2. try_lock_until: 在给定时间点到达之前尝试对互斥体加锁，成功true，失败超时false 

    ----------------------------
    std::recursive_mutex -- 提供 排他性 递归所有权语义
    1. 多个线程同一时间只能有一个线程对互斥体加锁  
    2. 当前线程可以多次对互斥体加锁  
    
    ----------------------------
    std::recursive_timed_mutex -- 提高可递归使用的带超时设置的互斥体 

    ----------------------------
    std::lock_guard<Mutex> 
    1. 每次手动调用lock/unlock很麻烦，lock_guard可自动获取和释放互斥体，符合RAII(Resource Acquisition Is Initialization)风格
    2. 构造完成互斥体锁定，析构完成互斥体的解锁 
*/ 

#include <mingw.thread.h>
#include <mingw.mutex.h>
#include <iostream>   
#include <chrono>

// 创建全局共享数据
static int share_data = 0;  
static int share_data2 = 0; 
static int share_data3 = 0; 
static std::mutex mtx; 
static std::recursive_mutex rcv_mtx;


// 全局数据自增
void SelfIncreaseProc(){ 
    // 为什么放在for里面 --- 最小化临界区 or 被保护区域
    // -- 若写在外面，则可能会先执行加，后执行减
    // -- 若写在里面，只保护自增和自减，线程A、B交替，不会某个线程独占。
    for(int i = 0; i < 1000000; ++i){
        mtx.lock(); 
        ++share_data;  
        // std::cout << "+1自增!" << std::endl;  
        mtx.unlock(); 
    }
} 

// 全局数据自减 
void SelfDecreaseProc(){
    for(int i = 0; i < 1000000; ++i){
        mtx.lock(); 
        --share_data;  
        // std::cout << "-1自减!" << std::endl;  
        mtx.unlock(); 
    }
}  

// RecursiveCall 测试 rcv_mtx  
// 递归调用
void RecursiveCall(int &num){
    // 递归终止
    if(--num == 0){
        return;
    } 

    rcv_mtx.lock(); // 若是std::mutex，第二次会在这死锁，因为是非递归 
    ++share_data2; 
    RecursiveCall(num); 
    rcv_mtx.unlock();
} 

// lock_guard测试
void lock_guardTest(){
    std::lock_guard<std::mutex> guard(mtx);  // 构造时调用lock，析构时调用unlock  
    ++share_data3; 
}

int main(){
    // 示例1 -- 基本mutex实现对共享数据进行保护的效果
    // std::thread tA(SelfIncreaseProc); 
    // std::thread tB(SelfDecreaseProc); 
    // tA.join(); 
    // tB.join(); 
    // std::cout << "share_data = " << share_data << std::endl; 

    // 示例2 -- recursive_mutex
    // int num = 100;   
    // // 线程传参是值传递  
    // // 不能使用真正意义上的引用，而是使用包装的ref，传入的是一个对象
    // std::thread tRec(RecursiveCall, std::ref(num));    
    // // 确保线程A先执行
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
    // std::thread tPrint([](){
    //     rcv_mtx.lock(); 
    //     std::cout << "shared_data: " << share_data2 << std::endl;
    //     rcv_mtx.unlock(); 
    // });  
    // tRec.join();
    // tPrint.join(); 

    // 示例3 -- lock_guard 



}
