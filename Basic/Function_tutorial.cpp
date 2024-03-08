/*
函数章节，很快奥，啪的一下 
*/

#include<iostream>
#include <string>
using namespace std;

// 申明 
void myFunction();  
void void_paramin(string fname);  
void void_paramin_multi(string fname,int age);  

// 函数先声明后定义再使用；也可以无声明只定义后使用。
// 默认参数不能在声明和定义中同时出现  
// 默认参数在申明里定义即可  
void void_paramin_default(string fname="defaultXiaoming");
int int_sum(int x, int y);  

// Swap 
void swap1(int x, int y); 
void swap2(int &x, int &y);  
void swap3(int *x, int *y); 

// 重载 
int plusFunc(int x, int y); 
double plusFunc(double x, double y); 

int main(){ //int means that the function returns an integer value
    myFunction();   //function call
    void_paramin("Liana");  
    void_paramin_default(); 
    void_paramin_multi("Hezichen",13); 
    int_sum(99,58); 

    int first = 10; 
    int second = 20;  

    // swap1，不改变 
    cout << "Before swap1: " << first << " " << second << endl;
    swap1(first, second);
    cout << "After swap1: " << first << " " << second << endl; 
    
    // swap2, 改变  
    // 调用swap2(&first, &second)是错误的，因为&符号用于获取变量的地址，而swap2函数期望的是引用而不是指针。正确的调用方式是直接传递变量本身，即swap2(first, second)。 
    // 在函数内部，x和y将成为first和second的别名，并且通过交换它们的值来实现交换效果。
    swap2(first, second);
    cout << "After swap2: " << first << " " << second << endl;  // 10,20 -> 20, 10 

    // swap3, 指针的调用 , 改变  
    // 要调用这个使用指针的swap2函数，你需要传递first和second的地址。这可以通过使用取地址操作符&来实现
    swap3(&first, &second);
    cout << "After swap3: " << first << " " << second << endl; // 20, 10 -> 10, 20 

    // 重载调用 
    int myNum1 = plusFunc(10, 20); 
    double myNum2 = plusFunc(10.5, 20.5);  
    cout << "重载前，myNum1: " << myNum1 << endl; 
    cout << "重载后，myNum2: " << myNum2 << endl;
    return 0;
}

// void 无返回值 
void myFunction(){ // void means that the function does not have a return value
    cout<<"I just got executed"<<endl;
}

// void 传参类型 
void void_paramin(string fname){
    cout <<fname<<" Ok void-paramin-exeu \n";
}

// void 多变量  
void void_paramin_multi(string fname,int age){
    cout<<fname<<" Refsnes. "<<age<<" years old. \n";
} 

// void 参数传递默认 
void void_paramin_default(string fname){
    cout << fname << "Ok void_paramin_default-exeu" << endl;   
}

// int  加和
int int_sum(int x, int y){ 
    cout << "Sum Result:" << x+y << endl; 
    return x + y; 
}

/*
当你在调用一个函数时，你可以将参数以值的形式传递，也可以将参数的地址传递给函数，让
函数通过引用来修改参数的值。
*/ 
// void 值传递 By Value ...  
// swap1函数使用的是值传递，它接受两个整数参数x和y，并在函数内部进行交换。
// 这种情况下，函数内部交换的是局部变量的值，而不会影响到main函数中的first和second。
void swap1(int x, int y){
    int temp = x; 
    x = y; 
    y = temp;  
}

// void 引用传递  By Reference ... 
// swap2函数使用的是引用传递，它接受两个整数的引用x和y。
// 通过使用引用，函数可以直接修改传递给它的变量的值。当你在main函数中调用swap2时，传递的是first和second的引用，这意味着swap2函数内部的操作会直接影响到main函数中的first和second。   
void swap2(int &x, int &y){
    // 传的是地址 
    int temp = x; 
    x = y; 
    y = temp; 
}

// void 指针传递 By Pointer ...
// 参数x和y是指向整数的指针。通过使用指针，我们可以通过解引用操作符*来访问指针所指向的值。 
// 在函数内部，temp变量保存了x指针所指向的值。然后，通过解引用x和y指针，并将它们的值进行交换。  
void swap3(int *x, int *y){
    int temp = *x; 
    *x = *y; 
    *y = temp; 
}

// 函数重载 
/*
重载的定义： 函数重载是指在同一个作用域（通常是在同一个类或命名空间中）中定义多个具有相同名称但参数列表不同的函数。函数重载允许你使用相同的函数名来执行不同的操作，根据传递给函数的参数类型和数量来选择正确的函数版本。 是不是没看懂，大白话就是：多个函数可以具有相同的名字、不同的传入参数，由传入参数区分你想调用的函数。 例如，以下的两个plusFunc根据传入的数据类型不一样，都成功被调用了
*/
int plusFunc(int x, int y){
    return x + y;
} 

double plusFunc(double x, double y){
    return x + y;
}