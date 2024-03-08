/*
1. <ctime> 
std::clock()函数  
- 返回当前进程启动依赖大概的[处理器时间/进程时间]，能够通过CLOCKS_PER_SEC转换成秒

2. <chrono>库(C++ 11) 
std::chrono::system_clock::now() 
class system_clock 
- 代表系统层面的实时时间，可以在任意时间点被改变 

3. 若不想用户改变，最适合、最稳定测量时间间隔的是std::chrono::steady_clock::now() 
*/ 
#include <ctime>
#include <iostream> 
#include <mingw.thread.h> 
#include <chrono>

void do_something(){ 
    /*10s的程序执行时间...*/ 

    int cnt = 0;  

    for(int i = 0; i<10; i++){
        // cnt += 1;   
        // 休眠1s 
        std::this_thread::sleep_for(std::chrono::seconds(1));  
    }
}

void test01_ctime(){ 
    /*
    注意：clock()返回的是进程执行时间，即CPU的执行时间。 
    - 当引入休眠操作时，若系统切换到其他进程，那么这段休眠时间就不会被计算。
    */
    // std::clock_t start = std::clock(); 
    auto start = clock(); // typedef long clock_t;  

    // 引入期望等待时间（5s)  
    std::clock_t expiredEnd = std::clock() + 5 * CLOCKS_PER_SEC;
    
    while(clock() < expiredEnd){ 
        // ！！！若跳转到其他进程，当前进程不会计算休眠时间，因为clock()是进程执行时间
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    do_something(); 
    auto end = clock(); 
    auto diff = end-start; 
    auto seconds = diff / CLOCKS_PER_SEC;  

    std::cout << "程序执行时间:" << seconds << "/秒" << std::endl; // 15s  

}  

void test02_chrono(){
    /*
    替换clock等待机制，使用chrono，保证为实时系统时间而不是进程时间
    */
    auto start = std::chrono::system_clock::now();  // time_point 

    // 引入期望等待时间（5s)  
    // std::clock_t expiredEnd = std::clock() + 5 * CLOCKS_PER_SEC;
    // duration 5s时间间隔，得到时间点 
    auto expiredEnd = std::chrono::system_clock::now() + std::chrono::duration<int>(5);
    
    while(std::chrono::system_clock::now() < expiredEnd){  
        /*即便切换进程，休眠的时间也会被计算在内，因为是系统的实时时间，但是用户可以改变*/
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 休眠1s 
    }

    do_something(); 
    auto end = std::chrono::system_clock::now(); 
    auto diff = end-start; 
    auto seconds = diff / CLOCKS_PER_SEC;  

    std::cout << "程序执行时间:" << seconds << "/秒" << std::endl; // 15s  
}

void test03_chrono(){
    /* 
    steady_clock
    即便用户修改系统时间，也不会影响
    */
    auto start = std::chrono::steady_clock::now();  // time_point 

    // 引入期望等待时间（5s)  
    // std::clock_t expiredEnd = std::clock() + 5 * CLOCKS_PER_SEC;
    // duration 5s时间间隔，得到时间点 
    auto expiredEnd = std::chrono::steady_clock::now() + std::chrono::duration<int>(5);
    
    while(std::chrono::steady_clock::now() < expiredEnd){  
        /*即便切换进程，休眠的时间也会被计算在内，因为是系统的实时时间，但是用户可以改变*/
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 休眠1s 
    }

    do_something(); 
    auto end = std::chrono::steady_clock::now(); 
    auto diff = end-start; 
    auto seconds = diff / CLOCKS_PER_SEC;  

    std::cout << "程序执行时间:" << seconds << "/秒" << std::endl; // 15s  
}

int main(){
    // test01_ctime();  
    // test02_chrono();
    test03_chrono();
    return 0; 
}