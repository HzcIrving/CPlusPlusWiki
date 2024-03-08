/*
1. vector vs. 数组
答：数组静态空间，vector可以动态拓展 

2. vector动态拓展 
答：1) 并不是在原空间之后续接新空间，而是找更大的内存空间，然后将原数据拷贝新空间，释放原空间
    2) vector容器的迭代器是支持随机访问的迭代器 

3. vector构造 
- 创建vector容器 
    3.1 vector<T> v; //采用模板实现类实现，默认构造函数
    3.2 vector(v.begin(), v.end()); //将v[begin(), end())区间中的元素拷贝给本身。
    3.3 vector(n, elem); //构造函数将n个elem拷贝给本身。
    3.4 vector(const vector &vec); //拷贝构造函数。 
  各种构造方式不存在可比性，灵活使用即可 

4. vector赋值  
    4.1 vector& operator=(const vector &vec); //重载等号操作符 
    4.2 assign(beg, end // 将[beg, end)区间中的数据拷贝赋值给本身。 
    4.3 assign(n, elem); //将n个elem拷贝赋值给本身。 

5. vector容量和大小 
    5.1 empty(); //判断容器是否为空
    5.2 capacity(); //容器的容量
    5.3 size(); //返回容器中元素的个数
    5.4 resize(int num); //重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
                         //如果容器变短，则末尾超出容器长度的元素被删除。
    5.5 resize(int num, elem); //重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
                        //如果容器变短，则末尾超出容器长度的元素被删除 

*6. vector插入和删除 
        push_back(ele); //尾部插入元素ele
        pop_back(); //删除最后一个元素
        insert(const_iterator pos, ele); //迭代器指向位置pos插入元素ele
        insert(const_iterator pos, int count,ele); //迭代器指向位置pos插入count个元素ele
        erase(const_iterator pos); //删除迭代器指向的元素
        erase(const_iterator start, const_iterator end); //删除迭代器从start到end之间的元素
        clear(); //删除容器中所有元素 

7. vector数据存取 
    对vector中的数据的存取操作 
        at(int idx); //返回索引idx所指的数据
        operator[]; //返回索引idx所指的数据
        front(); //返回容器中第一个数据元素
        back(); //返回容器中最后一个数据元素 

8. vector数据互换 
    swap(vec); // 将vec与本身的元素互换  
    swap可以用于收缩内存 (8.1)

*9. vector空间预留 
    减少vector在动态扩展容量时的扩展次数 
    reserve(int len); //容器预留len个元素长度，预留位置不初始化，元素不可访问。

*/

#include <iostream> 
#include <vector> 
using namespace std;

// 这里引用传递
// void func(const A &a)
// - 对于非内部数据类型的参数而言，象void func(A a) 这样声明的函数注定效率比较低。
//    因为函数体内将产生A类型的临时对象用于复制参数a，而临时对象的构造、复制、析构过程都将消耗时间 (A类型是自定的)
// - 为了提高效率，可以将函数声明改为void func(A &a)，因为“引用传递”仅借用一下参数的别名而已，不需要产生临时对象。
void printVector(vector<int> &v){
    for (vector<int>::iterator it = v.begin(); it!=v.end(); it++){
        cout << *it << " "; 
    }
    cout << endl; 
} 

// 8.1 内存收缩工具 
void MemoryShrinkTool(vector<int> &v){ 
    // swap可以使两个容器互换，可以达到实用的收缩内存效果
    vector<int>(v).swap(v); 
}

int main(){

    vector<int> v1; // 3.1 默认构造 
    for(int i=0; i<10; i++){
        v1.push_back(i); 
    }
    printVector(v1); 

    vector<int> v2(v1.begin(), v1.end()); // 3.2 将v[begin(), end())区间中的元素拷贝给本身。 
    printVector(v2);  

    vector<int> v3(10, 100); // 3.3 构造函数将n个elem拷贝给本身。 
    printVector(v3); 

    vector<int> v4(v3); // 3.4 vector(const vector &vec) --- 拷贝构造  
    printVector(v4); 

    vector<int> v5 = v1;  //4.1 重载等号操作符  
    printVector(v5);  

    vector<int> v6; 
    v6.assign(v1.begin()+1, v1.end()-1); // 4.2 将[beg, end)区间中的数据拷贝赋值给本身。 
    printVector(v6);  // 1~8 

    vector<int> v7; 
    v7.assign(100, 66); // 4.3 /将n个elem拷贝赋值给本身。
    printVector(v7);  


    // ---------------- 5. 容量和大小demo ----------------------------
    vector<int> v8 = {}; 
    cout << v8.empty() << endl;  // 1 // 5.1 判断容器为空 
    if (v8.empty()){
        v8 = v1; 
    }
    cout << v8.empty() << endl;  
    cout << "v8容量:" << v8.capacity() << endl; 
    cout << "v8大小:" << v8.size() << endl;  
    
    // resize变小  
    vector<int> v9; 
    v9.assign(v8.begin(), v8.end());  
    v9.resize(v9.size() - 2); 
    cout << "v9 resize后容量:" << v9.capacity() << endl; // 容量10 
    cout << "v9 resize后大小:" << v9.size() << endl; // 大小8  ---- 注意size反应真实大小，capacity是开辟的容量
    
    v9.resize(12); // 填充回12 
    printVector(v9);  // 默认0填充
    cout << "v9 resize后容量:" << v9.capacity() << endl; // 容量16?  通常会分配比所需大小更大的内存空间，以便在需要时可以容纳更多的元素，从而避免频繁的内存重新分配操作。
    cout << "v9 resize后大小:" << v9.size() << endl; // 大小12 ? 

    v9.resize(20,10); // 填充到20，默认用10填充 
    printVector(v9); // 0 1 2 3 4 5 6 7 0 0 0 0 10 10 10 10 10 10 10 10  
    cout << "v9 resize后容量:" << v9.capacity() << endl; // 容量24
    cout << "v9 resize后大小:" << v9.size() << endl;  

    // -------------------- 6. vector插入和删除 ---------------------------------
    vector<int> v10; 

    // 尾插 
    v10.push_back(10);
    v10.push_back(20);
    v10.push_back(30);
    v10.push_back(40);
    v10.push_back(50);
    printVector(v10); 

    // 尾删 
    v10.pop_back(); 
    v10.pop_back(); 
    printVector(v10); 

    // 插入 
    v10.insert(v10.begin(), 100); 
    printVector(v10); 
    v10.insert(v10.begin(), 3, 166); 
    printVector(v10);  

    // 删除 
    v10.erase(v10.begin()); 
    printVector(v10); 
    v10.erase(v10.begin()+2, v10.end()-2); 
    printVector(v10); 

    v10.clear(); 
    cout << "v10是否empty? 答:" << v10.empty() << endl;  

    
    // -------------------- 7. vector数据存取 ---------------------------------
    // 基于数据取用功能遍历  
    vector<int> v11 = v1; 
    for(int i = 0; i < v11.size(); i++){
        cout << "at访问: " <<  v11.at(i) << endl; 
        cout << "[]访问: " <<  v11[i] << endl;
    }  

    cout << "v11第1个数: " << v11.front() << endl; 
    cout << "v11最后1个数: " << v11.back() << endl; 

    // ------------------- 8.swap交换与内存收缩 ------------------------------- 
    vector<int> v12; 
    for (int i = 0; i<=99999; i++){
        v12.push_back(i);
    }
    cout << "v12容量: " << v12.capacity() << endl; 
    cout << "v12大小: " << v12.size() << endl;  

    v12.resize(10);
    cout << "v12容量: " << v12.capacity() << endl; 
    cout << "v12大小: " << v12.size() << endl;   

    MemoryShrinkTool(v12); 
    cout << "缩容后v12容量: " << v12.capacity() << endl; 
    cout << "缩容后v12大小: " << v12.size() << endl;    

    // 普通功能，交换
    v10.swap(v12);
    printVector(v10); 

    // ------------------- 9.reserve预留空间 ------------------------------- 
    // 比如需要一个大数组，直接开辟相应的内存空间即可 
    vector<int> v13; 

    //预留空间
    v13.reserve(100000);
    int num = 0;
    int* p = NULL; //空指针 
    for (int i = 0; i < 100000; i++) {
        v13.push_back(i);
        if (p != &v13[0]) {
            p = &v13[0];
            num++;
        }
    }

    cout << "num:" << num << endl;
    cout << "v13容量: " << v13.capacity() << endl; 
    cout << "v13大小: " << v13.size() << endl;   // 此时capacity和size肯定相等了 

    return 0; 
}