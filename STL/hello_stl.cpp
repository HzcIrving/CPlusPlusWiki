/*
用一个vector的例子，展开STL库的学习 
    push_back( ) 成员函数在向量的末尾插入值，如果有必要会扩展向量的大小。
    size( ) 函数显示向量的大小。
    begin( ) 函数返回一个指向向量开头的迭代器。
    end( ) 函数返回一个指向向量末尾的迭代器。
*/ 

#include <iostream> 
#include <vector> 
using namespace std; 

int main(){
    // 1.创建 
    vector<int> vec; 
    int i; 

    // 2. 显示vec原始大小 
    cout << "vec size before push_back: " << vec.size() << endl; 

    // 3. 尾插 
    for(i=0; i<5; i++){
        vec.push_back(i); 
    }

    // 4. 显示vec扩展后的大小
    cout << "vec size after push_back: " << vec.size() << endl; 

    // 5. 基于迭代器遍历vector大小 
    /*
    这行代码创建一个指向整数向量vec的第一个元素的迭代器v。
    begin()函数返回一个指向第一个元素的迭代器
    v是一个临时变量，用于存储这个迭代器。
    */
    vector<int>::iterator v = vec.begin();    
    while (v!=vec.end()){
        cout << "value of v = " << *v << endl; 
        v++; 
    } 

    return 0; 
}