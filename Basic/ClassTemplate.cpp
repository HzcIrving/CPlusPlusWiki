/*
1. 类模板对象做函数参数
 1. 指定传入的类型 --- 直接显示对象的数据类型
 2. 参数模板化 --- 将对象中的参数变为模板进行传递
 3. 整个类模板化 --- 将这个对象类型 模板化进行传递
*/

#include <iostream>
#include <string>
using namespace std; 

template <class NameType, class AgeType = int> 
class Person{
    public:
        Person(NameType name, AgeType age){
            this->mName = name; 
            this->mAge = age;
        }

        void showPerson(){
            cout << "name: " << this->mName << " age: " << this->mAge << endl; 
        } 

    public:
        NameType mName; 
        AgeType mAge; 
}; 

// 参数模块化  
template <class T1, class T2> 
void PrintPerson(Person<T1, T2> &p){
    p.showPerson();  
    cout << "T1类型:" << typeid(T1).name() << endl;  // string 
    cout << "T2类型:" << typeid(T2).name() << endl;  // int 
}  

// 整个类模块化
template <class T> 
void PrintPerson2(T &p){
    p.showPerson(); 
    cout << "T类型:" << typeid(T).name() << endl;  // Person 
}

// 指定类型 
void PrintPerson3(Person<string,int> &p){
    p.showPerson();
}

void testPP(){
    Person<string, int> p("Tom", 90); 
    PrintPerson(p); 
    PrintPerson2(p);
    PrintPerson3(p);
} 


/*
2. 类模板与继承 
    当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型
    如果不指定，编译器无法给子类分配内存
    如果想灵活指定出父类中T的类型，子类也需变为类模板
*/ 
template<class T> 
class Base{
    T m;
}; 

class Son :public Base<int> {// 必须指定类型
}; 

void test01(){
    Son c; 
}; 

// 类模板继承类模板 ,可以用T2指定父类中的T类型 
template<class T1, class T2> 
class Son2 :public Base<T2>{
    public:
        Son2(){
            cout << typeid(T1).name() << endl;  // int 
            cout << typeid(T2).name() << endl;  // char
        }
}; 

void test02(){ 
    // 指定了类型 
    Son2<int, char> child1; 
}

/*
3. 类模板成员函数类外实现时，需要加入模板参数列表 
//构造函数 类外实现
template<class T1, class T2>
    Person<T1, T2>::Person(T1 name, T2 age) {
    this->m_Name = name;
    this->m_Age = age;
}
//成员函数 类外实现
template<class T1, class T2>
    void Person<T1, T2>::showPerson() {
    cout << "姓名: " << this->m_Name << " 年龄:" << this->m_Age << endl;
}
*/  





int main(){
    // testPP(); 
    test02();
    return 0; 
}