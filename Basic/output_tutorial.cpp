/*
写各类打印 
*/
#include <iostream> 

// 命名空间  
// 在程序中就可以直接使用std命名空间中的名称 
// cout 代替 std::cout类似  
// 只适合当前作用域，使用std::可以避免一些不必要的重新定义
using namespace std; 

int main()
{
    // 输出字符串
    // endl 换行  
    cout << "Hello, C++ world!" << endl;  
    cout << "Hello" << "Start Learning C++";  
    cout << "...Hello" << endl;
    cout << "Learning C++"; 
    return 0;   
}