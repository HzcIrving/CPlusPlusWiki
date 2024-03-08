#include<iostream>
using namespace std; 

int main(){
    // 1. while 
    int couter = 0; 
    while (couter < 5){
        cout << couter << endl; 
        couter++; 
    }

    // 2. do while 
    int cout2 = 0; 
    do{
        cout << cout2 << endl; 
        cout2++; 
    }while (cout2 < 5);  

    // 3. 用for 实现上述功能
    for (int cout3 = 0; cout3 < 6; cout3++){  
        if (cout3==5){ // overflow warning ... 
            continue;
        }
        cout << cout3 << endl;
    } 

    return 0; 
}