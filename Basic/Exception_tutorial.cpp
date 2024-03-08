#include<iostream>
#include<fstream>
using namespace std;

int main(){
    try{
        int age = 15 ;
        if (age > 18){
            cout << "Access granted - you are old enough.";
        }else{
            throw (age);    // throw an exception
        }
    }
    catch(int myNum){
        cout << "Access denied - You must be at least 18 years old.\n";
        cout << "Age is: " << myNum << endl;
    }

    try
    {
        int age = 15;
        if (age > 18) {
            cout << "Access granted - you are old enough.";
        } else {
            throw 505;   
        }
    }
    catch(...)  // 捕获所有异常
    {
        cout << "Access denied - You must be at least 18 years old.\n";
    }

}