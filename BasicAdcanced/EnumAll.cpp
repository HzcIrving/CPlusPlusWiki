/*
enum那些事 
https://light-city.github.io/basic_content/enum/ 

1. enum 
- C++中的enum枚举类是一种用户定义的常量类型，用于表示一组相关值 
- 枚举定义了一组命名的常量，这些常量可以通过枚举类成员引用   
*/ 

#include <iostream> 
#include <string> 
using namespace std; 

enum DEMO{
    ONE , 
    TWO,
    THREE
};  

/*
1. enum 枚举定义 
*/

void demo1(){
    // 1. 枚举demo 
    DEMO c = ONE; 
    if (c == ONE) {
        std::cout << "The color is red" << std::endl;
    } else if (c == TWO) {
        std::cout << "The color is green" << std::endl;
    } else if (c == THREE) {
        std::cout << "The color is blue" << std::endl;
    } 
}

/*
2. enum的问题
    枚举有如下问题：
    作用域不受限,会容易引起 *命名冲突* 。例如下面无法编译通过的：  
    ----------------------------------
    enum Color { RED, BLUE };
    enum Feeling { EXCITED, BLUE }; 

    int main() {
    Color a = BLUE; // error --- 冲突
    Feeling b = EXCITED;
    std::cout << a << ":" << b << std::endl;
    return 0;
    } 
    ----------------------------------
    解决冲突的一种方法，给枚举变量命名加上前缀，如下所示
*/ 
enum Color{
    RED, 
    // BLUE 
    ColorBLUE 
};

enum Feeling{
    EXCITED, 
    FeelingBLUE, // 抑郁的 
}; 

void demo2(){
    Color a = ColorBLUE;  // error  
    Feeling b = FeelingBLUE; 
    cout << "Color is " << a << ", and feeling is " << b << endl;  // Color is 1, and feeling is 1  会隐式转换为int
}

/*
3. 解决命名冲突的另一种做法： 命名空间，然后基于范围解析运算符进行解决  
----------------------------------------------------------------
不过，因为命名空间是可以随后被扩充内容的，所以它提供的作用域封闭性不高。 
在大项目中，还是有可能不同人给不同的东西起同样的枚举类型名。 
更“有效”的办法是用一个类或结构体来限定其作用域。--- demo4 
*/  
namespace COLOR{
    enum Type{
        RED, 
        YELLOW=100,
        BLUE 
    };
}; 

void demo3(){ 
    using namespace COLOR; 
    Type color = YELLOW;    
    // COLOR::Type color2 = COLOR::YELLOW; // 等价
    cout << "Color is " << color << endl;
} 

/*
4. 解决命名冲突的第三种做法 --- 结构体 
-------------------------------------------
   不用担心类在别处被修改内容 
   这里用结构体而非类，一是因为本身希望这些常量可以公开访问 
   二是因为它只包含数据没有成员函数。
*/ 
struct COLOR2{
    enum Type{
        RED, 
        YELLOW = 111, 
        BLUE
    };
}; 
void demo4(){
    COLOR2 color2; 
    cout << "color is "<<color2.YELLOW << endl;  
}

/*
5. C++11的枚举类 enum class
----------------------------------------------
下面等价于enum class Color2: init  
新的enum作用域不是在全局，且不能隐式转换成其他类型, 要借助static_cast<int> 
*/
enum class Color3{
    RED,
    YELLOW = 1111,
    BLUE
}; 

void demo5(){
    // 枚举类 
    Color3 color3 = Color3::YELLOW; 
    // cout << "枚举类YELLOW:"<< color3 << endl;  error 
    cout << "枚举类YELLOW:" << static_cast<int>(color3) << endl;
} 

/*
6. C++11的枚举类 
----------------------------------------------
能够指定特定的类型来存储enum 
*/ 
enum class Color4:char; // 前向声明 
// 定义 
enum class Color4:char{
    YELLOW='r', // char '', string ""
    BLUE 
}; 

void demo6(){
    // 调用 
    // char color4 = static_cast<char>(Color4::YELLOW);  // 注意这里color4是char --- 指定的类型 ，与下面等价 
    // cout << "指定类型的枚举类YELLOW:" << color4 << endl;
    Color4 color4 = Color4::YELLOW; 
    cout << "指定类型的枚举类YELLOW:" << static_cast<char>(color4) << endl;
} 

/*
7. 类中的枚举类型 
   有时候希望某些常量只在类中有效，由于#define 定义的宏常量是全局的，不能达到目的 
   -------------------------------------------------------------------------
   1) 基于const修饰数据成员，但是const数据成员是客观存在的，无法修改
      const数据成员只在某个对象生存期内是常量，而**对于整个类而言却是可变的**，因为类可以创建多个对象，**不同的对象其 const 数据成员的值可以不同**。  
      错误示范：
      ------------
        class A 
        {
        const int SIZE = 100;   // 错误，企图在类声明中初始化 const 数据成员 
        int array[SIZE];  // 错误，未知的 SIZE 
        }; 
      ------------ 
      正确的，应该在类的构造函数的初始化列表中进行 
      ------------ 
        class A 
        {
            A(int size);  // 构造函数 
            const int SIZE ;    
        }; 
        A  a(100); // 对象 a 的 SIZE 值为 100 
        A  b(200); // 对象 b 的 SIZE 值为 200 
      ------------

    2) 基于Enum常量来实现 
*/
class Person{
    public: 
        // typedef用于为enum类型定义一个别名Gender
        typedef enum {
            MALE = 1, 
            FEMALE = 2
        } Gender;   
}; 

// 类中的枚举类型 , 只在类中有效
void demo7(){
    cout << "GENDER-MALE: " << Person::MALE << endl;  
    cout << "GENDER-FEMALE: " << Person::FEMALE << endl; 
}


int main(){
    // demo1(); 
    demo2(); // 命名冲突问题

    demo3(); // 命名空间 

    demo4(); // 结构体解决冲突 

    demo5(); // 枚举类 

    demo6(); // 枚举类指定类型 

    demo7(); // 类中的枚举类型 

    return 0; 
}