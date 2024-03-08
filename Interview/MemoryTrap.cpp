/*
内存操作陷阱 
------------------
https://www.bilibili.com/video/BV1Dh4y1x76b/?spm_id_from=333.788&vd_source=6c24fa112801abdbc5741fa1a55aea2d 

1.内存分配失败就使用。比如malloc/new分配内存可能会失败
2.内存分配虽然成功，但是尚未初始化就使用 
3.内存分配虽然成功并且已经初始化，但操作越过了内存的边界
4.忘记了delete/free内存，造成内存泄露
5.用free或delete释放了内存之后，未立即将指针设置为NULL，产生"悬空指针", 此时若再使用该指针，指针返回的值为垃圾值 
*/

#include <stdio.h>
#include <iostream> 
#include <string.h>
using namespace std; 

int main(){
    // 1.内存分配失败就使用。比如malloc/new分配内存可能会失败   
    // 2.内存分配虽然成功，但是尚未初始化就使用 
    int *p = NULL;    
    
    p = (int*)malloc(sizeof(int));  // malloc 4字节内存 

    // 检测内存是否分配成功
    // 可能会 OOM --- out of memory  
    // p返回空，吃时候
    if(p == NULL){
        cout << "内存分配失败" << endl; 
    } 

    // 若不作p是否为nullptr的判断，可能会报错
    memset(p, 0, sizeof(int));   // 4字节全部设为0 
    // 若不初始化就使用，也不行,需要初始化数值 

    // -------------------------------------
    // 3. 内存越界 
    int *p1 = nullptr; 
    p1 = (int*)malloc(3*sizeof(int)); //12字节 

    if(p1==NULL){
        cout << "内存分配失败" << endl;
    }  

    memset(p1, 0, 3*sizeof(int));  
    cout << p1[2] << endl; // 0
    // cout << p1[3] << endl; // 越界 -- segment fault 

    free(p); 
    free(p1); 

    p = nullptr;
    p1 = nullptr;

    // -------------------------------------
    // 4. delete/free ， 内存泄漏, 用free或delete释放了内存之后，未立即将指针设置为NULL，产生"悬空指针", 此时若再使用该指针，指针返回的值为垃圾值  
    int *ptr = new int(1); 
    delete ptr; 

    cout << *ptr << endl; // 垃圾值

    ptr = nullptr;
    
    // cout << *ptr << endl;
}