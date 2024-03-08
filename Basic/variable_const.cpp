#include <iostream> 
using namespace std; 

int main() {
    int myNum = 15;
    cout << myNum << endl;
    ///////////////////////////////////////////////////////////////
    int myNum1;     // 声明变量
    myNum1 = 15;    // 赋值
    cout << myNum1 << endl;
    ///////////////////////////////////////////////////////////////
    int myNum2 = 15;
    myNum2 = 10;
    cout << myNum2 << endl;
    ///////////////////////////////////////////////////////////////
    int myNum3 = 15;            //整型Integer
    double myFloatNum = 5.99;   //浮点型Float
    char myLetter = 'D';        //字符型Character
    string myText = "Hello";    //字符串String
    bool myBoolean = true;      //布尔型Boolean
    ///////////////////////////////////////////////////////////////
    int myAge = 35;
    cout << "I am " << myAge << " years old." << endl;
    ///////////////////////////////////////////////////////////////
    int x = 5;
    int y = 6;
    int z = 50;
    int sum = x + y + z;
    cout << sum << endl;
    ///////////////////////////////////////////////////////////////
    int x1 = 5, y1 = 6, z1 = 50;
    cout << x + y + z   << endl; 
    /////////////////////////////////////////////////////////////// 

    // 常量 CONST 
    const int minutesPerHour = 60; 
    const float PI = 3.14159;  
    const int constNum = 15; 

    // constNum = 10; // 报错，const 不能被修改 


    return 0;
}