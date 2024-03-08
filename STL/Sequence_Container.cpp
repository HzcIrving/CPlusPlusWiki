/*
介绍常见顺序容器的使用方法，以及迭代器基本知识 
1. vector: 长度可变化数组，类模板，
*/
#include <iostream>
#include <vector>    
using namespace std;

void vector_test(); 

int main(){
    
    vector_test();
    return 0; 

}

void vector_test(){
    std::vector<int> a{1,2,3};  
    std::vector<int> b{4,5};  

    // vector可以像数组一样使用 
    std::cout << a[0] << std::endl;  
    std::cout << b[1] << std::endl; 
}