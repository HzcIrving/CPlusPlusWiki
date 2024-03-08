#pragma once // 一次 
#include <iostream>   
using namespace std;

/*
案例描述: 实现一个通用的数组类，要求如下： 
-------------------------------------------
可以对内置数据类型以及自定义数据类型的数据进行存储
将数组中的数据存储到[堆区] 
    | 用于存储程序运行时动态分配的内存。当程序运行时，它会根据
    | 需要动态分配内存来存储数据、对象和临时变量等。
    | 这些内存区域在程序结束时会被释放，由操作系统回收。 
[堆区] vs. [栈区] 
| 总之，堆区和栈区的内存管理方式和使用场景不同，需要根据具体情况选择合适的内存区域。如果需要动态分配内存并且内存大小未知，可以选择堆区；如果只需要保存局部变量和函数参数，并且内存大小已知，可以选择栈区。
堆区需要手动释放，栈区会自动释放。 

1）内存分配方式：堆区是动态分配的，而栈区是函数调用时自动分配的。
2）内存大小：堆区的大小是在运行时确定的，而栈区的大小是在编译期确定的。
3）内存管理：堆区的内存管理由程序自己负责，而栈区的内存管理由程序自动完成。
4）内存释放时间：堆区内存的释放是由程序手动完成的（析构），而栈区内存在函数调用结束时会自动释放。

构造函数中可以传入数组的容量
提供对应的[拷贝构造函数]以及[operator=防止浅拷贝]问题
提供[尾插法]和[尾删法]对数组中的数据进行增加和删除
可以通过[下标]的方式访问数组中的元素
可以获取数组中当前[元素个数]和[数组的容量]  
------------------------------------------- 

深拷贝是将一个对象完全复制到另一个对象中，包括所有成员变量和动态分配的内存。这意味着如果源对象中有指向堆内存的指针，那么深拷贝会为目标对象分配一块新的内存，将源对象指针所指向的数据复制到这块新内存中。因此，深拷贝可以保证两个对象之间的数据完全独立，任何一个对象的修改都不会影响另一个对象。 

-- 实现:  
深拷贝通常需要在类的复制构造函数和赋值运算符重载函数中进行实现。在复制构造函数中，需要为目标对象分配新的内存，并将源对象中的数据复制到新的内存中。
在赋值运算符重载函数中，需要先释放目标对象已有的内存，再为目标对象分配新的内存，并将源对象中的数据复制到新的内存中。 

*/

template<class T> 
class MyArray{

    public:
        MyArray(int capacity);   
        MyArray(const MyArray & arr);  // 同类型的拷贝构造 
        MyArray& operator=(const MyArray& myarray); // 重载"="，防止浅拷贝 
        T& operator[](int index); // 重载[]，操作符   
        void push_back(const T &val); // 尾插
        void pop_back(); // 尾删 

        // 数组大小获取
        int size(){
            return this->m_Size;
        }

        // 数组容量获取 
        int capacity(){
            return this->m_Capacity; 
        } 


        // 打印 
        void PrintArray(const MyArray & myarray){
            for(int i = 0; i < myarray.m_Size; i++){
                cout << myarray[i] << " ";
            }
            cout << endl; 
        }


        // 析构
        ~MyArray(); 
    
    private: 
        T * pAddress; // 堆区, 存储数据 // 比如MyArray<int>、MyArray<char> ... 
        int m_Capacity;  // 数组容量(>=mSize)
        int m_Size; // 元素个数 
};  

// 构造函数类外实现 
template<class T> 
MyArray<T>::MyArray(int capacity){
    // 容量 
    this->m_Capacity = capacity; 
    this->m_Size = 0;  
    this->pAddress = new T[capacity];  // 类比int *a = new int(10)---[new 数据类型] 利用new创建的数据，会返回该数据对应的类型的指针  // 堆区
}

// 拷贝构造（重载） 
template <class T> 
MyArray<T>::MyArray(const MyArray & arr){
    this->m_Capacity = arr.m_Capacity; 
    this->m_Size = arr.m_Size;  

    // pAddress = new T[arr.m_Capacity];
    this->pAddress = new T[arr.m_Capacity];  
    for(int i = 0; i < this->m_Size; i++){
        // 如果T为对象，而且还包含指针，必须需要重载 = 操作符，因为这个等号不是[构造]而是[赋值]
        // 普通类型可以直接= 但是指针类型需要深拷贝 
        this->pAddress[i] = arr.pAddress[i]; 
    }  
} 

// 深拷贝 ，重载=，规避浅拷贝问题
// 在赋值运算符重载函数中，需要先释放目标对象已有的内存，再为目标对象分配新的内存，并将源对象中的数据复制到新的内存中。  
template <class T> 
MyArray<T>& MyArray<T>::operator=(const MyArray& myarray){
    // 释放目标对象已有内存 
    if (this.pAddress != NULL){
        delete[] this->pAddress; 
        this->m_Capacity = 0;
        this->m_Size = 0; 
    } 

    this->m_Capacity = myarray.m_Capacity;
    this->m_Size = myarray.m_Size;  

    // 堆区 开辟一个m_Capacity的内存空间大小的数组，用于存放数据
    this->pAddress = new T[this->m_Capacity];  
    for(int i = 0; i < this->m_Size; i++){
        this->pAddress[i] = myarray[i];  
    }

    return *this; 
};  

template<class T> 
T& MyArray<T>::operator[](int index){
    return this->pAddress[index]; //指针 不考虑越界，用户自己去处理
};


template<class T> 
void MyArray<T>::push_back(const T & val){
    if (this->m_Capacity == this->m_Size){
        return ; 
    }
    this->pAddress[this->m_Size] = val; 
    this->m_Size ++; 
} 

template<class T> 
void MyArray<T>::pop_back(){
    if (this->m_Size == 0){
        return; 
    }
    this->m_Size--;
}

template <class T> 
MyArray<T>::~MyArray(){
    if (this->pAddress != NULL){
        delete[] this->pAddress; 
        this->pAddress = NULL; // 空指针  
        this->m_Capacity = 0; 
        this->m_Size = 0;  
    }

}



