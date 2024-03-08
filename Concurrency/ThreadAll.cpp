/* 
【BASIC】
线程是调度的基本单位 进程是资源分配的基本单位。
可以把一个程序理解为进程，进程又包含多个线程。 
例如：浏览器是个进程，而每开一个tab就是一个线程。  

------------------------------------------------
【线程vs.进程】
1. 进程间相互独立，同一进程的各线程间共享;
2. 某进程内的线程在其它进程不可见; 
3. 进程间通信IPC，线程间可以直接读写进程数据段（如全局变量）来进行通信（需要进程同步和互斥手段的辅助，以保证数据的一致性）； 
4. 线程上下文切换比进程上下文切换要快得多；
5. 在多线程OS中，进程不是一个可执行的实体；
-------------------------------------------------
*/ 

// #include "thread" 
#include <mingw.thread.h> 
#include <chrono>  // 处理时间和时间间隔的标准模板库STL 
#include <iostream> 

/*
【五种创建线的方式】
 1. 函数指针
 2. Lambda函数吧
 3. Functor(仿函数)
 4. 非静态成员函数
 5. 静态成员函数
*/

using namespace std::chrono;  
using namespace std; 

// 1. 函数指针 
void func(int x){ 
    cout << "函数指针，进程1" << ":" ;
    while (x-- > 0){   
        cout << x << " "; 
    } cout << endl; 
}

// 3. 非静态成员


int main(){
    // func(10); 

    // 1. 函数指针线程创建 
    std::thread t1(func, 10); 
    t1.join();

    // lambda函数 
    // auto fun = [](int x){
    //     while(x-- > 0){
    //         cout << x << endl; 
    //     }cout << endl; 
    // }; 

    // // 2. lambda线程创建  
    // // std::1.thread t1(fun, 10)
    std::thread t2([](int x){ 
        cout << "函数指针，进程2" << ":" ;
        while (x-- > 0){
            cout << x << " "; 
        }cout << endl; 
    },11); 

    t2.join(); 

    


    return 0; 
}