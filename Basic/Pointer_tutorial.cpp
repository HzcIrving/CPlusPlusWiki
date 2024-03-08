#include <iostream> 
using namespace std; 

// 函数申明中的*x 
void foo(int * x); // 申明，参数是整数指针  

int main(){
    string food = "Pizza";
    string* ptr = &food; // 引用是 string& ref = food 

    cout << "food value: " << food << endl;         // Pizza
    cout << "ptr value: " << ptr << endl;           // 0x61fde0
    cout << "food address: " << &food << endl;      // 0x61fde0
    cout << "ptr address: " << &ptr << endl;        // 0x61fdd8
    cout << "ptr dereferenced: " << *ptr << endl;   // Pizza

    // change the value of the pointer
    *ptr = "Hamburger";
    cout << "food value: " << food << endl;         // Hamburger
    cout << "ptr value: " << ptr << endl;           // 0x61fde0 

    // 可以看到，指针ptr的值即所指向的变量food的地址，可以通过取地址符&获取变量的地址，可以通过解引用符*获取指针所指的内容。 
    // 指针和所指向的变量之间是密切相关的，修改指针所指的内容其实就是修改了所指向的变量的值。
    cout << "food address: " << &food << endl;      // 0x61fde0
    cout << "ptr address: " << &ptr << endl;        // 0x61fdd8
    cout << "ptr dereferenced: " << *ptr << endl;   // Hamburger

    
    ///////////////////////////////////////////
    // 2. 函数调用 *x 与函数申明 *x 
    int num = 10; 
    int *ptr_2 = &num; 

    foo(ptr_2); //函数调用，将指针ptr传递给函数

    return 0;
}

void foo(int *x){
    int value = *x ; // 解引用指针x，获取指针所指向的值 
    cout << "取数:" << value << endl; 
}