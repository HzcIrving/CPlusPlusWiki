#include <iostream>
#include <stack> 

using namespace std; 

int main(){
    stack<int> s;  

    s.push(1); 
    s.push(2);
    s.push(3); 

    /*访问栈顶元素*/
    std::cout << "栈顶元素为：" << s.top() << std::endl; 
    std::cout << "栈的大小为：" << s.size() << std::endl; 

    /*弹出栈顶元素*/ 
    s.pop(); 
    s.pop(); 

    /*判空*/ 
    if(s.empty()){
        std::cout << "栈为空" << std::endl;
    }else{
        std::cout << "栈不为空" << std::endl;
    }

    return 0; 
}