#include<iostream>
using namespace std;

int main(){ 
    // \t是制表符，用于对齐  
    // sizeof()是C++的内置函数，用于计算变量的字节数(1字节=8bits)
    /*
    type    value   size
    int     5       4
    float   5.99    4
    double  9.98    8
    float   35000   4
    double  120000  8
    char    D       1
    bool    1       1
    string  Hello   32
    */

    cout << "type\t" << "value\t" << "size" << endl; 

    int myNum = 5; // Integer (whole number without decimals)  
    cout <<  "int\t" << myNum << '\t' << sizeof(myNum) << endl; 
    float myFloatNum = 5.99; // Floating point number (with decimals)
    cout << "float\t" << myFloatNum << '\t' << sizeof(myFloatNum) << endl;

    double myDoubleNum = 9.98; // Floating point number (with decimals)
    cout << "double\t" << myDoubleNum << '\t' << sizeof(myDoubleNum)<< endl;

    float f1 = 35e3; // Scientific numbers
    double d1 = 12E4;
    cout << "float\t" << f1 << '\t' << sizeof(f1) << endl;
    cout << "double\t" << d1 << '\t' << sizeof(d1) << endl;

    char myLetter = 'D'; // Character 
    cout << "char\t" << myLetter << '\t' << sizeof(myLetter) << endl;

    bool myBoolean = true; // Boolean
    cout << "bool\t" << myBoolean << '\t' << sizeof(myBoolean) << endl;

    string myText = "Hello"; // String
    cout << "string\t" << myText << '\t' << sizeof(myText) << endl;

    return 0;
}