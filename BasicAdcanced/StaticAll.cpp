/*
Static那些事
https://light-city.github.io/basic_content/static/  

当与不同类型一起使用时，Static关键字具有不同的含义。我们可以使用static关键字：
1. 静态变量： 函数中的变量，类中的变量
2. 静态类的成员： 类对象和类中的函数

*/ 
#include <iostream> 
#include <string> 
using namespace std; 

/*
1. 静态变量 --- 函数中的变量 
   当变量声明为static时，空间将在程序的 生命周期 内分配。 
   即使多次调用该函数，静态变量的空间也只分配一次，前一次调用中的变量值通过下一次函数调用传递。
   这对于在C / C ++或需要存储先前函数状态的任何其他应用程序非常有用。
*/ 
void demo1(){
    // 1. static variable 
    static int count = 0; // 输出0 1 2 3 4，有效存储先前函数状态 ， 值通过函数调用来传递。每次调用函数时，都不会对变量计数进行初始化。
    // int count = 0; // 输出 0 0 0 0 0
    cout << count << endl; 

    // value update  
    count++; 
}

/*
2. 静态变量 --- 类中的变量  
*/
class Apple
{
    public:
        static int i; 
        Apple(){}

}; 

int Apple::i = 10; // 类中的静态变量应由用户使用类外的类名和范围解析运算符::显式初始化

void demo2(){ 
    // 错误, 尝试为多个对象创建静态变量i的多个副本。但这并没有发生
    Apple obj1; 
    Apple obj2; 
    obj1.i = 10;
    obj2.i = 5; 

    cout << obj1.i << " " << obj2.i << endl; 
}

void demo2Right(){
    Apple obj; 
    cout << obj.i << endl;
}  

/*
3. 静态成员 --- 类对象为静态 
   - 就像变量，对象也在声明为static时具有范围，直到程序的生命周期 
*/ 
class Orange{
    int i; 
    public:
        Orange(){
            i = 0; 
            cout << "Inside Constructor " << endl; 
        }
        ~Orange(){
            cout << "Inside Destructor " << endl;
        }
}; 

void demo3(){
    int x = 0; 
    if(x==0){
        // Orange obj;   // 输出 Inside Constructor \n Inside Destructor \n End of main --- 因为对象在if块内声明为非静态。因此，变量的范围仅在if块内
        static Orange obj; // 输出 Inside Constructor \n End of main \n Inside Destructor --- 在main结束后调用析构函数。这是因为静态对象的范围是贯穿程序的生命周期。
    } 
    cout << "End of main" << endl; 
}

/*
4. 静态成员 --- 类中的静态函数 
   静态成员函数也不依赖于类的对象, 我们被允许使用对象和'.'来调用静态成员函数。但建议使用类名和范围解析运算符::调用静态成员。 
   ---------
   允许静态成员函数仅访问静态数据成员或其他静态成员函数，它们无法访问类的非静态数据成员或成员函数。
*/

class Banana{
    public: 
        static void printMsg(){
            cout << "访问静态" << endl; 
        } 

        void printMsgNonStatic(){
            cout << "不可访问" << endl;  
        }
};

void demo4(){
    // invoking a static member function 
    Banana::printMsg(); // 可以直接访问静态 
    
    // Banana::printMsgNonStatic();  --- error非静态访问
    Banana obj; 
    obj.printMsgNonStatic(); // 正确访问
    
}

int main(){

    // demo01 -- 1. 静态变量 -- 函数中的变量
    for (int i = 0; i<5; i++){
        demo1();
    }  

    // demo02 -- 2.类中的静态变量
    // demo2();
    demo2Right();

    // demo03 -- 3. 静态成员--类对象为静态 
    demo3(); 

    // demo04 -- 4. 类中静态成员 
    demo4(); 
    return 0; 
}
