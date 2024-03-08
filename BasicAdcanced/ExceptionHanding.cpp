/*
异常处理 - Wiki 

1. What is 异常处理 ? 
异常处理当然指的是对异常的处理，异常是指程序在执行期间产生的问题，没有按正确设想的流程走下去，比如除以零的操作，异常处理提供了一种转移程序控制权的方式，这里涉及到三个关键字：
 - throw：
    > 当问题出现时，程序会通过throw来抛出一个异常
 - catch：
    > 在可能有throw想要处理问题的地方，通过catch关键字来捕获异常
 - try：
    > try块中的代码标识将被激活的特定异常，它后面通常跟着一个或多个catch块

2. C++ 提供了一系列标准的异常，定义在<exception> 中，我们可以在程序中使用这些标准的异常。
*/ 

#include <iostream>  
#include <exception>
// #include
using namespace std;


// demo 01 
// void func(){
//     throw exception; // 异常抛出 
// }

// int main(){
//     try{ 
//         // try里放置可能抛出异常的代码，块中代码被称为保护代码
//         func(); 
//     } catch (exception1& e){
//         // 异常1 code 
//     } catch (exception2& e){
//         // 异常2 code 
//     } catch (...) {
//         // 其他异常 
//     }

//     return 0;
// }