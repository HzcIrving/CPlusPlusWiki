/*
https://www.runoob.com/cplusplus/cpp-templates.html 

模板是泛型编程的基础，泛型编程即以一种独立于任何特定类型的方式编写代码。 
模板是创建泛型类或函数的蓝图或公式。库容器，比如迭代器和算法，都是泛型编程的例子，它们都使用了模板的概念。  

---举个粒子--- 
每个容器都有一个单一的定义，比如 向量，我们可以定义许多不同类型的向量，比如 vector <int> 或 vector <string>。 
您可以使用模板来定义函数和类，接下来让我们一起来看看如何使用。 

---函数模板范例--- 
template <typename type> ret-type func-name(parameter list)
{
   // 函数的主体
}     

-- type是函数所使用的数据类型的占位符名称  
-- 这个名称可以在函数定义中使用   

---类模板范例--- 
template <class type> class class-name {
.
}  
-- type 是占位符类型名称，可以在类被实例化的时候进行指定。 
-- 您可以使用一个逗号分隔的列表来定义多个泛型数据类型。 
-- 案例，是使用vector来实现Stack类， 
-- 基于 泛型方法来对元素进行入栈出栈操作 
*/ 

#include <iostream> 
#include <string>  
#include <vector> 

using namespace std; 

// 函数模板 
// Max函数的参数都是T const &类型的常量引用，这意味着它们只能读取参数，不能修改参数。
template <typename T>  
inline T const & Max(T const &a, T const &b){
    return a < b ? b:a; 
}

// 类模板 
template <class T> 
class Stack{
    private: 
        vector<T> elems; // 元素 
    
    public:  

        // const& elem 限制函数只能读取参数，不能修改参数
        void push(T const&); // 入栈 
        void pop(); // 出栈 --- 先入后出  

        // 这里的const只能读取栈顶元素，不能修改栈顶元素 
        T top() const;  // 返回栈顶元素  
        bool empty() const{
            return elems.empty();
        } 
}; 

template <class T> 
void Stack<T>::push(T const& elem){
    // 追加元素 
    elems.push_back(elem); 
} 

template <class T> 
void Stack<T>::pop(){
    // 删除 
    if (elems.empty()){
        throw out_of_range("Stack<>::pop(): empty stack");
    }
    // 删除最后一个元素
    elems.pop_back(); // 尾删，实现先入后出  
}

template <class T>
T Stack<T>::top() const{
    if (elems.empty()){
        throw out_of_range("Stack<>::pop(): empty stack");
    }
    
    elems.back(); // 返回最后一个元素
}

int main ()
{
// 1. 函数模板，不同类型数据输入 
//     int i = 39;
//     int j = 20;
//     cout << "Max(i, j): " << Max(i, j) << endl; 

//     double f1 = 13.5; 
//     double f2 = 20.7; 
//     cout << "Max(f1, f2): " << Max(f1, f2) << endl; 

//     string s1 = "Hello"; 
//     string s2 = "World"; 
//     cout << "Max(s1, s2): " << Max(s1, s2) << endl; 

//    return 0; 
    try{ 
    
        // 定义栈类型
        Stack<int> intStack;  
        Stack<string> stringStack;  

        // 操作int栈
        intStack.push(7); 
        cout << intStack.top() << endl; 

        // 操作 string 类型的栈 
        stringStack.push("hello"); 
        cout << stringStack.top() << std::endl; 
        stringStack.pop(); 
        stringStack.pop(); 

    }
    catch(exception const& ex){ 
        // 捕获 throw出来的异常 
        cout << "Exception: " << ex.what() << endl; 
    }
}

