#include <iostream>  
#include <vector>
#include <algorithm> 

using namespace std; 

/*
需求：算法、容器、迭代器初识
- 向vector（容器）中插入（迭代器）数据并遍历（算法） 
- vector 分别存放 内置数据类型 & 自定义数据类型 
*/ 

void MyPrint(int val){
    cout << val << endl; 
}  

// 1. 内置数据类型存放 
void VectorData(){
    // 创建容器对象, 并且通过模板参数指定容器中存放的数据的类型 
    vector<int> v1; 
    // 插入 
    v1.push_back(10);
    v1.push_back(20); 
    v1.push_back(30); 
    v1.push_back(40); 

    // 每一个容器都有自己的迭代器，迭代器是用来遍历容器中的元素 
    // 遍历1  
    vector<int>::iterator itBegin = v1.begin();  
    vector<int>::iterator itEnd = v1.end(); 

    cout << "迭代器遍历1：" << endl; 
    while (itBegin != itEnd){
        cout << *itBegin << endl; // 类似于指针 
        itBegin++; 
    } 

    // 遍历2  
    cout << "迭代器遍历2：" << endl; 
    for (vector<int>::iterator it = v1.begin(); it!=v1.end(); it++){ 
        cout << *it << endl; 
    } 

    // 遍历3 -- for each算法遍历  
    cout << "算法遍历：" << endl; 
    for_each(v1.begin(), v1.end(), MyPrint); 

}

// 2. 自定义数据类型存放 
class Person{
    public: 
    // 构造  
    Person(string name, int age){
        mName = name; 
        mAge = age; 
    }

    public:
    string mName; 
    int mAge;
}; 

void MyPrintPerson(Person& person){
    cout << "姓名：" << person.mName << " 年龄：" << person.mAge << endl; 
}

void VectorPerson(){

    vector<Person> v2; 

    //创建数据
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);
	Person p4("ddd", 40);
	Person p5("eee", 50); 

    v2.push_back(p1);
	v2.push_back(p2);
	v2.push_back(p3);
	v2.push_back(p4);
	v2.push_back(p5); 

    // for each 遍历
    cout << "算法遍历：" << endl; 
    for_each(v2.begin(), v2.end(), MyPrintPerson); 

    // 迭代器遍历   
    cout << "迭代器遍历：" << endl; 
    for(vector<Person>::iterator it = v2.begin(); it!=v2.end(); it++){
        cout << "姓名：" << it->mName << " 年龄：" << it->mAge << endl;  
        cout << "姓名：" << (*it).mName << "年龄："<< (*it).mAge << endl;  
    } 

    // 可以存放对象指针   
    // 存储Person对象指针的vector
    vector<Person*> v3;  
    v3.push_back(&p1);
	v3.push_back(&p2);
	v3.push_back(&p3);
	v3.push_back(&p4);
	v3.push_back(&p5);  

    for(vector<Person*>::iterator it = v3.begin(); it!=v3.end(); it++){
        // cout << it << endl; 
        Person* p = (*it);  // 指针 
        cout << "Name: " << p->mName << " Age:" << (*it)->mAge << endl;
    }
}

int main(){

    VectorData(); 
    cout << "---------" << endl;  
    VectorPerson(); 
    // system("pause") // system("pause")会暂停程序的执行，直到用户按下键盘上的任意键后才会继续。这通常用于调试和观察程序的执行过程。
    return 0; 
}
