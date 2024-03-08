#include <iostream>
using namespace std;

int main(){

    //////////////////////////////////////////////////
    // 1. 基本运算 
    // int x = 5;
    // int y = 3;

    // cout << x + y << endl; // 8
    // cout << x - y << endl; // 2
    // cout << x * y << endl; // 15
    // cout << x / y << endl; // 1 # 
    // cout << x % y << endl; // 2 

    // // X++ 先执行cout，再执行x = x + 1 
    // cout << x++ << endl; // 5 
    // cout << x-- << endl; // 6  

    // // --X 先执行x = x + 1，再执行cout
    // cout << ++x << endl; // 6 
    // cout << --x << endl; // 5
    // cout << y++ << endl; // 3
    // cout << y-- << endl; // 4
    // cout << ++y << endl; // 4
    // cout << --y << endl; // 3
    
    //////////////////////////////////////////////////
    // 2. += , -= , *= , /= 
    // int x = 5;
    // x +=3;
    // cout << "x += 3: " << x << endl; // 8
    // x = 5;
    // x -=3;
    // cout << "x -= 3: " << x << endl; // 2
    // x = 5;
    // x *=3;
    // cout << "x *= 3: " << x << endl; // 15
    // x = 5;
    // x /=3;
    // cout << "x /= 3: " << x << endl; // 1


    //////////////////////////////////////////////////
    // 3. bool判断运算符  
    int x = 5;
    int y = 3; 

    // C++查看输出(x==y)变量的类型语法  
    cout << typeid(x).name() << endl;  // i (int)
    cout << typeid(x==y).name() << endl;  // b (bool)
    cout  << (x == y) << endl; // 0 返回的是布尔型
    cout  << (x != y) << endl; // 1
    cout  << (x > y) << endl; // 1
    cout  << (x < y) << endl; // 0
    cout  << (x >= y) << endl; // 1
    cout  << (x <= y) << endl; // 0

    //////////////////////////////////////////////////
    // 4. 与或非  
    cout << typeid(true && false).name() << endl; // b 
    cout << (true && false) << endl; // 0
    cout << (true || false) << endl; // 1
    cout << (!true) << endl; // 0

    return 0;
}