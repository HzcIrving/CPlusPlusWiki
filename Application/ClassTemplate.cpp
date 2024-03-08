/*
案例描述: 实现一个通用的数组类，要求如下： 
-------------------------------------------
可以对内置数据类型以及自定义数据类型的数据进行存储
将数组中的数据存储到[堆区] 
    | 用于存储程序运行时动态分配的内存。当程序运行时，它会根据
    | 需要动态分配内存来存储数据、对象和临时变量等。这些内存区域在程序结束时会被释放，由操作系统回收。
构造函数中可以传入数组的容量
提供对应的[拷贝构造函数]以及[operator=防止浅拷贝]问题
提供[尾插法]和[尾删法]对数组中的数据进行增加和删除
可以通过[下标]的方式访问数组中的元素
可以获取数组中当前[元素个数]和[数组的容量] 
------------------------------------------- 

*/

#include <iostream>
#include <string>
#include "../include/MyArray.h"

using namespace std;  

void printIntArray(MyArray<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 内置数据类型测试
void test01(){
    MyArray<int> array1(10); // 初始化的值capacity  
    for (int i = 0; i < 10; i++)
    {
    array1.push_back(i); 
    }
    cout << "array1打印输出：" << endl;
    printIntArray(array1);
    cout << "array1的大小：" << array1.size() << endl;
    cout << "array1的容量：" << array1.capacity() << endl;
    cout << "--------------------------" << endl;
    MyArray<int> array2(array1);
    array2.pop_back();
    cout << "array2打印输出：" << endl;
    printIntArray(array2);
    cout << "array2的大小：" << array2.size() << endl;
    cout << "array2的容量：" << array2.capacity() << endl;
} 

//测试自定义数据类型
class Person {
public:
    Person() {}
    Person(string name, int age) {
    this->m_Name = name;
    this->m_Age = age;
}
public:
    string m_Name;
    int m_Age;
};

void printPersonArray(MyArray<Person>& personArr)
{
    for (int i = 0; i < personArr.size(); i++) {
        cout << "姓名：" << personArr[i].m_Name << " 年龄： " << personArr[i].m_Age << endl;
    }
} 

void test02()
{
    //创建数组
    MyArray<Person> pArray(10);
    Person p1("孙悟空", 30);
    Person p2("韩信", 20);
    Person p3("妲己", 18);
    Person p4("王昭君", 15);
    Person p5("赵云", 24);
    //插入数据
    pArray.push_back(p1); 

    pArray.push_back(p2);
    pArray.push_back(p3);
    pArray.push_back(p4);
    pArray.push_back(p5);
    printPersonArray(pArray);
    cout << "pArray的大小：" << pArray.size() << endl;
    cout << "pArray的容量：" << pArray.capacity() << endl;
}



int main(){
    // test01();
    test02();
    return 0; 
}