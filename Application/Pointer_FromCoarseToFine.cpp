#include <iostream> 
using namespace std; 

/*
指针全面学习  
学习 C++ 的指针既简单又有趣。通过指针，可以简化一些 C++ 编程任务的执行
还有一些任务，如动态内存分配，没有指针是无法执行的。

所以，想要成为一名优秀的 C++ 程序员，学习指针是很有必要的。
*/ 

const int MAX = 3; 

int main(){

    // 1.关于取址符 &  
    // 每一个变量都有一个内存位置，每一个内存位置都定义了可使用连字号（&）运算符访问的地址，它表示了在内存中的一个地址。

    int var1; 
    char var2[10]; 

    cout << "var1 变量的地址： ";
    cout << &var1 << endl; // 0x61fe1c

    cout << "var2 变量的地址： ";
    cout << &var2 << endl; // 0x61fe12  

    // --------------------2. 什么是指针? -----------------------------------------------------------
    // 指针是一个变量，其值为另一个变量的地址，即，内存位置的直接地址。
    // 就像其他变量或常量一样，您必须在使用指针存储其他变量地址之前，对其进行声明。指针变量声明的一般形式为：
    // type *var-name;  
    // int    *ip;    /* 一个整型的指针 */
    // double *dp;    /* 一个 double 型的指针 */
    // float  *fp;    /* 一个浮点型的指针 */
    // char   *ch;     /* 一个字符型的指针 */ 
    // 所有指针的值的实际数据类型，不管是整型、浮点型、字符型，还是其他的数据类型，都是一样的，都是一个代表内存地址的长的十六进制数。 
    // 不同数据类型的指针之间唯一的不同是，指针所指向的变量或常量的数据类型不同。 

    // ---------------2.1 C++中使用指针 -------------------------------------------------------------
    int  var3 = 20;   // 实际变量的声明
    int  *ip;        // 指针变量的声明

    ip = &var3;       // 在指针变量中存储 var 的地址

    cout << "Value of var variable: ";
    cout << var3 << endl;

    // 输出在指针变量中存储的地址 
    // Address stored in ip variable: 0x61fe04
    cout << "Address stored in ip variable: ";
    cout << ip << endl;

    // 访问指针中地址的值
    cout << "Value of *ip variable: ";
    cout << *ip << endl;

    // ---------------2.2 C++中的NULL 空指针 --------------------------------------------------------
    /* 
    在变量声明的时候，如果没有确切的地址可以赋值，为指针变量赋一个 NULL 值是一个良好的编程习惯。
    赋为 NULL 值的指针被称为空指针。
    NULL 指针是一个定义在标准库中的值为零的常量。请看下面的程序：

    如需检查一个空指针，您可以使用 if 语句，如下所示：
    if(ptr)     如果 p 非空，则完成 
    if(!ptr)    如果 p 为空，则完成 
    */ 
    int *ptr = NULL;  
    // ptr地址:0x61fdf8
    cout << "ptr地址:" << &ptr << endl; 
    cout << "ptr的值:" << ptr << endl;

    // --------------2.3 指针的比较与运算 -------------------------------------------------- 

    // 1）对指针递减/递增 
    int var4[MAX] = {10,100,200}; 
    int *ptr2; 

    ptr2 = &var4[MAX-1]; // 指向最后一个元素地址 
    for (int i = MAX; i > 0; i--){
      cout << "Address of var[" << i << "] = ";
      cout << ptr2 << endl; 
      cout << "Value of var[" << i << "] = ";
      cout << *ptr2 << endl; // 200, 100, 10 
      // 移动到下一个位置
      ptr2--;
    } 

    // 比较运算符 
    int i = 0;  
    int *ptr3; 
    ptr3 = var4; 
    while (ptr3 <= &var4[MAX-1]){
      cout << "Address of var[" << i << "] = ";
      cout << ptr3 << endl;
      cout << "Value of var[" << i << "] = ";
      cout << *ptr3 << endl;
      // 指向上一个位置
      ptr3++;
      i++;
    } 

    // ------------------2.4 指针数组-------------------------------------------------------------------
    int var5[MAX] = {10,100,200}; 
    int *ptr4[MAX];  

    /*
    Value of var5[0] = 10
    Value of var5[1] = 100
    Value of var5[2] = 200
    */
    for(i=0; i<MAX; i++){
        ptr4[i] = &var5[i];  
    }
    for (int i = 0; i < MAX; i++)
    {
        cout << "Value of var5[" << i << "] = ";
        cout << *ptr4[i] << endl;
    } 

    // 2) 可以用一个指向字符的指针数组来存储一个字符串列表 
    const char *names[MAX]={
        "Zara", "Nike", "New Balance"
    };
    for (int i = 0; i < MAX; i++){
        cout << "Value of names[" << i << "] = ";
        cout << names[i] << endl; 
    }
    
    // ------------------- 2.5 多级间接寻址 （指针套指针，指向指针的指针）----------------------------------- 
    // 一个指针包含一个变量的地址。
    // 当我们定义一个指向指针的指针时，第一个指针包含了第二个指针的地址，第二个指针指向包含实际值的位置。
    int  var6;
    int  *ptr5;
    int  **pptr;

    var6 = 3000;

    // 获取 var 的地址
    ptr5 = &var6;

    // 使用运算符 & 获取 ptr 的地址
    pptr = &ptr5;

    // 使用 pptr 获取值
    cout << "Value of var :" << var6 << endl;
    cout << "Value available at *ptr :" << *ptr5 << endl;
    cout << "Value available at **pptr :" << **pptr << endl;

    return 0; 
}

