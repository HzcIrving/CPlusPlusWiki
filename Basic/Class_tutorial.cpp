/*
类与面对对象OOP编程技术 C++   
------------------------------
OOP (Object Oriented Programming)面向对象编程 程序化编程只指编写对数据进行操作的程序或函数； 
面向对象编程是指创建同时包含数据和函数的对象

包含重点知识1：构造函数与析构函数 
>>> 类的构造函数是类的一种特殊的成员函数，它会在每次[创建类]的新对象时执行。  
    ClassName::ClassName 
>>> 类的析构函数是类的一种特殊的成员函数，它会在每次[删除类]所创建的对象时执行。  
>>> 只是在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数。
>>> 析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。
    ClassName::~ClassName 

2. 拷贝构造 
>>> 类对象与普通对象不同，类对象内部结构一般较为复杂，存在各种成员变量。 
>>> 相同类型的类对象是通过拷贝构造函数来完成整个复制过程的。 
>>> 如果在类中没有定义拷贝构造函数，编译器会自行定义一个。
>>> 如果类带有指针变量，并有动态内存分配，则它必须有一个拷贝构造函数。

------------------------------
*/

#include <iostream> 
using namespace std; 

class Car{  
    // 类内Private. 不允许外部访问 
    // private access specifier，私有访问说明符  
    // getter和setter是用于访问和修改私有成员变量的方法。  
    // Getter用于获取私有成员变量的当前值，而setter用于设置私有成员变量的新值。
    // 它们提供了对私有成员变量进行控制的简便方式，同时也可确保对这些成员变量的访问和修改按照类的设计进行，以确保程序的正确性和可维护性。
    private:
        string disadvantages = "容易坏!";  

    public: // 类内public 允许外部访问  
        string brand; // 1. 类中定义的变量为属性 
        string model; 
        int year;  
    
        // 2. 类中的函数叫做Method方法
        int speed(int maxSpeed); // 申明一下 
        void myMethod(){
            cout << "类中的函数叫做Method方法 \n"; 
        } 

        // 4. private变量修改  
        // 4.1 setter
        void setDisadvantages(string x){
            disadvantages = x;
        }

        // 4.2 getter 
        string getDisadvantages(){
            return disadvantages;
        }

}; // 注意这个";" 不可以少 

// 类中的方法第二种定义模式 
int Car::speed(int maxSpeed){
    return maxSpeed;
}

// 3. 类的构造函数 --- 初始化工具
// 类的构造函数是一种特殊的成员函数，它用于创建对象时初始化对象的数据成员。
// 在C++中，构造函数的名称必须与类的名称相同，且没有返回类型（不应该有void）。 
// 构造函数可以带有参数（参数列表可以为空），也可以被重载。  
// 类似于Python Class 的__init__ 
class Car_CF{
    public:
        string brand;
        string model; 
        int year;  

        // 构造函数，会在每次创建类的新对象时执行 ... 
        Car_CF(string x, string y, int z);  

        ~Car_CF(); 
};

// 类的构造函数 
Car_CF::Car_CF(string x, string y, int z){
    brand = x;
    model = y;
    year = z;
    cout << "Car()构造函数被调用" << endl; 
}

// 类的析构函数（释放资源）
Car_CF::~Car_CF(){
  cout << "Car()构造析构函数，资源已释放，ByeBye" << endl; 
}

// 5. 类继承 
// 5.1 Base class 基类 
class Vehicle {
  public:
    string brand = "Ford"; 

    // 构造函数
    Vehicle() {
      cout << "This is a Ford Vehicle" << endl;
    }

  // Protected类 
  protected: 
    string disadvantages = "Protected变量(子类可以用), ";  
};  

class Vehicle2 {
  public:
    string brand = "BMW"; 

    // 构造函数 
    Vehicle2() {
      cout << "This is a BMW Vehicle" << endl;
    }
}; 

// 5.2 Derived class 派生类 
class Car_Derive: public Vehicle {
  public: 
    string model = " New add (derive) --- [Mustang] "; // 新增  

    // protected use in Vehicle:  
    void setdisadvantages(string s){
        cout << "使用了Vehicle模板的Protected变量!\n";
        disadvantages = s; 
    }
    string getdisadvantages(){
        return disadvantages; 
    }

};  

// 5.3 Derived Double class 多继承派生 
class Car_Double_Derive: public Vehicle, public Vehicle2 {
  public: 
    string model = " New add (double derive) --- [Mustang], [BMW] "; // 新增 
}; 

// 6. 拷贝构造 
// 带有指针变量+动态内存分配的拷贝构造函数 
/*
classname (const classname &obj){
  // 主体 
}
*/ 

class Line{
  public: 
    int getLength(void); 
    Line(int len); // 简单构造 
    Line(const Line &obj); // 拷贝构造 
    ~Line(); // 析构 

  private: 
    int *ptr; 
}; 

// 构造
Line::Line(int len){
  cout << "Normal constructor allocating ptr" << endl;
  // 为指针分配内存 
  ptr = new int; 
  *ptr = len; 
} 

// 拷贝构造 
Line::Line(const Line &obj){
  cout << "Copy constructor allocating ptr" << endl;
  ptr = new int; 
  *ptr = *obj.ptr; // copy 拷贝构造+动态内存分配 
} 
 
// 析构函数 
Line::~Line(){
  cout << "Freezing Memory " << endl; 
  delete ptr; 
}

int Line::getLength(void){
  return *ptr; 
}

void display(Line obj)
{
   cout << "Length of line : " << obj.getLength() <<endl;
}
 
int main(){

    //////////////////////////////////////////////////////////////////////////
    // 实例化一辆车  
    // 在类中定义的对象称为实例，或者称为对象，此时才会分配内存
    Car carObj1;    // 在类中定义的对象称为实例，或者称为对象，此时才会分配内存
    carObj1.brand = "BMW";
    carObj1.model = "X5";
    carObj1.year = 1999;

    // Create another object of Car
    Car carObj2;
    carObj2.brand = "Ford";
    carObj2.model = "Mustang";
    carObj2.year = 1969;

    // Print attribute values
    cout << carObj1.brand << " " << carObj1.model << " " << carObj1.year << endl;
    cout << carObj2.brand << " " << carObj2.model << " " << carObj2.year << endl; 

    ////////////////////////////////////////////////////////////////////////// 
    Car myObj;
    cout << myObj.speed(200) << endl; 
    myObj.myMethod();


    /////////////////////////////////////////////////////////////////////////
    // 构造函数  
    // 注意：创建时就会调用里面的Car(string x, string y, int z)
    Car_CF carObj3("BMW", "X5", 2017); 
    Car_CF carObj4("Ford", "Mustang", 1969); 

    cout << carObj3.brand << " " << carObj3.model << " " << carObj3.year << endl;
    cout << carObj4.brand << " " << carObj4.model << " " << carObj4.year << endl;


    ///////////////////////////////////////////////////////////////////////// 
    // 私有变量修改 
    carObj1.setDisadvantages("Easy to break ");  
    carObj2.setDisadvantages("No Front Rader"); 
    cout << carObj1.getDisadvantages() << endl; 
    cout << carObj2.getDisadvantages() << endl;

    ///////////////////////////////////////////////////////////////////////// 
    // 继承 
    Car_Derive myCar_DeriveFromVehicle;  
    cout << myCar_DeriveFromVehicle.brand << " " << myCar_DeriveFromVehicle.model << endl; 

    // protected disadvantages 
    myCar_DeriveFromVehicle.setdisadvantages("No Front Rader"); 
    cout << "---" << myCar_DeriveFromVehicle.getdisadvantages() << endl;


    // 多继承 
    Car_Double_Derive myCar_Double_DeriveFromVehicle; 
    cout << myCar_Double_DeriveFromVehicle.model << endl;

    // 拷贝构造 
    Line line(10); // length 10 
    display(line);

    // 通过使用已有的同类型的对象来初始化新创建的对象：  
    Line line2 = line; // 拷贝构造调用 
    display(line2);  


    return 0;  

}
