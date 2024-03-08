/*
https://learn.microsoft.com/zh-cn/cpp/cpp/pointers-cpp?view=msvc-170  

C++中三个主要用途
1. 堆区分配新对象 
2. 将函数传递给其他函数
3. 循环访问数组或其他数据结构中的元素 

新式 C++ 
- 提供了智能指针用于分配对象
- 提供了迭代器用于遍历数据结构
- 还提供了 Lambda 表达式用于传递函数。

[原始指针] 
指针是一种变量。 它将对象的地址存储在内存中，并用于访问该对象。 
原始指针是指其生存期不受封装对象控制的指针，例如智能指针。 
可以为原始指针分配另一个非指针变量的地址，也可以为其分配 nullptr 值。 
未分配值的指针包含随机数据。 

[const指针] 
const指针不能指向不同的内存位置，这种意义上说，类似于引用  
        const int | func1(); // 无意义，因为函数本身返回值需要赋值给其他变量 
        const int* | func2(); // 指针指向的内容不变 
        int *const | func3(); // 指针本身不可变。  
定义函数时，除非希望函数修改对象，否则请将指针参数指定为 const。 通常，const 引用是将对象传递给函数的首选方式，除非对象的值可能为 nullptr。 

[指向函数的指针]
指向函数的指针使函数能够传递给其他函数。  它们用于 C 风格编程中的“回调”。 
新式 C++ 使用 lambda 表达式来实现此目的。 

[初始化和成员访问] 
声明、初始化和使用原始指针。 它使用 new 初始化，以指向堆上分配的对象，必须显式删除 (delete) 该对象。

[原始指针容易发生内存泄漏] 
1. C --- malloc(), free()释放 --- malloc只分配内存 
   C++ --- new,  delete释放 --- new则更进一步，不仅分配了内存，还调用了构造函数进行初始化 
2. 使用构造和析构解决内存泄漏
    5-1 : 就算发生了异常，也能够保证析构函数成功执行！这里的例子是这个资源只有一个人使用，我不用了就将它释放掉。 
    5-2 : 一份资源被很多人共同使用，要等到所有人都不再使用的时候才能释放掉

[固定和可变指针] 
1. const 和 volatile 关键字可更改处理指针的方式。 
    - const 关键字指定指针在初始化后无法修改；此后指针将受到保护，防止进行修改。 
    - volatile 关键字指定与后跟的名称关联的值可由用户应用程序中的操作以外的操作修改。 
      因此，volatile 关键字对于声明共享内存中可由多个进程访问的对象或用于与中断服务例程通信的全局数据区域很有用。
      - 如果某个名称被声明为 volatile，则每当程序访问该名称时，编译器都会重新加载内存中的  
        值。 这将显著减少可能的优化。 但是，当对象的状态可能意外更改时，这是保证可预见的程序性能的唯一方法。


*/ 

#include <iostream> 
#include <string> 
using namespace std; 

class MyClass{
    public: 
        MyClass(int num, string name){
            this->num = num; 
            this->name = name; 
        }
        int num; 
        string name; 
        void print(){cout << name << ":" << num << endl;} 

}; 

// 1. 原始指针 
void demo01(){ 

    // 指针初始化, nullptr，避免包含随机数据 
    int *p = nullptr;  

    int i = 5; 
    p = &i;  // 地址 
    int j = *p;  
    cout << "j = " << j << endl; 

} 

// 2. const指针  
void demo02(){
    // non-const pointer, 只是指针指向内容不可变
    const char* std = "Hello World";   

    const int c = 1; 
    const int *pconst = &c;   // non-const pointer, 指向const int 
    const int c2 = 2; 
    pconst = &c2; // pconst itself isn't const   
    const int* const pconst2 = &c; // pconst2是一个const指针，指向const int  
    // pconst2 = &c2;  // error 
}

// 3. malloc & new 
void demo03(){
    // malloc返回值是void 
    int *argC = (int *)malloc(sizeof(int));
    free(argC);  

    string *argC2 = new string("25"); // 1. 分配内存，初始化
    delete argC2; 
}

// 4. 初始化和成员访问 
// 声明、初始化和使用原始指针   
// C风格编程，非C++ ----------- !!! 
void func_A(MyClass *mc){  // 接收MyClass Pointer
    mc->num = 3;  
    // 修改mc指向的对象属性;  
    // 所有pt拷贝都指向相同的修改对象 
}  
void func_B(MyClass mc){ // 接受 MyClass 对象
    mc.num = 21;   // 此语句仅修改 mc 的本地副本。
    cout << "MC的局部拷贝" ; 
    mc.print(); 
}
void demo04(){
    // new 分配与初始化内存  --- 堆区 
    MyClass *pmc = new MyClass(108, "Nick"); 
    cout << "Pointer pmc Address:" << pmc << endl;   // Pointer Address:0xf87570   
    pmc->print();  

    // 通过解除对指针的引用来复制指向的对象 
    // mc 是一个单独的对象，在栈区上分配, 自动回收 
    MyClass mc = *pmc;     
    cout << "mc Address" << &mc << endl;  // mc Address0x61fd70

    // 使用 & 操作符声明一个指向 mc 的指针
    MyClass* pmc_copy = &mc;  
    cout << "Pointer pmc_copy Address:" << pmc_copy << endl; // Pointer pmc_copy Address:0x61fd70  

    // 指针拷贝, pmc2和pmc指向一个对象 
    MyClass *pmc2 = pmc; 
    cout << "Pointer pmc2 Address: " << pmc2 << endl;  // Pointer Address:0xf87570   
    // Modify 
    pmc2->name = "HeZichen";
    pmc->print();  // "HeZichen:108"
    pmc2->print(); // "HeZichen:108"    

    // 将指针传递给函数。 
    func_A(pmc);  // 可以修改源对象 
    pmc->print();  // HeZichen:3
    pmc2->print();  // HeZichen:3 

    //  取消对指针的引用并传递一个副本 
    func_B(*pmc); 
    pmc->print();  


    // new一个，要删掉  
    delete(pmc); 
    // delete(pmc2); // Crush ... 已经被删了    
    // cout << pmc2 << endl; 
}

// 5. 内存泄漏问题  
// new和delete必须成对出现，有时候是不小心忘记了delete，有时候则是很难判断在这个地方自己是不是该delete，这个和资源的生命周期有关，这个资源是属于我这个类管理的还是由另外一个类管理的（其它类可能要使用），如果是别人管理的就由别人delete。 
void badThing(){
    throw 1; // 抛出异常
} 

void demo05(){
    char *a = new char[1000];  
    badThing();  // 程序在中间的时候抛出了异常，由于没有立即捕获，程序从这里退出了
    delete[] a; // 内存泄漏 
}

// 5-1 解决办法1 --- 基于构造和析构的内存泄漏解决方法 
// 一份资源单人使用，不用了就释放
class SafeIntPointer{ 
    // explicit 关键字表示这个构造函数是显式的，即在调用时必须显式地指定参数。 
    // 构造函数中初始化一个新的整数对象，并将该对象的指针存储在成员变量 m_value  
public: 
    // explicit SafeIntPointer(int v) : m_value(new int(v)) {}
    SafeIntPointer(int v){
        m_value = new int(v);
    }
    ~SafeIntPointer(){ delete m_value; 
        cout << "析构函数内存释放" << endl;  
     } 
    int get() {return *m_value; }
private:
    int *m_value = nullptr;
};

void demo06(){
    SafeIntPointer a(5);
    badThing(); 
} 

// 5-2 解决办法2 --- 一份资源被很多人共同使用，要等到所有人都不再使用的时候才能释放掉，对于这种问题
//     就需要对上面的SafeIntPointer增加一个引用计数 
class SafeIntPointer2{
    public:
        explicit SafeIntPointer2(int v): m_value(new int(v)), m_used(new int(1)){} 

        // 拷贝构造
        SafeIntPointer2(const SafeIntPointer2& other){ 
            cout << "&other: " << &other << endl;  
            cout << "this: " << this << endl;  

            m_used = other.m_used; 
            m_value = other.m_value;  
            (*m_used)++; // 引用计数+1 

            cout << "拷贝构造调用 --- m_used + 1" << endl; 
        } 

        // 赋值 operator=  
        // https://blog.csdn.net/xiaozhidian/article/details/114377907
        SafeIntPointer2 &operator= (const SafeIntPointer2& other){ 
            cout << "&other: " << &other << endl;  
            cout << "this: " << this << endl; 
            if (this == &other) // 避免自我赋值 --- 同一个内存地址 
                return *this;  
            
            m_used = other.m_used; 
            m_value = other.m_value; 
            (*m_used)++; 
            cout << "赋值构造调用 --- m_used + 1" << endl;  
            return *this;
        }  


        // 最后每次析构一次后引用计数减一 
        // 直到全部释放 引用计数为 0，才真正释放资源
        ~SafeIntPointer2(){
            cout << "析构函数内存释放" << endl; 
            (*m_used) --; // 引用计数 -1  
            if(*m_used == 0){
                delete m_value; 
                delete m_used;  
                cout << "所有人都不再使用的时候性能释放" << endl; 
            }
        } 


        int get() {return *m_value; } 

        int getRefCount(){
            return *m_used; // 计数显示 
        }

    private: 
        int *m_value;  
        int *m_used; // 引用计数 
}; 

void demo07(){
    SafeIntPointer2 a(5);  
    cout << "ref count = " << a.getRefCount() << endl; 
    SafeIntPointer2 b(a);  
    cout << "ref count = " << a.getRefCount() << endl;
    SafeIntPointer2 c = b; // 拷贝构造 与SafeIntPointer2 c(b)等价
    cout << "ref count = " << a.getRefCount() << endl; 
    SafeIntPointer2 d(5);
    d = c;   // 
    cout << "ref count = " << a.getRefCount() << endl; 
}

int main(){

    // demo01();  
    // demo02(); 
    // demo03(); 

    // demo04(); 

    // 内存泄漏
    // try{
    //     demo05(); 
    // }
    // catch(int i){
    //     cout << "error happened --- " << i << endl; 
    // } 

    // 构造、析构 避免内存泄漏  
    try{
        // demo06(); 
        demo07(); 
    }
    catch(int i){
        cout << "error happened --- " << i << endl; 
    }


    return 0; 
}