/*
实战1： 中括号重载
*/ 
#include <cstring>
#include <iostream>  

using namespace std; 

// 结构体 
struct Person{
    // 基本信息 
    double salary; 
    char *name; 
}; 

class SalaryManage{
    Person *employ;  // 存放职工信息数组 
    int max; // 下标上界 
    int n; // 数组中实际职工人数 

    public: 
        SalaryManage(int max){
            max = max;  
            n = 0; 
            employ = new Person[max];
        }

    // 返回引用特性是可以直接放在左值，方便使用  
    // --------------------------------------------------------
    // e.g. s["张三"] = 2188.88;  
    double &operator[](char *Name){
        // 重载 []， 返回引用   
        // 在调用s["张三"]时，会创建一个指向Person结构体的指针p。
        Person *p;  

        // 遍历存储员工信息的数组，如果找到姓名匹配的员工，则返回该员工的工资。
        for(p = employ; p<employ +n; p++){
            // 若存在，处理  
            if (strcmp(p->name, Name) == 0){
                return p->salary; 
            }
        }
        
        // 如果未找到姓名匹配的员工，则会在数组尾部添加一个新的员工。
        p = employ + n;  
        n++; 
        
        p->name = new char[strlen(Name) + 1]; 
        strcpy(p->name, Name); 
        p->salary = 0;  

        // 返回新员工的工资，以便进行赋值操作。 
        // 整个过程通过运算符重载的方式，使得访问指定员工的工资变得更加简洁和直观。
        return p->salary;
        // ---------------------------------------------------- 
    } 

    void display(){
        for(int i = 0; i<n; i++){
            cout << employ[i].name << " " << employ[i].salary << endl; 
        }
    } 

    // 析构
    ~SalaryManage(){
        for(int i = 0; i<n; i++){
            delete [] employ[i].name; 
        }
        delete [] employ; 
    }
}; 

int main(){ 
    // Max = 10 
    SalaryManage s(10); 
    s["张三"] = 2188.88; 
    s["李四"] = 1234.56; 
    s["王五"] = 3456.78; 
    s["赵六"] = 5678.90; 
    s["孙七"] = 7890.12; 

    cout << "张三" << " " << s["张三"] << endl; 
    cout << "李四" << " " << s["李四"] << endl;
    cout << "王五" << " " << s["王五"] << endl;
    cout << "赵六" << " " << s["赵六"] << endl;
    cout << "孙七" << " " << s["孙七"] << endl;

    cout << "----Display--------" << endl; 
    s.display();

}
