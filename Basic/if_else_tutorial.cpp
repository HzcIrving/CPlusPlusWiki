/*
条件语句 
if 
else if 
else 
三目运算 
*/ 
#include <iostream> 
#include <cmath> 

using namespace std; 

int main(){

    // 生成一个[0,20]的随机数 
    int x = rand()%20; 
    int y = rand()%20; 

    cout << "x=" << x << ";y=" << y << endl; 

    if (x>y){
        cout << "x is bigger" << endl; 
    }else if(x==y){
        cout << "x==y" << endl;
    }else{
        cout << "y is bigger" << endl; 
    }  


    // 三目运算一般模板
    // 类型 A = (条件) ? 满足 : 不满足; 
    int time = rand() % 100 ; 
    cout << "time type:" << typeid(time).name() << endl;  
    string result = (time<50) ? "time is less than 50" : "time is bigger than 50" ; 
    cout << result << endl; 
    return 0; 
}
