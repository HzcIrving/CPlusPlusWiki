/*
线程：系统调度最小单位
进程：分配资源最小单位 

可以把一个程序理解为进程，进程又包含多个线程。 
例如：浏览器是个进程，而每开一个tab就是一个线程。

---------------------------------------------------
【线程vs.进程】
1. 进程间相互独立，同一进程的各线程间共享;
2. 某进程内的线程在其它进程不可见; 
3. 进程间通信IPC，线程间可以直接读写进程数据段（如全局变量）来进行通信（需要进程同步和互斥手段的辅助，以保证数据的一致性）； 
4. 线程上下文切换比进程上下文切换要快得多；
5. 在多线程OS中，进程不是一个可执行的实体； 
----------------------------------------------------
【五种创建线程的方式】
 1. 函数指针
 2. Lambda函数吧
 3. Functor(仿函数)
 4. 非静态成员函数
 5. 静态成员函数
---------------------------------------------------- 
【为何使用线程】 
现代CPU都是多核心，每个核心都有自己的指令流水线，可以独立执行任务。
使用多线程可以大幅提升程序效率（即使在单核平台，多线程编程的代码也可以正常执行）。
----------------------------------------------------  
【C++中的线程使用】
 C++11之前 -- pthread库
 C++11之后 -- thread标准库（底层是pthread) 
    编译时使用 -lpthread -std=c++11 
------------------------------------------------------
【线程销毁】 
 线程没有直接销毁的接口，只有等到线程函数执行完毕或者进程被系统强行终止； 
 主程序调用std::thread::join()后会阻塞主线程，直到子线程执行完毕，主线程才退出。 
-------------------------------------------------------- 
【线程id】
 通过调用std::thread::get_id()或者std::this_thread::get_id()可以获取相应线程编号，可以i做判断。
*/ 

#include <mingw.thread.h> 
#include <iostream>  
#include <ctime> 
#include <chrono>

// 使用Xs操作符，比如3s即3秒 
using std::chrono::operator""s; 

void do_something(){ 
    /*10s休眠时间...*/ 

    int cnt = 0;  

    for(int i = 0; i<10; i++){
        // cnt += 1;   
        // 休眠1s  --- sleep_for
        std::this_thread::sleep_for(std::chrono::seconds(1));  
    } 

    std::cout << "10s完成" << std::endl;
}


void until_do_somthing(const int &duration){
    for(int i = 0; i<3; ++i){
        std::cout << "Hello World!" << std::endl; 
        // 应该结束的时间点
        auto endTime = std::chrono::steady_clock::now() + std::chrono::seconds(duration);  

        // do something else  --- 可以计算一些耗时操作
        // do_something_else();

        std::this_thread::sleep_until(endTime);  // 计算耗时操作后，还要额外等待durations
    }
}

void calc_sum(const int &a, const int &b, int &sum){ 
    std::cout << "计算结果:" << a + b << std::endl;
    sum = a + b;  
    // return sum;  
}

// yield 调度 框架 
// void yield_do_something(){
//     while(true){
//         if(check_condition()){
//             do_otherthing();
//         }else{
//             std::this_thread::yield();//通知调度程序重新调度
//         }
//     }
// }

/*1. 创建线程*/ 
int main(){
    // 无参函数构造线程 --- 传入函数地址
    std::thread thread_1(do_something);  
    std::cout << "当前线程:" << thread_1.get_id() << std::endl;
    thread_1.join();  // 阻塞当前主线程

    

    // 带参函数构造线程
    int sum;  
    std::thread thread_2(calc_sum, 10, 20, std::ref(sum));
    std::cout << "当前线程:" << thread_2.get_id() << std::endl; 
    thread_2.join(); 

    

    // lambda 匿名函数构造 
    std::thread thread_3([](int x){ 
        std::cout << "函数指针，进程2" << ":" ;
        while (x-- > 0){
            std::cout << x << " "; 
        }std::cout << std::endl; 
    },11); 
    std::cout << "当前线程:" << thread_3.get_id() << std::endl;
    thread_3.join(); 

    

    // 休眠 
    std::thread thread_4(until_do_somthing, 3);  
    std::cout << "当前线程:" << thread_4.get_id() << std::endl; 
    thread_4.join();  

    

    std::cout << "主线程id:" << std::this_thread::get_id() << std::endl;

    return 0; 
}

