/* 
KeyPts: 
1. 传递数组给函数
2. 从函数返回数组 

这个案例将实现C++ 传递数组给函数 
C++ 不允许向函数传递一个完整的数组作为参数  
通过指定不带索引的数组名来传递一个指向数组的指针。 

方式1： 形参是一个指针
void myFunction(int *param); 

方式2：形式参数是一个已定义大小的数组：
void myFunction(int param[10]); 

方式3：形参是一个未定义大小的数组；  
void myFunction(int param[]);  

C++ 不允许返回一个完整的数组作为函数的参数。
但是，您可以通过指定不带索引的数组名来返回一个指向数组的指针。

方式1：想要从函数返回一个一维数组，您必须声明一个返回指针的函数
P.S. C++ 不支持在函数外返回局部变量的地址，但是需要将局部变量定义为static类型 
int * myFunction();  
    static int r[10]; 
*/

#include <iostream> 
#include <ctime> 
using namespace std; 


// double getAvg(int arr[], int size); 
double getAvg(int *arr, int size);
// int * getRandom(int size);
int * getRandom(); 

int main(){
    // 初始化数组   
    int arr[5] = {1, 2, 3, 4, 5};  
    double avg;  

    // int arr_size = size(arr); 

    avg = getAvg(arr, 5);  
    cout << "平均值：" << avg << endl; 
    
    // 2. 获得随机数组 
    int *p; 
    // p = getRandom(10);  
    p = getRandom(); 
    for(int i=0; i<10; i++){
        cout << "*(p+" << i << "):" << *(p+i) << endl;   
    }  

    // delete [] p; // 释放内存

    return 0; 
}



// 写一个函数，输入数组，返回数组平均值 
// double getAvg(int arr[], int size){
double getAvg(int *arr, int size){
    int i, sum = 0; 
    double avg; 

    for(i=0; i<size; i++){
        sum += arr[i]; 
    }

    avg = double(sum)/size; 

    return avg; 
} 

// 写一个函数，生成随机数，并基于数组返回   
// int * getRandom(int size){
int * getRandom(){
    
    // 需要分配内存 
    // int *random_array = new int[size];  // 分配内存 
    // static int r[10];  

    // 第二种，返回局部变量地址，但是需要将局部变量定义为static类型 
    static int random_array[10];

    // 初始化种子 
    srand((unsigned)time(NULL)); 

    for(int i=0; i<10; i++){
        random_array[i] = rand(); 
        cout << random_array[i] << " " << endl;
    }

    // 返回的是地址 
    return random_array; 
}