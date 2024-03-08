#include <iostream>
using namespace std;

int main(){ 
    /////////////////////////////////////////////////
    // 1. 字符串拼接 
    string firstName = "John ";
    string lastName = "Doe";
    string fullName = firstName + lastName;
    cout << fullName << endl; 

    fullName = firstName + " " + lastName; // "+"符号 
    cout << fullName << endl;

    fullName = firstName.append(lastName); // append函数  
    cout << fullName << endl;

    /////////////////////////////////////////////////
    // 2. 字符串命令（长度length() or 尺寸size()） 
    string txt = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout << "The length of the txt string is: " << txt.length() << endl;
    cout << "The length of the txt string is: " << txt.size() << endl;

    /////////////////////////////////////////////////
    // 3. 字符串命令 访问 
    string myString = "Hello";
    cout << myString[0] << endl;
    myString[0] = 'J';
    cout << myString << endl;

    return 0; 
}