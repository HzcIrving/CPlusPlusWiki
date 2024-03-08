/*
任务需求: 利用函数模板，封装排序函数，对不同数据类型数组排序 

- 排序规则从小到大，排序算法为选择排序、冒泡排序、快排等  
- 基于char数组、int数组、double数组进行测试

需求分析：
1. 需要swap函数，来交换两个值 
2. Sort函数，能针对不同类型数据排序 --- template  

Ver1 选择排序:
1. 比较+交换，每轮检查把未排序数值跟该轮最小值比较，将最小值与该轮起点值交换 
2. 复杂度分析 
   [5,4,3,2,1]最坏的情况，一共4+3+2+1次比较 N(N-1)/2=10次比较
   每轮都要交换1次（最坏情况） —— 一共4次交换 
   所以，算法复杂度: O(N^2) -> O(N^2)


记录1: vector<Candidate>类型模板
// 需要在typename前加typename 
template <class T> 
void printArray(T &v){
    int size = v.size();  
    // typename用于指定迭代器类型的正确类型别名。
    for (typename T::iterator it = v.begin(); it != v.end(); it++){
        cout << "姓名:" << it->mname << "," << "成绩:" << it->mscore << endl;
    }
}
*/ 

#include <iostream>    
#include <string>
#include <vector>
using namespace std;  

// 按照候选人成绩排名 --- 模板处理自定义数据类型 
// 1. 重载 
// 2. 具体化
class Candidate 
{
    public:
    Candidate(string name, int score); 
    string mname;  
    int mscore; 
};

// 析构 
Candidate::Candidate(string name, int score){
    this->mname = name;
    this->mscore = score; 
}

// template 1 Swap 
template <class DataType> 
void Swap(DataType &a, DataType &b){
    DataType temp = a; 
    a = b; 
    b = temp; 
} 

// template 2 --- Quick Sort (O(N^2/2) --- O(N^2))
template <class DataType> 
void SelectingSort(DataType arr[], int len){
    for (int i = 0; i < len; i++){
        int min = i; 
        for (int j = i + 1; j < len; j++){
            if (arr[min] > arr[j]){
                min = j; 
            }
        }
        // 若min下表不是i,交换 
        if (min!= i){
            Swap(arr[i], arr[min]); 
        }
    }
}    


// 模板重载 
template <class DataType>  
void SelectingSort(DataType &v){
    cout << "模板重载" << endl; 
    int len = v.size(); // vector 
    for (int i = 0; i < len; i++){
        int min = i; 
        for (int j = i + 1; j < len; j++){ 
            // 依据成绩排名 
            if (v[min].mscore > v[j].mscore){
                min = j; 
            }
        }
        // 若min下表不是i,交换 
        if (min!= i){
            Swap(v[i], v[min]); 
        }
    }
}    


template <class T> 
void PopSort();  

template <class T> 
void QuickSort(); 

// template tool --- ArrayPrint
template <class T> 
void printArray(T arr[], int len){
    for (int i = 0; i<len; i++){
        cout << arr[i] << " "; 
    }
    cout << endl; 
} 

// template<template<class> class T, class t>  
// 常规函数
// void printArray(vector<Candidate> &v){
//     int size = v.size();
//     for (vector<Candidate>::iterator it = v.begin(); it != v.end(); it++){
//         // -> 等价于 (*p).
//         cout << "姓名:" << it->mname << "," << "成绩:" << it->mscore << endl;
//     }
// }
// 需要在typename前加typename 
template <class T> 
void printArray(T &v){
    int size = v.size();  
    // typename用于指定迭代器类型的正确类型别名。
    for (typename T::iterator it = v.begin(); it != v.end(); it++){
        cout << "姓名:" << it->mname << "," << "成绩:" << it->mscore << endl;
    }
} 


void test01(){
    // test 01 --- char 数组 
    char charArr[] = "asfqwethjt"; 
    int num = sizeof(charArr) / sizeof(char); 
    // 排序前 
    cout << "Before Sort: ";
    printArray(charArr, num);
    
    // 快排 从小到大 
    SelectingSort(charArr, num);  
    cout << "After QuickSort: ";
    printArray(charArr, num);

    // delete num; 

    // test02 --- double数组 
    double doubleArr[] = {8.6, 1.2, 3.4,2.7, 0.8};
    int num2 = sizeof(doubleArr) / sizeof(double); 
    cout << "Before Sort: ";
    printArray(doubleArr, num2);
    SelectingSort(doubleArr, num2);  
    cout << "After QuickSort: ";
    printArray(doubleArr, num2);
} 

void test02(){
    // 自定义数据类型 
    // Candidate p1("小明", 95); 
    // Candidate p2("小李", 90);
    // Candidate p3("小张", 85);
    // Candidate p4("小王", 80); 
    // Candidate p5("小刘", 100);  

    string person[] = {"小明","小李","小张","小王","小刘"}; 
    int scores[] = {95, 90 , 85, 80, 100};  
    int nums = sizeof(scores) / sizeof(int); 
    vector<Candidate> vecs;  

    for (int i = 0; i<nums; i++){
        vecs.push_back(Candidate(person[i], scores[i])); 
    } 
    
    cout << "Before Sort: " << endl; 
    printArray(vecs);  
    cout << "After Sort: " << endl;
    SelectingSort(vecs); 
    printArray(vecs);
}

int main(){
    // test01 
    // test01();  
    test02();

    return 0; 
}

