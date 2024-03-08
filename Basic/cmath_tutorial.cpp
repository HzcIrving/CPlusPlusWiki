#include<iostream>
#include<cmath>
using namespace std;

/* 
cmath tutorial: https://www.w3cschool.cn/cpp/cpp-numbers.html 
*/
int main(){
    cout << max(5, 10) << endl;
    cout << min(5, 10) << endl;
    cout << sqrt(64) << endl; // double 
    cout << round(2.6) << endl;
    cout << log(2) << endl;

    cout << "abs(x)"
         << "Returns the absolute value of x" << abs(-5) << endl;
    cout << "acos(x)"
         << "Returns the arccosine of x" << acos(0.64) << endl;
    // ... 
    return 0;
}