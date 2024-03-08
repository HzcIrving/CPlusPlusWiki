/*多态
多态是面向对象程序设计中的一个重要概念，表示对象同一个行为或方法在不同情况下的不同响应方式。具体而言，多态性指的是同一个类的不同对象在调用同一个方法时，可以表现出不同的行为。这个特点使得程序更加灵活和可扩展，也是面向对象编程的一个重要优势。

多态可以分为编译时多态和运行时多态。编译时多态主要包括函数重载和运算符重载，通过函数签名或参数的不同来区分不同的行为；而运行时多态主要通过虚函数和抽象类实现，让对象在运行期确定调用哪个版本的方法。

例如，有一个动物基类，包含了一个虚函数makeSound()，派生类Dog和Cat分别重写了这个函数，分别实现了不同的叫声。当我们在调用一个指向动物对象的指针的makeSound()方法时，实际上调用的是这个对象所属的子类的makeSound()方法，即运行时多态。这样就让代码更加灵活，可以处理不同类型的对象，而不需要为每一个对象再写相应的代码。
*/ 

#include <iostream> 
using namespace std; 

// Base Class 
class Animal{
    public: 
        // virtual函数 
        void animalSound(){
            cout << "Animal is making a sound" << endl; 
        }
};

// Derived Class 1 
class Pig: public Animal{
    public: 
        // 重写 
        void animalSound(){
            cout << "Pig says: wee wee" << endl; 
        }
}; 


// Derived Class 2
class Dog: public Animal{
    public: 
        // 重写 
        void animalSound(){
            cout << "Dog says: bow bow" << endl; 
        }
}; 

int main(){
    Animal myAnimal; 
    Pig myPig; 
    Dog myDog; 

    myAnimal.animalSound(); 
    myPig.animalSound(); 
    myDog.animalSound(); 

    return 0;

}