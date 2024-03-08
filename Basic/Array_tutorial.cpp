/*
数组学习 
P.S. 知识 setw 
*/
#include<iostream>
#include<string> 
#include <algorithm> 
#include <iomanip>

using namespace std;  

// 在C++中，std::setw是一个使用iomanip库的辅助函数，用于设置输出字段宽度。 
// std::setw函数接受一个整数参数，表示要设置的字段宽度。例如，如果你想要将一个整数输出为10位宽的字段，可以使用std::setw(10)。 
using std::setw; 

// 功能函数，数组个数 
// int getArraySize(string arr[]){
//     return sizeof(arr) / sizeof(arr[0]); 
// }

int main(){
    // 定义一个数组  
    // type arrayName [ arraySize ]; 
    string cars[4] = {"Volvo", "BMW", "Ford", "Mazda"}; // array of strings  
    string bands[] = {"Volvo", "BMW", "Ford", "Mazda", "Tesla"};    // size of array is 5 未分配内存 
    int myNums[3] = {10,20,30} ;

    cout  << typeid((sizeof(cars)/sizeof(cars[0]))).name() << endl;   // y代表unsigned long long int ... 

    // cout << "The size of bands is:" << bands->size() << endl; 
    // cout << "The size of myNums is:" << myNums->() << endl;

    for(int i = 0; i < int(sizeof(bands)/sizeof(bands[0])); i++){
        cout << i << ":" <<  bands[i] << endl; 
    } 

    // 声明数组 
    int n[10];  

    // 数组赋值 
    for(int j = 0; j<10; j++){
        n[j] = j + 100; 
    } 

    // setw方便对齐 
    cout << "Element" << setw(13) << "Value" << endl;   

    // 输出数组中每个元素的值                     
    for ( int j = 0; j < 10; j++ ){
        cout << setw( 7 )<< j << setw( 13 ) << n[ j ] << endl;
    }

    return 0; 
}