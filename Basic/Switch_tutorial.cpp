#include <iostream>
using namespace std;

int main(){

    int day = 4;  
    day = (day-1) % 7 + 1 ;

    // 写一个判断今天是周几的switch程序
    switch (day){
        case 1:
            cout << "Monday" << endl; 
            break; 
        case 2:
            cout << "Tuesday" << endl; 
            break; 
        case 3:
            cout << "Wednesday" << endl; 
            break; 
        case 4:
            cout << "Thursday" << endl; 
            break; 
        case 5:
            cout << "Friday" << endl; 
            break; 
        case 6:
            cout << "Saturday" << endl;
            break;
        case 7:
            cout << "Sunday" << endl; 
            break; 
        default:
            cout << "Invalid day" << endl; 
    } 
    return 0; 
}