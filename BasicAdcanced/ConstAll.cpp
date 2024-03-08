/*
https://light-city.github.io/basic_content/const/
const那些事儿总结

1. 含义
   使用类型修饰符const说明的类型，常类型的变量或对象是 [不能被更新] 的。   
   const 定义的变量只有类型为整数或枚举，且以常量表达式初始化时才能作为常量表达式。
   其他情况下它只是一个 const 限定的变量，不要将与常量混淆。 

2. const 与 define 
   const常量与#define宏定义常量的区别：
    const常量具有类型，编译器可以进行安全检查；
    #define宏定义没有数据类型，只是简单的字符串替换，不能进行安全检查。 

3. 作用总结
    1) 定义常量 
    2) 类型检查 e.g. const int/... 具有类型  
    3) 防止修改，保护作用  e.g. void f(const int i)  
    4) 节省空间，避免不必要的内存分配 
       const定义常量从汇编的角度来看，只是给出了对应的内存地址，而不是像#define一样给出的是立即数。
       所以，const定义的常量在程序运行过程中只有一份拷贝，而#define定义的常量在内存中有若干个拷贝。 

4. 指针与Const : 如果const位于*的左侧，则const就是用来修饰指针所指向的变量，即指针指向为常量； 
                 如果const位于*的右侧，const就是修饰指针本身，即指针本身是常量。  
    *左---指针指向常量， *右---常量指针
    --------------------------------------------------------------------------------
    const char * a; //指向const对象的指针或者说指向常量的指针。
    char const * a; //同上
    char * const a; //指向类型对象的const指针。或者说常指针、const指针。
    const char * const a; //指向const对象的const指针。 
    ---------------------------------------------------------------------------------

5. 指向常量指针小结：   
    1) 对于指向常量的指针，不能通过指针来修改对象的值。 
    2) 也不能使用void`*`指针保存const对象的地址，必须使用const void`*`类型的指针保存const对象的地址。 
    3) 允许把非const对象的地址赋值给const对象的指针，如果要修改指针所指向的对象值，必须通过其他方式修改，不能直接通过当前指针直接修改。 

6. Const引用传参 
    函数中使用const --- 对于非内部数据类型的输入参数，应该将“值传递”的方式改为“const 引用传递”，目的是提高效率。例如将void func(A a) 改为
                      void func(const A &a)。
                      对于内部数据类型的输入参数，不要将“值传递”的方式改为“const 引用传递”。否则既达不到提高效率的目的，
                      又降低了函数的可理解性。例如void func(int x) 不应该改为void func(const int &x). 
    1) const修饰函数返回值  --- return层
        const int | func1(); // 无意义，因为函数本身返回值需要赋值给其他变量 
        const int* | func2(); // 指针指向的内容不变 
        int *const | func3(); // 指针本身不可变。 
    2) const修饰函数参数 --- 函数输入 
        a. 传递过来的参数及指针本身在函数内不可变，无意义！ 
        表明参数在函数体内不能被修改，但此处没有任何意义，var本身就是形参，在函数内不会改变。包括传入的形参是指针也是一样。 
        P.S. 输入参数采用“值传递”，由于函数将自动产生**临时变量**用于复制该参数，该输入参数本来就无需保护，所以不要加const 修饰。
        - void func(const int var)   // 传递过来的参数不可变
        - void func(int *const var)  // 指针本身不可变  
        --------------------
        b. 参数指针所指内容为常量不可变
        - void Stringcopy(char *dst, const char *src); 
        - 这里，dst是输出参数，src是输入参数，字符串复制
        - 给src加上const修饰后，如果函数体内的语句试图改动src的内容，编译器将指出错误。 --- const的主要作用之一  
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~面试1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
        - 如果函数需要传入一个指针，是否需要为该指针加上const，把const加在指针不同的位置有什么区别? 【面试题1】
        - 答：看情况而定，int *const var 指的是指针本身不可变；const int *var 指指向常量的指针. 
        -------------------- 
        c. 参数为引用，为了增加效率同时防止修改 ******* 
        - void func(const A &a)
        - 对于非内部数据类型的参数而言，象void func(A a) 这样声明的函数注定效率比较低。因为函数体内将产生A类型的临时对象用于复制参数a，而临时对象的构造、复制、析构过程都将消耗时间.(A类型是自定的)
        - 为了提高效率，可以将函数声明改为void func(A &a)，因为“引用传递”仅借用一下参数的别名而已，不需要产生临时对象。但是函数void func(A &a) 存在一个缺点： “引用传递”有可能改变参数a，这是我们不期望的。解决这个问题很容易，加const修饰即可，因此函数最终成为void func(const A &a)。 
        P.S. 以此类推，是否应将void func(int x) 改写为void func(const int &x)，以便提高效率？完全没有必要，因为内部数据类型的参数不存在构造、析构的过程，而复制也非常快，“值传递”和“引用传递”的效率几乎相当。 
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~面试2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
        - 如果写的函数需要传入的参数是一个复杂类型的实例，传入值参数或者引用参数有什么区别，什么时候需要为传入的引用参数加上const。【面试题】
        - 答：引用参数效率更高，因为对于复杂类型实例的临时对象构造、复制、析构都会消耗时间；而引用传递仅仅借用参数别名，不会产生临时对象。若不能改变参数，则需要加const.  

7. 类中使用const 
    在一个类中，任何不会修改数据成员的函数都应该声明为const类型。
    如果在编写const成员函数时，不慎修改数据成员，或者调用了其它非const成员函数，编译器将指出错误，这无疑会提高程序的健壮性。
    使用const关字进行说明的成员函数，称为常成员函数。
    只有常成员函数才有资格操作常量或常对象，没有使用const关键字明的成员函数不能用来操作常对象。

*/      
#include <iostream> 
using namespace std; 

#define A 100;  

// const 可以防止修改，起保护作用，增强程序健壮性
void f(const int i){
    // i++; //error ! 
    cout << i << endl; 
}

// 类中使用const 
class Apple{
    private: 
        int people[100];
    public:
        Apple(int i); 
        static const int apple_number; 

        // const对象只能访问const成员函数,而非const对象可以访问任意的成员函数,包括const成员函数. 
        void take(int num) const;   
        
        int add(int num);   

        // 在类中声明的成员函数前加上const关键字，表示该成员函数不会修改类的成员变量
        int add(int num) const; 

        int getCount() const; 
};

// 初始化apple_number(const) 
// 类中的const成员变量必须通过初始化列表进行初始化 
// Apple::Apple(int i){
//     apple_number = i; 
// }
// Apple::Apple(int i):apple_number(i){
// } 

const int Apple::apple_number = 10; 

int Apple::add(int num){
    take(num);
} 

int Apple::add(int num) const{
    take(num);
}

void Apple::take(int num) const{
    cout<<"take func "<<num<<endl;
} 

int Apple::getCount() const{
    take(1); 
    // add(apple_number); 
    return apple_number; 
}

int main(){
    // --------------- 作用1. 定义常量 ------------------- 
    const int a = 100;   
    // a = 10;  // error ! a 不可更改  
    // const int b;  error ! b 是常量，必须要初始化 **  


    // ---------------- 指针与Const ---------------------- 
    // * 左边 --- 指针指向const常量 
    // * 右边 --- 常量指针  
    
    // 1) 指向常量指针  
    //    ptr是一个指向int类型const对象的指针，const定义的是int类型，也就是ptr所指向的对象类型，而不是ptr本身，
    //    所以ptr可以不用赋初始值。但是不能通过ptr去修改所指对象的值。
    const int * ptr;  
    // *ptr = 10; // error !  不可修改  
    // 允许把非const对象的地址赋给指向const对象的指针。 
    int val = 3; 
    ptr = &val; 
    // *ptr = 10; // error ! 我们不能通过ptr指针来修改val的值，即使它指向的是非const对象! 
    // 通过如下方式进行修改   
    cout << "------" << "指向常量指针" << "------" << endl; 
    cout << "修改前:" << *ptr << endl; 
    int * ptr2 = &val; 
    *ptr2 = 10; 
    cout << "修改后" <<  *ptr << endl;  


    // 2) 常指针 
    // const指针必须进行初始化，且const指针的值不能修改。  
    cout << "------" << "常指针" << "------" << endl; 
    int num = 0;
    int *const ptr3 = &num; // 常指针初始化，且不可修改  

    // 修改ptr指针所指向的值，可以通过非const指针来修改。 
    int *t = &num; 
    *t = 1; 
    cout << *ptr3 << endl; // 通过这种方式修改  

    // 不可把常量的地址给常指针，因为常指针指向是变量
    const int num2 = 9999999; 
    // int *const ptr4 = &num2;   // error ! 
    // 可以用指向常量的指针或者指向常量的常量指针 
    const int *ptr4 = &num2;   // 指向常量的指针 
    cout << *ptr4 << endl; 
    const int * const ptr5 = &num2;  // 指向常量的常量指针
    cout << *ptr5 << endl;   


    cout << "------" << "类使用const" << "------" << endl;  
    return 0; 
}