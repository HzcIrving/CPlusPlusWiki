/*
C++ 11 中非常好用的关键字 -- auto 自动类型推导
https://www.bilibili.com/video/BV1Hk4y1p7zV/?spm_id_from=333.999.0.0&vd_source=6c24fa112801abdbc5741fa1a55aea2d 
1. 优势：
- 节省字数
e.g. 自动类型推导   
vector<int> v  
-- 迭代器 vector<int>::iterator iter = v.begin()
-- 自动推导 auto iter = v.begin()    
---------------------------------------------
- 取代手写某些类型你不是很确定的对象  
e.g.  callable obj取代 (lambda仿函数)
-- auto closure = [](const int&, const int&){}  
-- auto可以自动推理出返回类型是 std::function
-----------------------------------------------
- 与decltype关键字自结合,解决某些“丑陋”问题 
e.g. 用在模板内 
template<class T, class U> 
??? mul(T t, U u){
    return t*u; // 返回的是T类型还是U类型？？？
}
>>> 
template<class T, class U> 
auto mul(T t, U u){
    return t * u;
}
-----------------------------------------------

2. 缺点 
- 降低代码可读性 

- auto可能得不到你预想的类型 
e.g. vector<bool>[] 返回类型可能并不是一个bool 

*/ 
#include <ctime> 
#include <random>
#include <iostream> 
#include <vector> 
#include <typeinfo> 
using namespace std; 

// 自动类型推导
void test01(){
    vector<int> v;  
    // 随机生成证书 
    uniform_int_distribution<int> u(-100,100); 
    default_random_engine e(111);
    for(int i = 0; i < 10; i++){
        v.push_back(u(e));
    }; 

    // 打印 
    for(auto iter = v.begin(); iter!= v.end(); iter++){
        cout << *iter << " "; 
    } cout << endl;
}

// 取代仿函数返回类型 
void test02(){
    auto closure = [](const int&, const int&){cout << "仿函数" << endl;}; 
    closure(1,2);
}

// 解决某些“丑陋”问题 
template <class T, class U> 
auto mul(T t, U u){
    return t * u; // 自动推导类型 
}
void test03(){
    int t = 10; 
    float u = 2.0; 
    cout << mul(t,u) << endl; 
}


// Cons:  auto可能得不到你预想的类型  
void test04(){
    uniform_int_distribution<int> u(0,2); 
    default_random_engine e2(22);

    vector<bool> v;
    for (int i =0; i<10; i++){
        switch (u(e2))
        {
        case 1:
            v.push_back(true);
            break;
        
        case 2:
            v.push_back(false);
            break;
        
        default:
            break;
        } 
    }
    // 打印 
    for(auto iter = v.begin(); iter!= v.end(); iter++){
        cout << *iter << " "; 
    } cout << endl;

    auto var = v[0]; 
    // 检测推导类型  
    // typeid获取类型信息 
    cout << typeid(var).name() << endl; // 是一个proxy class 
    cout << var << endl; // 构造对象，对auto进行隐式转换

}
int main(){
    test01(); 
    test02();
    test03(); 
    test04();
}