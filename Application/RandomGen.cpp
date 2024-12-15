/*
随机数模块 
https://blog.csdn.net/qq_40080842/article/details/124166928?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522170002501816800184146135%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=170002501816800184146135&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_click~default-1-124166928-null-null.142^v96^control&utm_term=C%2B%2B%E7%94%9F%E6%88%90%E9%9A%8F%E6%9C%BA%E6%B5%AE%E7%82%B9%E6%95%B0&spm=1018.2226.3001.4187 

在 C++11 之前，我们通常用 rand() 来生成随机数。

但 rand() 对一些情况显得难以处理：
- 不同范围的随机数
- 需要随机浮点数
- 需要非均匀分布的随机数 

这里我们使用 random随机库  
下文将使用 C++11 定义在头文件 random 中的随机数库，通过一组协作的类来解决这些问题。
    一个随机数引擎类可以生成 unsigned 随机数序列
    一个随机数分布类使用一个随机引擎类生成指定类型的、在给定范围内的、服从特定概率分布的随机数
*/ 

#include <ctime>
#include <iostream> 
#include <random> 
#include <math.h> 
using namespace std; 

#define PI acos(-1) 

int main(){
    // 1. 生成[1,100] 左闭、右闭随机证书 
    uniform_int_distribution<int> u(-100,100); 
    // 类似于random seed  
    default_random_engine e;   
    // time(NULL) 是一个无符号整数类型,表示当前的时间,它被用作随机数生成器的种子。
    // 种子是一个无符号整数类型的值,用于生成随机数。不同的种子可能导致生成的随机数序列不同。
    e.seed(time(NULL)); 
    for(int i=0;i<10;i++){
        cout << u(e) << " "; 
    }
    cout << endl;   

    // 2. 产生[-Pi,Pi] 范围随机浮点数 
    uniform_real_distribution<double> u1(-1*PI,PI); 
    default_random_engine e1(time(NULL)); 
    for (int i =0; i<10; i++){
        cout << u1(e1) << " ";
    }
    cout << endl; 
    

    // 3. 生成均值PI, 标准差0的随机数, 固定seed
    normal_distribution<double> n(PI,2);  
    default_random_engine e3(115); 
    for(int i=0; i<10; i++){
        cout << n(e3) << " "; 
    }
    cout << endl;  

    // 4. 生成布尔随机，设置概率0.7为1 
    bernoulli_distribution b(0.7); 
    for (int i=0; i<10; i++){
        cout << b(e3) << " ";
    }
    cout << endl; 

    return 0; 
}