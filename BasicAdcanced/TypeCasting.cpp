/*
众所周知C++关于类型转换引入了四种方式：

static_cast
const_cast
dynamic_cast
reinterpret_cast

1. 背景 
我们都知道C++完全兼容C语言，C语言的转换方式很简单，可以在任意类型之间转换，但这也恰恰是缺点，因为极其不安全，
可能不经意间将指向const对象的指针转换成非const对象的指针，可能将基类对象指针转成了派生类对象的指针，这种
转换很容易出bug，需要严格审查代码才能消除这种隐患，但是C这种转换方式不利于我们审查代码，且程序运行时也可能会出bug。

而C++引入的这几种类型转换可以完美的解决上述问题，不同场景下不同需求使用不同的类型转换方式，同时有利于代码审查。 

2. static_cast 
使用场景：
基本数据类型之间的转换使用，例如float转int，int转char等，在有类型指针和void*之间转换使用，子类对象指针转换成父类对象指针也可以使用static_cast。 

3. dynamic_cast 
用于将父类的指针或引用转换为子类的指针或引用，此场景下父类必须要有虚函数，因为dynamic_cast是运行时检查，检查需要运行时信息RTTI，而RTTI存储在虚函数表中，关于虚函数表具体可以看我的这篇文章：面试系列之C++的对象布局 

4. const_cast --- 去除常量性
用于常量指针或引用与非常量指针或引用之间的转换，只有const_cast才可以对常量进行操作，一般都是用它来去除常量性，去除常量性是危险操作，还是要谨慎操作。 

5. reinterpret_cast 
没啥场景，类似C语言中的强制类型转换，什么都可以转，万不得已不要使用
一般前三种转换方式不能解决问题了使用这种强制类型转换方式。

*/ 
#include <iostream> 

using namespace std; 


// 2. 类型转换1 --- sttatic_cast  
// 基类 
struct Base{
    virtual void Func() {cout << "Base Func \n";} 
}; 

// 派生类 
struct Derive : public Base{
    void Func() override {cout << "Derive Func \n"; } 
};  

void static_cast_demo(){
    float f = 1.123; 
    cout << "f " << f << endl;  
    // 查询f类型
    cout << "f typeid " << typeid(f).name() << endl; 
    int i = static_cast<int>(f); 
    cout << "i " << i << endl;   
    cout << "i typeid " << typeid(i).name() << endl; 

    // 易错点1 --- 不可以基于static_id将 float* 转换到 int *  
    // 不能使用static_cast在有类型指针之间进行类型转换。
    cout << "&f typeid " << typeid(&f).name() << endl; // type: Pf
    // int *pi = static_cast<int *>(&f); 

    // 是否可以将派生类指针转换成基类指针 
    // 子类对象指针转换成父类对象指针也可以使用static_cast
    Derive d;
    d.Func();   
    cout << " d typeid " << typeid(d).name() << endl; //  6Derive
    Base *b = static_cast<Base *>(&d);  
    b->Func(); 
    cout << " b typeid " << typeid(b).name() << endl; // P4Base

} 

// 3. 类型转换2 --- dynamic_cast 
// 用于将父类的指针或引用转换为子类的指针或引用，此场景下父类必须要有虚函数 
void dynamic_cast_demo(){
    Derive d; 
    d.Func();
    cout << "d typeid" <<  typeid(d).name() << endl; // 6Derive 
    Base *b = dynamic_cast<Base *>(&d); 
    b->Func(); 
    cout << "b typeid" <<  typeid(b).name() << endl;  // P4Base
    Derive *dd = dynamic_cast<Derive *>(b); 
    dd->Func(); 
    cout << "dd typeid" <<  typeid(dd).name() << endl;  // P6Derive
}

// 4. 类型转换3 --- const_cast  
void  const_cast_demo() {
    int data = 10;
    const int *cpi = &data; // int 常量指针  
    cout << " cpi typeid " << typeid(cpi).name() << endl; // 
    int *pi = const_cast<int *>(cpi);  // 常量 -> 非常量指针 
    cout << " pi typeid " << typeid(pi).name() << endl; // 
    const int *cpii = const_cast<const int *>(pi); 
    cout << " pi typeid " << typeid(cpii).name() << endl; // 
}

// 5. 类型转换4 --- reinterpret_cast  
void reinterpret_cast_demo() {
    int data = 10;
    cout << " &data typeid " << typeid(&data).name() << endl; // Pi 
    int *pi = &data; 
    cout << " pi typeid " << typeid(pi).name() << endl; // Pi
    float *fpi = reinterpret_cast<float *>(pi);  // int Pointer -> float Pointer
    cout << " fpi typeid " << typeid(fpi).name() << endl; // Pf 
}

int main(){

    // ------------------------------------------
    static_cast_demo(); 
    cout << "dynamic_cast_demo ..." << endl; 
    dynamic_cast_demo(); 
    cout << "const_cast_demo ..." << endl; 
    const_cast_demo(); 
    cout << "reinterpret_cast_demo ..." << endl;   
    reinterpret_cast_demo();
    // ------------------------------------------ 

    return 0; 
}